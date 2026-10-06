/************************************************************************/
/*									*/
/* PCG-8100 sound: 8253 compatible PIT, three square/pulse outputs	*/
/*									*/
/* The PIT runs in whole PIT clocks. Audio is produced per sound	*/
/* window: the stretch of emulated time snddrv mixes into one		*/
/* osd_update_audio_stream() call. A port write first renders the	*/
/* outputs up to its position in the window, then takes effect, so	*/
/* nothing is queued and everything the next sample depends on is in	*/
/* the savestate.							*/
/*									*/
/************************************************************************/

#include <string.h>

#include "quasi88.h"
#include "pcg8100.h"

#include "intr.h"
#include "memory.h"
#include "suspend.h"

/* snddrv: position within the current sound window, scaled to value */
int	sound_scalebufferpos(int value);

#define	PCG8100_CLOCK		3993600.0	/* PIT clock, Hz	*/
#define	PCG8100_CH_LEVEL	3584		/* one output, high	*/

#define	PCG8100_EN0		0x08	/* Port 02h D3 */
#define	PCG8100_EN1		0x40	/* Port 02h D6 */
#define	PCG8100_EN2		0x80	/* Port 02h D7 */

/* Longest window: 44100 / 10 Hz VSYNC */
#define	PCG_MAX_SAMPLES		4410

/* Window length in PIT clocks, fixed point */
#define	PCG_WIN_FRAC_BITS	12

/* DC blocker pole, Q15 (about 20 Hz at 44.1 kHz) */
#define	PCG_DC_POLE		32674


typedef struct {
	int		rw_mode;
	int		mode;
	int		bcd;

	int		write_phase;
	int		write_lsb;

	int		reload;
	int		pending_reload;

	int		pending_valid;
	int		null_count;

	int		output;
	int		gate;
	int		counting;

	int		remain;		/* PIT clocks to the next transition */

	int		trigger_pending;
	int		pulse_state;

	int		load_pending;
	int		programmed;
} PCG8253_CHANNEL;


static	PCG8253_CHANNEL	pcg_ch[3];
static	int		pcg_enable;

/* The current sound window */
static	int		pcg_win_clocks;		/* length, PIT clocks	*/
static	int		pcg_win_carry;		/* fraction carried over */
static	int		pcg_win_samples;	/* length, samples	*/
static	int		pcg_t;			/* rendered up to	*/
static	int		pcg_sample;		/* sample holding pcg_t	*/
static	int		pcg_sample_end;		/* where that sample ends */
static	int		pcg_acc[PCG_MAX_SAMPLES];	/* high clocks	*/

/* DC blocker */
static	int		pcg_dc_x;
static	int		pcg_dc_y;


/*----------------------------------------------------------------------*/
/* 8253 channel								*/
/*----------------------------------------------------------------------*/

static int pcg_bcd_to_bin(int v)
{
	return  (v        & 0x0f)
	     + ((v >>  4) & 0x0f) * 10
	     + ((v >>  8) & 0x0f) * 100
	     + ((v >> 12) & 0x0f) * 1000;
}

static int pcg_effective_count(const PCG8253_CHANNEL *ch, int reload)
{
	int n = ch->bcd ? pcg_bcd_to_bin(reload) : reload;

	if (n == 0)
		n = ch->bcd ? 10000 : 65536;
	return n;
}

static void pcg_schedule_mode3_half(PCG8253_CHANNEL *ch)
{
	int n = pcg_effective_count(ch, ch->reload);

	if (n < 2)
		n = 2;
	if (n & 1)
		ch->remain = ch->output ? (n + 1) / 2 : (n - 1) / 2;
	else
		ch->remain = n / 2;
	if (ch->remain < 1)
		ch->remain = 1;
	ch->counting = 1;
}

static void pcg_load_ce(PCG8253_CHANNEL *ch)
{
	int n;

	if (ch->pending_valid) {
		ch->reload = ch->pending_reload;
		ch->pending_valid = 0;
	}

	ch->null_count   = 0;
	ch->load_pending = 0;
	ch->counting     = 1;

	n = pcg_effective_count(ch, ch->reload);

	switch (ch->mode) {
	case 0:
		ch->output      = 0;
		ch->pulse_state = 0;
		ch->remain      = n;
		break;

	case 1:
		ch->output      = 0;
		ch->pulse_state = 1;
		ch->remain      = n;
		break;

	case 2:
		ch->output      = 1;
		ch->pulse_state = 0;
		ch->remain      = (n > 1) ? n - 1 : 1;
		break;

	case 3:
		ch->output = 1;
		pcg_schedule_mode3_half(ch);
		break;

	case 4:
	case 5:
		ch->output      = 1;
		ch->pulse_state = 0;
		ch->remain      = n;
		break;

	default:
		ch->counting = 0;
		ch->remain   = 0;
		break;
	}
}

/* The channel's next transition is due */
static void pcg_update_channel(PCG8253_CHANNEL *ch)
{
	int n;

	if (ch->load_pending) {
		if (ch->mode == 1 || ch->mode == 5) {
			if (!ch->trigger_pending && ch->gate == 0) {
				ch->load_pending = 0;
				ch->remain       = 0;
				return;
			}
			ch->trigger_pending = 0;
		}
		pcg_load_ce(ch);
		return;
	}

	switch (ch->mode) {
	case 0:
		ch->output   = 1;
		ch->counting = 0;
		ch->remain   = 0;
		break;

	case 1:
		ch->output      = 1;
		ch->counting    = 0;
		ch->pulse_state = 0;
		ch->remain      = 0;
		break;

	case 2:
		if (ch->pulse_state == 0) {
			ch->output      = 0;
			ch->pulse_state = 1;
			ch->remain      = 1;
		} else if (ch->pending_valid)
			pcg_load_ce(ch);
		else {
			ch->output      = 1;
			ch->pulse_state = 0;
			n               = pcg_effective_count(ch, ch->reload);
			ch->remain      = (n > 1) ? n - 1 : 1;
			ch->counting    = 1;
		}
		break;

	case 3:
		ch->output = ch->output ? 0 : 1;
		if (ch->pending_valid) {
			ch->reload        = ch->pending_reload;
			ch->pending_valid = 0;
			ch->null_count    = 0;
		}
		pcg_schedule_mode3_half(ch);
		break;

	case 4:
	case 5:
		if (ch->pulse_state == 0) {
			ch->output      = 0;
			ch->pulse_state = 1;
			ch->remain      = 1;
			ch->counting    = 1;
		} else {
			ch->output      = 1;
			ch->pulse_state = 0;
			ch->counting    = 0;
			ch->remain      = 0;
			if (ch->mode == 5 && ch->pending_valid) {
				ch->load_pending    = 1;
				ch->trigger_pending = 1;
				ch->remain          = 1;
			}
		}
		break;

	default:
		ch->counting = 0;
		ch->remain   = 0;
		break;
	}
}

/* Advances a channel by d PIT clocks; returns the clocks its output was
 * high. A running mode 2 or 3 square skips whole periods at once. */
static int pcg_advance(PCG8253_CHANNEL *ch, int d)
{
	int high = 0;

	while (d > 0) {
		if (!(ch->counting || ch->load_pending) || ch->remain <= 0) {
			if (ch->output)
				high += d;
			break;
		}
		if (d < ch->remain) {
			if (ch->output)
				high += d;
			ch->remain -= d;
			break;
		}

		if (ch->output)
			high += ch->remain;
		d         -= ch->remain;
		ch->remain = 0;

		pcg_update_channel(ch);
		if ((ch->counting || ch->load_pending) && ch->remain < 1)
			ch->remain = 1;

		if (d > 0 && ch->counting && !ch->load_pending && !ch->pending_valid
		 && (ch->mode == 2 || ch->mode == 3)) {
			int n      = pcg_effective_count(ch, ch->reload);
			int period = (ch->mode == 3 && n < 2) ? 2 : n;

			if (period >= 2 && d >= period) {
				int k     = d / period;
				int phigh = (ch->mode == 3) ? (period + 1) / 2 : period - 1;

				high += k * phigh;
				d    -= k * period;
			}
		}
	}
	return high;
}

static void pcg_write_control(PCG8253_CHANNEL *ch, int data)
{
	int rw   = (data >> 4) & 3;
	int mode = (data >> 1) & 7;

	if (rw == 0)		/* counter latch: nothing reads the counters */
		return;
	if (mode >= 6)
		mode -= 4;

	ch->rw_mode         = rw;
	ch->mode            = mode;
	ch->bcd             = data & 1;
	ch->write_phase     = 0;
	ch->write_lsb       = 0;
	ch->pending_valid   = 0;
	ch->null_count      = 1;
	ch->counting        = 0;
	ch->load_pending    = 0;
	ch->trigger_pending = 0;
	ch->pulse_state     = 0;
	ch->remain          = 0;
	ch->programmed      = 1;
	ch->output          = (mode == 0) ? 0 : 1;
}

static void pcg_commit_count(PCG8253_CHANNEL *ch, int value)
{
	ch->pending_reload = value & 0xffff;
	ch->pending_valid  = 1;
	ch->null_count     = 1;
	ch->programmed     = 1;

	switch (ch->mode) {
	case 0:
		ch->output       = 0;
		ch->counting     = 0;
		ch->load_pending = 1;
		ch->remain       = 1;
		break;

	case 1:
	case 5:
		ch->trigger_pending = 1;
		ch->load_pending    = 1;
		ch->remain          = 1;
		break;

	case 2:
	case 3:
		if (!ch->counting) {
			ch->load_pending = 1;
			ch->remain       = 1;
		}
		break;

	case 4:
		ch->load_pending = 1;
		ch->remain       = 1;
		break;

	default:
		break;
	}
}

static void pcg_write_count(PCG8253_CHANNEL *ch, int data)
{
	if (!ch->programmed && ch->rw_mode == 0)
		return;

	switch (ch->rw_mode) {
	case 1:
		pcg_commit_count(ch, data);
		break;

	case 2:
		pcg_commit_count(ch, data << 8);
		break;

	case 3:
		if (ch->write_phase == 0) {
			ch->write_lsb   = data;
			ch->write_phase = 1;
		} else {
			ch->write_phase = 0;
			pcg_commit_count(ch, ch->write_lsb | (data << 8));
		}
		break;

	default:
		break;
	}
}


/*----------------------------------------------------------------------*/
/* Sound window								*/
/*----------------------------------------------------------------------*/

static int pcg_window_samples(void)
{
	int n = (int)(44100 / vsync_freq_hz);

	if (n < 1)
		n = 1;
	if (n > PCG_MAX_SAMPLES)
		n = PCG_MAX_SAMPLES;
	return n;
}

/* Where sample i of the window starts, in PIT clocks */
static int pcg_sample_start(int i)
{
	return (int)(((unsigned long)pcg_win_clocks * (unsigned long)i)
		     / (unsigned long)pcg_win_samples);
}

static void pcg_start_window(void)
{
	int step = (int)(PCG8100_CLOCK * (double)(1 << PCG_WIN_FRAC_BITS)
			 / vsync_freq_hz + 0.5);
	int len  = pcg_win_carry + step;

	pcg_win_clocks  = len >> PCG_WIN_FRAC_BITS;
	pcg_win_carry   = len & ((1 << PCG_WIN_FRAC_BITS) - 1);
	pcg_win_samples = pcg_window_samples();
	pcg_t           = 0;
	pcg_sample      = 0;
	pcg_sample_end  = pcg_sample_start(1);
	memset(pcg_acc, 0, sizeof(pcg_acc));
}

/* Renders the outputs up to PIT clock t of the window */
static void pcg_render_to(int t)
{
	static const int enable_bit[3] = { PCG8100_EN0, PCG8100_EN1, PCG8100_EN2 };
	int i, end, high;

	if (t > pcg_win_clocks)
		t = pcg_win_clocks;

	while (pcg_t < t) {
		end = (t < pcg_sample_end) ? t : pcg_sample_end;

		for (i = 0; i < 3; i++) {
			high = pcg_advance(&pcg_ch[i], end - pcg_t);
			if (pcg_enable & enable_bit[i])
				pcg_acc[pcg_sample] += high;
		}
		pcg_t = end;

		if (pcg_t == pcg_sample_end && pcg_sample + 1 < pcg_win_samples) {
			pcg_sample++;
			pcg_sample_end = pcg_sample_start(pcg_sample + 1);
		}
	}
}

/* Removes the DC level the outputs sit at, as the board's output
 * capacitor does */
static int pcg_dc_block(int x)
{
	long t = (long)pcg_dc_y * PCG_DC_POLE;
	int  y = x - pcg_dc_x + (int)(t >= 0 ? t >> 15 : -((-t) >> 15));

	pcg_dc_x = x;
	pcg_dc_y = y;
	return y;
}


/*----------------------------------------------------------------------*/
/* Interface								*/
/*----------------------------------------------------------------------*/

void pcg8100_reset(void)
{
	int i;

	memset(pcg_ch, 0, sizeof(pcg_ch));
	for (i = 0; i < 3; i++)
		pcg_ch[i].gate = 1;
	pcg_enable    = 0;
	pcg_win_carry = 0;
	pcg_dc_x      = 0;
	pcg_dc_y      = 0;
	pcg_start_window();
}

void pcg8100_out(unsigned char port, unsigned char data)
{
	int t;

	if (!use_pcg)
		return;

	switch (port) {
	case 0x02:
	case 0x0c:
	case 0x0d:
	case 0x0e:
	case 0x0f:
		break;
	default:
		return;
	}

	if (pcg_win_samples < 1)
		pcg8100_reset();

	/* The write's place in the window, as the snddrv streams place theirs */
	t = sound_scalebufferpos(pcg_win_clocks);
	if (t > pcg_t)
		pcg_render_to(t);

	switch (port) {
	case 0x02:
		pcg_enable = data & (PCG8100_EN0 | PCG8100_EN1 | PCG8100_EN2);
		break;

	case 0x0c:
	case 0x0d:
	case 0x0e:
		pcg_write_count(&pcg_ch[port - 0x0c], data);
		break;

	case 0x0f:
		if (((data >> 6) & 3) <= 2)
			pcg_write_control(&pcg_ch[(data >> 6) & 3], data);
		break;
	}
}

void pcg8100_update(short *stereo, int frames)
{
	int i, len, x, y, s;

	if (!use_pcg || stereo == NULL || frames <= 0)
		return;
	if (pcg_win_samples < 1)
		pcg8100_reset();

	pcg_render_to(pcg_win_clocks);

	if (frames > pcg_win_samples)
		frames = pcg_win_samples;

	for (i = 0; i < frames; i++) {
		len = pcg_sample_start(i + 1) - pcg_sample_start(i);
		x   = (len > 0) ? (pcg_acc[i] * PCG8100_CH_LEVEL + len / 2) / len : 0;
		y   = pcg_dc_block(x);

		s = stereo[i * 2] + y;
		stereo[i * 2]     = (short)(s > 32767 ? 32767 : s < -32768 ? -32768 : s);
		s = stereo[i * 2 + 1] + y;
		stereo[i * 2 + 1] = (short)(s > 32767 ? 32767 : s < -32768 ? -32768 : s);
	}

	pcg_start_window();
}


/*----------------------------------------------------------------------*/
/* Savestate								*/
/*----------------------------------------------------------------------*/

#define	SID		"PCG "
#define	SID_ACC		"PCGA"

#define	PCG_CH_WORK(n)	\
	{ TYPE_INT,	&pcg_ch[n].rw_mode		},	\
	{ TYPE_INT,	&pcg_ch[n].mode			},	\
	{ TYPE_INT,	&pcg_ch[n].bcd			},	\
	{ TYPE_INT,	&pcg_ch[n].write_phase		},	\
	{ TYPE_INT,	&pcg_ch[n].write_lsb		},	\
	{ TYPE_INT,	&pcg_ch[n].reload		},	\
	{ TYPE_INT,	&pcg_ch[n].pending_reload	},	\
	{ TYPE_INT,	&pcg_ch[n].pending_valid	},	\
	{ TYPE_INT,	&pcg_ch[n].null_count		},	\
	{ TYPE_INT,	&pcg_ch[n].output		},	\
	{ TYPE_INT,	&pcg_ch[n].gate			},	\
	{ TYPE_INT,	&pcg_ch[n].counting		},	\
	{ TYPE_INT,	&pcg_ch[n].remain		},	\
	{ TYPE_INT,	&pcg_ch[n].trigger_pending	},	\
	{ TYPE_INT,	&pcg_ch[n].pulse_state		},	\
	{ TYPE_INT,	&pcg_ch[n].load_pending		},	\
	{ TYPE_INT,	&pcg_ch[n].programmed		}

static	T_SUSPEND_W	suspend_pcg8100_work[]=
{
	PCG_CH_WORK(0),
	PCG_CH_WORK(1),
	PCG_CH_WORK(2),

	{ TYPE_INT,	&pcg_enable		},
	{ TYPE_INT,	&pcg_win_clocks		},
	{ TYPE_INT,	&pcg_win_carry		},
	{ TYPE_INT,	&pcg_win_samples	},
	{ TYPE_INT,	&pcg_t			},
	{ TYPE_INT,	&pcg_sample		},
	{ TYPE_INT,	&pcg_dc_x		},
	{ TYPE_INT,	&pcg_dc_y		},

	{ TYPE_END,	0			},
};

int statesave_pcg8100(void)
{
	if (statesave_table(SID, suspend_pcg8100_work) != STATE_OK)
		return FALSE;
	if (statesave_block(SID_ACC, pcg_acc, sizeof(pcg_acc)) != STATE_OK)
		return FALSE;
	return TRUE;
}

int stateload_pcg8100(void)
{
	if (stateload_table(SID, suspend_pcg8100_work) != STATE_OK
	 || stateload_block(SID_ACC, pcg_acc, sizeof(pcg_acc)) != STATE_OK) {
		/* A state without the PCG-8100 starts it from power-on */
		pcg8100_reset();
		return TRUE;
	}

	if (pcg_win_samples < 1 || pcg_win_samples > PCG_MAX_SAMPLES
	 || pcg_win_clocks < 1 || pcg_t < 0 || pcg_t > pcg_win_clocks
	 || pcg_sample < 0 || pcg_sample >= pcg_win_samples) {
		pcg8100_reset();
		return TRUE;
	}
	pcg_sample_end = pcg_sample_start(pcg_sample + 1);
	return TRUE;
}
