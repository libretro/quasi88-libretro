/************************************************************************/
/*									*/
/* PCG-8100 音声 (8253 compatible PIT, event-driven)			*/
/*									*/
/************************************************************************/

#include <string.h>

#include "quasi88.h"
#include "pcg8100.h"

#include "pc88cpu.h"
#include "intr.h"
#include "memory.h"
#include "suspend.h"

#define	PCG8100_CLOCK		3993600.0

#define	PCG8100_EVT_MAX		512

#define	PCG8100_CH_LEVEL	3584

#define	PCG_MIX_BUDGET		8192

#define	PCG8100_EN0		0x08	/* Port 02h D3 */
#define	PCG8100_EN1		0x40	/* Port 02h D6 */
#define	PCG8100_EN2		0x80	/* Port 02h D7 */

#define	PCG_NO_EVENT		1.0e30
#define	PCG_EPS			1.0e-9


typedef struct {
	int		rw_mode;
	int		mode;
	int		bcd;

	int		write_phase;
	byte		write_lsb;

	unsigned int	reload;
	unsigned int	pending_reload;

	int		pending_valid;
	int		null_count;

	int		output;
	int		gate;
	int		counting;

	double		clocks_to_transition;

	int		trigger_pending;
	int		pulse_state;

	int		load_pending;
	int		programmed;
} PCG8253_CHANNEL;


typedef struct {
	PCG8253_CHANNEL	ch[3];

	byte		output_enable;

	int		programmed;
} PCG8100_STATE;


typedef struct {
	byte		port;
	byte		data;
	double		frac;
	double		pit_time;
	int		mapped;
} PCG8100_EVENT;


static	PCG8100_STATE	pcg;

static	PCG8100_EVENT	pcg_evt[PCG8100_EVT_MAX];
static	int		pcg_evt_r;
static	int		pcg_evt_w;

static	double		pcg_render_pit;
static	int		pcg_mix_budget;
static	byte		pcg_queued_enable;


static unsigned pcg_bcd_to_bin(unsigned v)
{
	unsigned n;

	n  =  (v        & 0x0f);
	n += ((v >>  4) & 0x0f) * 10;
	n += ((v >>  8) & 0x0f) * 100;
	n += ((v >> 12) & 0x0f) * 1000;
	return n;
}

static unsigned pcg_effective_count(const PCG8253_CHANNEL *ch, unsigned reload)
{
	unsigned n;

	if (ch->bcd)
		n = pcg_bcd_to_bin(reload);
	else
		n = reload;

	if (n == 0)
		n = ch->bcd ? 10000 : 65536;

	return n;
}

static void pcg_schedule_mode3_half(PCG8253_CHANNEL *ch)
{
	unsigned n, half;

	n = pcg_effective_count(ch, ch->reload);
	if (n < 2)
		n = 2;

	if (n & 1) {
		if (ch->output)
			half = (n + 1) / 2;
		else
			half = (n - 1) / 2;
		if (half < 1)
			half = 1;
	} else {
		half = n / 2;
	}

	ch->clocks_to_transition = (double)half;
	ch->counting = 1;
}

static void pcg_load_ce(PCG8253_CHANNEL *ch)
{
	unsigned n;

	if (ch->pending_valid) {
		ch->reload = ch->pending_reload;
		ch->pending_valid = 0;
	}

	ch->null_count = 0;
	ch->load_pending = 0;
	ch->counting = 1;

	n = pcg_effective_count(ch, ch->reload);

	switch (ch->mode) {
	case 0:
		ch->output = 0;
		ch->pulse_state = 0;
		ch->clocks_to_transition = (double)n;
		break;

	case 1:
		ch->output = 0;
		ch->pulse_state = 1;
		ch->clocks_to_transition = (double)n;
		break;

	case 2:
		ch->output = 1;
		ch->pulse_state = 0;
		ch->clocks_to_transition = (n > 1) ? (double)(n - 1) : 1.0;
		break;

	case 3:
		ch->output = 1;
		pcg_schedule_mode3_half(ch);
		break;

	case 4:
	case 5:
		ch->output = 1;
		ch->pulse_state = 0;
		ch->clocks_to_transition = (double)n;
		break;

	default:
		ch->counting = 0;
		ch->clocks_to_transition = 0.0;
		break;
	}
}

static void pcg_update_channel(PCG8253_CHANNEL *ch)
{
	unsigned n;

	if (ch->load_pending) {
		if (ch->mode == 1 || ch->mode == 5) {
			if (!ch->trigger_pending && ch->gate == 0) {
				ch->load_pending = 0;
				ch->clocks_to_transition = 0.0;
				return;
			}
			ch->trigger_pending = 0;
		}
		pcg_load_ce(ch);
		return;
	}

	switch (ch->mode) {
	case 0:
		ch->output = 1;
		ch->counting = 0;
		ch->clocks_to_transition = 0.0;
		break;

	case 1:
		ch->output = 1;
		ch->counting = 0;
		ch->pulse_state = 0;
		ch->clocks_to_transition = 0.0;
		break;

	case 2:
		if (ch->pulse_state == 0) {
			ch->output = 0;
			ch->pulse_state = 1;
			ch->clocks_to_transition = 1.0;
		} else {
			if (ch->pending_valid)
				pcg_load_ce(ch);
			else {
				ch->output = 1;
				ch->pulse_state = 0;
				n = pcg_effective_count(ch, ch->reload);
				ch->clocks_to_transition = (n > 1) ? (double)(n - 1) : 1.0;
				ch->counting = 1;
			}
		}
		break;

	case 3:
		ch->output = ch->output ? 0 : 1;
		if (ch->pending_valid) {
			ch->reload = ch->pending_reload;
			ch->pending_valid = 0;
			ch->null_count = 0;
		}
		pcg_schedule_mode3_half(ch);
		break;

	case 4:
	case 5:
		if (ch->pulse_state == 0) {
			ch->output = 0;
			ch->pulse_state = 1;
			ch->clocks_to_transition = 1.0;
			ch->counting = 1;
		} else {
			ch->output = 1;
			ch->pulse_state = 0;
			ch->counting = 0;
			ch->clocks_to_transition = 0.0;
			if (ch->mode == 5 && ch->pending_valid) {
				ch->load_pending = 1;
				ch->trigger_pending = 1;
				ch->clocks_to_transition = 1.0;
			}
		}
		break;

	default:
		ch->counting = 0;
		ch->clocks_to_transition = 0.0;
		break;
	}
}

static void pcg_write_control(PCG8253_CHANNEL *ch, byte data)
{
	int rw, mode;

	rw = (data >> 4) & 3;
	if (rw == 0) {
		/* Counter Latch: 音声経路では未使用 */
		return;
	}

	mode = (data >> 1) & 7;
	if (mode >= 6)
		mode -= 4;

	ch->rw_mode = rw;
	ch->mode = mode;
	ch->bcd = data & 1;
	ch->write_phase = 0;
	ch->write_lsb = 0;
	ch->pending_valid = 0;
	ch->null_count = 1;
	ch->counting = 0;
	ch->load_pending = 0;
	ch->trigger_pending = 0;
	ch->pulse_state = 0;
	ch->clocks_to_transition = 0.0;
	ch->programmed = 1;

	if (mode == 0)
		ch->output = 0;
	else
		ch->output = 1;
}

static void pcg_commit_count(PCG8253_CHANNEL *ch, unsigned value)
{
	ch->pending_reload = value & 0xffff;
	ch->pending_valid = 1;
	ch->null_count = 1;
	ch->programmed = 1;

	switch (ch->mode) {
	case 0:
		ch->output = 0;
		ch->counting = 0;
		ch->load_pending = 1;
		ch->clocks_to_transition = 1.0;
		break;

	case 1:
	case 5:
		ch->trigger_pending = 1;
		ch->load_pending = 1;
		ch->clocks_to_transition = 1.0;
		break;

	case 2:
	case 3:
		if (!ch->counting) {
			ch->load_pending = 1;
			ch->clocks_to_transition = 1.0;
		}
		break;

	case 4:
		ch->load_pending = 1;
		ch->clocks_to_transition = 1.0;
		break;

	default:
		break;
	}
}

static void pcg_write_count(PCG8253_CHANNEL *ch, byte data)
{
	unsigned v;

	if (!ch->programmed && ch->rw_mode == 0)
		return;

	switch (ch->rw_mode) {
	case 1:
		pcg_commit_count(ch, (unsigned)data);
		break;

	case 2:
		pcg_commit_count(ch, ((unsigned)data) << 8);
		break;

	case 3:
		if (ch->write_phase == 0) {
			ch->write_lsb = data;
			ch->write_phase = 1;
		} else {
			v = (unsigned)ch->write_lsb | (((unsigned)data) << 8);
			ch->write_phase = 0;
			pcg_commit_count(ch, v);
		}
		break;

	default:
		break;
	}
}

static void pcg_apply_io(byte port, byte data)
{
	int sc;

	switch (port) {
	case 0x02:
		pcg.output_enable = (byte)(data & (PCG8100_EN0 | PCG8100_EN1 | PCG8100_EN2));
		break;

	case 0x0c:
		pcg_write_count(&pcg.ch[0], data);
		pcg.programmed = 1;
		break;

	case 0x0d:
		pcg_write_count(&pcg.ch[1], data);
		pcg.programmed = 1;
		break;

	case 0x0e:
		pcg_write_count(&pcg.ch[2], data);
		pcg.programmed = 1;
		break;

	case 0x0f:
		sc = (data >> 6) & 3;
		if (sc <= 2) {
			pcg_write_control(&pcg.ch[sc], data);
			pcg.programmed = 1;
		}
		break;

	default:
		break;
	}
}

static int pcg_mix_level(void)
{
	int level = 0;

	if ((pcg.output_enable & PCG8100_EN0) && pcg.ch[0].output)
		level++;
	if ((pcg.output_enable & PCG8100_EN1) && pcg.ch[1].output)
		level++;
	if ((pcg.output_enable & PCG8100_EN2) && pcg.ch[2].output)
		level++;

	return level;
}

static int pcg_channel_pending(const PCG8253_CHANNEL *ch)
{
	return (ch->clocks_to_transition > PCG_EPS);
}

static int pcg_any_pending(void)
{
	return pcg_channel_pending(&pcg.ch[0])
	    || pcg_channel_pending(&pcg.ch[1])
	    || pcg_channel_pending(&pcg.ch[2]);
}

static void pcg_advance_channels(double dt)
{
	int i;

	for (i = 0; i < 3; i++) {
		if (pcg.ch[i].clocks_to_transition > 0.0) {
			pcg.ch[i].clocks_to_transition -= dt;
			if (pcg.ch[i].clocks_to_transition < 0.0)
				pcg.ch[i].clocks_to_transition = 0.0;
		}
	}
}

static double pcg_next_channel_time(double now)
{
	int i;
	double next, t;

	next = PCG_NO_EVENT;
	for (i = 0; i < 3; i++) {
		if (pcg.ch[i].clocks_to_transition > PCG_EPS) {
			t = now + pcg.ch[i].clocks_to_transition;
			if (t < next)
				next = t;
		}
	}
	return next;
}

static double pcg_io_frac(void)
{
	int den;
	double frac;

	den = boost * state_of_vsync;
	if (den < 1)
		den = 1;

	frac = (double)(state_of_cpu + z80main_cpu.state0 + boost_cnt * state_of_vsync)
	     / (double)den;
	if (frac < 0.0)
		frac = 0.0;
	if (frac > 1.0)
		frac = 1.0;
	return frac;
}

static void pcg_evt_clear(void)
{
	pcg_evt_r = 0;
	pcg_evt_w = 0;
}

static void pcg_evt_push(byte port, byte data, double frac)
{
	int next;

	next = (pcg_evt_w + 1) % PCG8100_EVT_MAX;
	if (next == pcg_evt_r)
		return;

	pcg_evt[pcg_evt_w].port = port;
	pcg_evt[pcg_evt_w].data = data;
	pcg_evt[pcg_evt_w].frac = frac;
	pcg_evt[pcg_evt_w].pit_time = 0.0;
	pcg_evt[pcg_evt_w].mapped = 0;
	pcg_evt_w = next;
}

static void pcg_map_io_events(double start, double span)
{
	int i;
	double prev, f;

	prev = -1.0;
	i = pcg_evt_r;
	while (i != pcg_evt_w) {
		f = pcg_evt[i].frac;
		if (prev >= 0.0 && f + 0.02 < prev)
			break;
		pcg_evt[i].pit_time = start + f * span;
		pcg_evt[i].mapped = 1;
		prev = f;
		i = (i + 1) % PCG8100_EVT_MAX;
	}
}

static double pcg_next_io_time(void)
{
	if (pcg_evt_r == pcg_evt_w || !pcg_evt[pcg_evt_r].mapped)
		return PCG_NO_EVENT;
	return pcg_evt[pcg_evt_r].pit_time;
}

static void pcg_apply_due_io(double time)
{
	while (pcg_evt_r != pcg_evt_w) {
		if (!pcg_evt[pcg_evt_r].mapped)
			break;
		if (pcg_evt[pcg_evt_r].pit_time > time + PCG_EPS)
			break;
		pcg_apply_io(pcg_evt[pcg_evt_r].port, pcg_evt[pcg_evt_r].data);
		pcg_evt_r = (pcg_evt_r + 1) % PCG8100_EVT_MAX;
	}
}

static void pcg_fire_due_channels(void)
{
	int i;

	for (i = 0; i < 3; i++) {
		if ((pcg.ch[i].counting || pcg.ch[i].load_pending)
		 && pcg.ch[i].clocks_to_transition <= PCG_EPS) {
			pcg_update_channel(&pcg.ch[i]);
			/* 1 PIT clock 未満の残りは切り上げ、ゼロ進行の無限ループを防ぐ */
			if ((pcg.ch[i].counting || pcg.ch[i].load_pending)
			 && pcg.ch[i].clocks_to_transition < 1.0)
				pcg.ch[i].clocks_to_transition = 1.0;
		}
	}
}

static double pcg_integrate(double t0, double t1)
{
	double time, next, acc, dt, ch_t, io_t;

	acc = 0.0;
	time = t0;

	if (t1 <= t0)
		return 0.0;

	while (time < t1) {
		if (pcg_mix_budget <= 0)
			break;
		pcg_mix_budget--;

		next = t1;
		io_t = pcg_next_io_time();
		if (io_t < next)
			next = io_t;
		ch_t = pcg_next_channel_time(time);
		if (ch_t < next)
			next = ch_t;
		if (next < time)
			next = time;

		dt = next - time;
		if (dt > 0.0) {
			acc += (double)pcg_mix_level() * dt;
			pcg_advance_channels(dt);
			time = next;
		}

		pcg_apply_due_io(time);
		pcg_fire_due_channels();

		if (dt <= 0.0) {
			if (pcg_evt_r != pcg_evt_w
			 && pcg_evt[pcg_evt_r].mapped
			 && pcg_evt[pcg_evt_r].pit_time <= time + PCG_EPS) {
				pcg_apply_io(pcg_evt[pcg_evt_r].port, pcg_evt[pcg_evt_r].data);
				pcg_evt_r = (pcg_evt_r + 1) % PCG8100_EVT_MAX;
			} else {
				time += 1.0;
				if (time > t1)
					time = t1;
			}
		}
	}

	if (time < t1) {
		dt = t1 - time;
		acc += (double)pcg_mix_level() * dt;
		pcg_advance_channels(dt);
		pcg_apply_due_io(t1);
	}

	return acc;
}

static void pcg_add_sample(short *stereo, int pcm)
{
	int samp;

	samp = (int)stereo[0] + pcm;
	if (samp > 32767)
		samp = 32767;
	else if (samp < -32768)
		samp = -32768;
	stereo[0] = (short)samp;

	samp = (int)stereo[1] + pcm;
	if (samp > 32767)
		samp = 32767;
	else if (samp < -32768)
		samp = -32768;
	stereo[1] = (short)samp;
}


void pcg8100_reset(void)
{
	int i;

	memset(&pcg, 0, sizeof(pcg));
	pcg_evt_clear();
	pcg_render_pit = 0.0;
	pcg_queued_enable = 0;

	for (i = 0; i < 3; i++) {
		pcg.ch[i].gate = 1;
		pcg.ch[i].output = 0;
	}
}

void pcg8100_out_at(unsigned char port, unsigned char data, int cpu_state)
{
	byte en;

	(void)cpu_state;

	if (!use_pcg)
		return;

	if (port != 0x02 && port != 0x0c && port != 0x0d
	 && port != 0x0e && port != 0x0f)
		return;

	/* グラフィック用 02h 書き込みは enable ビットが変わったときだけ記録する */
	if (port == 0x02) {
		en = (byte)(data & (PCG8100_EN0 | PCG8100_EN1 | PCG8100_EN2));
		if (en == pcg_queued_enable)
			return;
		pcg_queued_enable = en;
	}

	pcg_evt_push((byte)port, (byte)data, pcg_io_frac());

	if (port != 0x02)
		pcg.programmed = 1;
}

void pcg8100_out(unsigned char port, unsigned char data)
{
	pcg8100_out_at(port, data, 0);
}

void pcg8100_mix(short *stereo, int frames, int sample_rate)
{
	double start, end, span, t0, t1, acc, sample_len;
	int i, pcm, level;
	static int reentry;

	if (!use_pcg || stereo == NULL || frames <= 0)
		return;

	if (sample_rate < 1)
		sample_rate = 44100;

	if (frames > 4096)
		frames = 4096;

	if (reentry)
		return;
	reentry = 1;

	pcg_mix_budget = PCG_MIX_BUDGET;

	/* 可聴時間は PCM バッファ長。CPU の VSYNC 内カウンタは巻き戻るので使わない */
	span = PCG8100_CLOCK * (double)frames / (double)sample_rate;
	start = pcg_render_pit;
	end = start + span;

	pcg_map_io_events(start, span);

	if (!pcg.programmed) {
		pcg_apply_due_io(end);
		pcg_render_pit = end;
		reentry = 0;
		return;
	}

	if (span <= PCG_EPS) {
		pcg_render_pit = end;
		reentry = 0;
		return;
	}

	if (!pcg_any_pending() && pcg_next_io_time() >= PCG_NO_EVENT) {
		level = pcg_mix_level();
		if (level == 0) {
			pcg_apply_due_io(end);
			pcg_render_pit = end;
			reentry = 0;
			return;
		}
		pcm = level * PCG8100_CH_LEVEL;
		for (i = 0; i < frames; i++)
			pcg_add_sample(&stereo[i * 2], pcm);
		pcg_apply_due_io(end);
		pcg_render_pit = end;
		reentry = 0;
		return;
	}

	sample_len = span / (double)frames;
	t0 = start;
	for (i = 0; i < frames; i++) {
		if (pcg_mix_budget <= 0) {
			pcm = pcg_mix_level() * PCG8100_CH_LEVEL;
			for (; i < frames; i++)
				pcg_add_sample(&stereo[i * 2], pcm);
			break;
		}
		if (i == frames - 1)
			t1 = end;
		else
			t1 = start + sample_len * (double)(i + 1);

		acc = pcg_integrate(t0, t1);
		if (sample_len > 0.0)
			pcm = (int)(acc / sample_len * (double)PCG8100_CH_LEVEL + 0.5);
		else
			pcm = 0;
		pcg_add_sample(&stereo[i * 2], pcm);
		t0 = t1;
	}

	pcg_render_pit = end;
	reentry = 0;
}


#define	SID	"PCG "

static	int	sv_ch_rw_mode[3];
static	int	sv_ch_mode[3];
static	int	sv_ch_bcd[3];
static	int	sv_ch_write_phase[3];
static	int	sv_ch_write_lsb[3];
static	int	sv_ch_reload[3];
static	int	sv_ch_pending_reload[3];
static	int	sv_ch_pending_valid[3];
static	int	sv_ch_null_count[3];
static	int	sv_ch_output[3];
static	int	sv_ch_gate[3];
static	int	sv_ch_counting[3];
static	int	sv_ch_clocks_int[3];
static	int	sv_ch_clocks_frac[3];
static	int	sv_ch_trigger_pending[3];
static	int	sv_ch_pulse_state[3];
static	int	sv_ch_load_pending[3];
static	int	sv_ch_programmed[3];
static	int	sv_output_enable;
static	int	sv_programmed;
static	int	sv_queued_enable;


static	T_SUSPEND_W	suspend_pcg8100_work[]=
{
	{ TYPE_INT,	&sv_ch_rw_mode[0],		},
	{ TYPE_INT,	&sv_ch_mode[0],			},
	{ TYPE_INT,	&sv_ch_bcd[0],			},
	{ TYPE_INT,	&sv_ch_write_phase[0],		},
	{ TYPE_INT,	&sv_ch_write_lsb[0],		},
	{ TYPE_INT,	&sv_ch_reload[0],		},
	{ TYPE_INT,	&sv_ch_pending_reload[0],	},
	{ TYPE_INT,	&sv_ch_pending_valid[0],	},
	{ TYPE_INT,	&sv_ch_null_count[0],		},
	{ TYPE_INT,	&sv_ch_output[0],		},
	{ TYPE_INT,	&sv_ch_gate[0],			},
	{ TYPE_INT,	&sv_ch_counting[0],		},
	{ TYPE_INT,	&sv_ch_clocks_int[0],		},
	{ TYPE_INT,	&sv_ch_clocks_frac[0],		},
	{ TYPE_INT,	&sv_ch_trigger_pending[0],	},
	{ TYPE_INT,	&sv_ch_pulse_state[0],		},
	{ TYPE_INT,	&sv_ch_load_pending[0],		},
	{ TYPE_INT,	&sv_ch_programmed[0],		},

	{ TYPE_INT,	&sv_ch_rw_mode[1],		},
	{ TYPE_INT,	&sv_ch_mode[1],			},
	{ TYPE_INT,	&sv_ch_bcd[1],			},
	{ TYPE_INT,	&sv_ch_write_phase[1],		},
	{ TYPE_INT,	&sv_ch_write_lsb[1],		},
	{ TYPE_INT,	&sv_ch_reload[1],		},
	{ TYPE_INT,	&sv_ch_pending_reload[1],	},
	{ TYPE_INT,	&sv_ch_pending_valid[1],	},
	{ TYPE_INT,	&sv_ch_null_count[1],		},
	{ TYPE_INT,	&sv_ch_output[1],		},
	{ TYPE_INT,	&sv_ch_gate[1],			},
	{ TYPE_INT,	&sv_ch_counting[1],		},
	{ TYPE_INT,	&sv_ch_clocks_int[1],		},
	{ TYPE_INT,	&sv_ch_clocks_frac[1],		},
	{ TYPE_INT,	&sv_ch_trigger_pending[1],	},
	{ TYPE_INT,	&sv_ch_pulse_state[1],		},
	{ TYPE_INT,	&sv_ch_load_pending[1],		},
	{ TYPE_INT,	&sv_ch_programmed[1],		},

	{ TYPE_INT,	&sv_ch_rw_mode[2],		},
	{ TYPE_INT,	&sv_ch_mode[2],			},
	{ TYPE_INT,	&sv_ch_bcd[2],			},
	{ TYPE_INT,	&sv_ch_write_phase[2],		},
	{ TYPE_INT,	&sv_ch_write_lsb[2],		},
	{ TYPE_INT,	&sv_ch_reload[2],		},
	{ TYPE_INT,	&sv_ch_pending_reload[2],	},
	{ TYPE_INT,	&sv_ch_pending_valid[2],	},
	{ TYPE_INT,	&sv_ch_null_count[2],		},
	{ TYPE_INT,	&sv_ch_output[2],		},
	{ TYPE_INT,	&sv_ch_gate[2],			},
	{ TYPE_INT,	&sv_ch_counting[2],		},
	{ TYPE_INT,	&sv_ch_clocks_int[2],		},
	{ TYPE_INT,	&sv_ch_clocks_frac[2],		},
	{ TYPE_INT,	&sv_ch_trigger_pending[2],	},
	{ TYPE_INT,	&sv_ch_pulse_state[2],		},
	{ TYPE_INT,	&sv_ch_load_pending[2],		},
	{ TYPE_INT,	&sv_ch_programmed[2],		},

	{ TYPE_INT,	&sv_output_enable,		},
	{ TYPE_INT,	&sv_programmed,			},
	{ TYPE_INT,	&sv_queued_enable,		},

	{ TYPE_END,	0				},
};

static void pcg_flush_io(void)
{
	while (pcg_evt_r != pcg_evt_w) {
		pcg_apply_io(pcg_evt[pcg_evt_r].port, pcg_evt[pcg_evt_r].data);
		pcg_evt_r = (pcg_evt_r + 1) % PCG8100_EVT_MAX;
	}
	pcg_evt_clear();
}

static void pcg_pack_state(void)
{
	int i;
	double clk;
	int clocks_int;

	pcg_flush_io();

	for (i = 0; i < 3; i++) {
		sv_ch_rw_mode[i] = pcg.ch[i].rw_mode;
		sv_ch_mode[i] = pcg.ch[i].mode;
		sv_ch_bcd[i] = pcg.ch[i].bcd;
		sv_ch_write_phase[i] = pcg.ch[i].write_phase;
		sv_ch_write_lsb[i] = (int)pcg.ch[i].write_lsb;
		sv_ch_reload[i] = (int)pcg.ch[i].reload;
		sv_ch_pending_reload[i] = (int)pcg.ch[i].pending_reload;
		sv_ch_pending_valid[i] = pcg.ch[i].pending_valid;
		sv_ch_null_count[i] = pcg.ch[i].null_count;
		sv_ch_output[i] = pcg.ch[i].output;
		sv_ch_gate[i] = pcg.ch[i].gate;
		sv_ch_counting[i] = pcg.ch[i].counting;
		clk = pcg.ch[i].clocks_to_transition;
		if (clk < 0.0)
			clk = 0.0;
		clocks_int = (int)clk;
		sv_ch_clocks_int[i] = clocks_int;
		sv_ch_clocks_frac[i] = (int)((clk - (double)clocks_int) * 1000000.0 + 0.5);
		sv_ch_trigger_pending[i] = pcg.ch[i].trigger_pending;
		sv_ch_pulse_state[i] = pcg.ch[i].pulse_state;
		sv_ch_load_pending[i] = pcg.ch[i].load_pending;
		sv_ch_programmed[i] = pcg.ch[i].programmed;
	}
	sv_output_enable = (int)pcg.output_enable;
	sv_programmed = pcg.programmed;
	sv_queued_enable = (int)pcg_queued_enable;
}

static void pcg_unpack_state(void)
{
	int i;
	double clk;

	for (i = 0; i < 3; i++) {
		pcg.ch[i].rw_mode = sv_ch_rw_mode[i];
		pcg.ch[i].mode = sv_ch_mode[i];
		pcg.ch[i].bcd = sv_ch_bcd[i];
		pcg.ch[i].write_phase = sv_ch_write_phase[i];
		pcg.ch[i].write_lsb = (byte)sv_ch_write_lsb[i];
		pcg.ch[i].reload = (unsigned int)sv_ch_reload[i];
		pcg.ch[i].pending_reload = (unsigned int)sv_ch_pending_reload[i];
		pcg.ch[i].pending_valid = sv_ch_pending_valid[i];
		pcg.ch[i].null_count = sv_ch_null_count[i];
		pcg.ch[i].output = sv_ch_output[i] ? 1 : 0;
		pcg.ch[i].gate = sv_ch_gate[i] ? 1 : 0;
		pcg.ch[i].counting = sv_ch_counting[i];
		clk = (double)sv_ch_clocks_int[i] + (double)sv_ch_clocks_frac[i] / 1000000.0;
		if (clk < 0.0)
			clk = 0.0;
		pcg.ch[i].clocks_to_transition = clk;
		pcg.ch[i].trigger_pending = sv_ch_trigger_pending[i];
		pcg.ch[i].pulse_state = sv_ch_pulse_state[i];
		pcg.ch[i].load_pending = sv_ch_load_pending[i];
		pcg.ch[i].programmed = sv_ch_programmed[i];
	}
	pcg.output_enable = (byte)sv_output_enable;
	pcg.programmed = sv_programmed;
	pcg_queued_enable = (byte)sv_queued_enable;

	pcg_evt_clear();
	pcg_render_pit = 0.0;
}

int statesave_pcg8100(void)
{
	pcg_pack_state();
	if (statesave_table(SID, suspend_pcg8100_work) != STATE_OK)
		return FALSE;
	return TRUE;
}

int stateload_pcg8100(void)
{
	int s;

	s = stateload_table(SID, suspend_pcg8100_work);
	if (s == STATE_OK) {
		pcg_unpack_state();
		return TRUE;
	}

	/* 旧 state に PCG 音声ブロックが無くても本体ロードは継続する */
	pcg8100_reset();
	return TRUE;
}



