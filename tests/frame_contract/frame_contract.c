/* Frame contract and savestate determinism test for the quasi88 core.
 *
 * Links the core's objects statically and checks, for every retro_run:
 *   - exactly one video frame is pushed;
 *   - every audio mix produced during the run is pushed once, in order
 *     (samples pushed == mixes * samples per frame);
 *   - fps and sample_rate describe a whole number of samples per frame.
 * It then checks that replaying from a savestate reproduces video, audio
 * and the per-run mix/VSYNC cadence, both after a single load and with a
 * save+load before every frame.
 *
 * Scenarios, selected on the command line:
 *   boot  power-on without media: the sub-CPU paces frames
 *   main  main CPU only: VSYNC paces frames
 *   dual  sub-CPU mode 1 with both CPUs stepping: VSYNC and the sub-CPU
 *         load counter both end frames
 *   disk  a disk image is inserted (path given as the next argument): its
 *         save file must be created as <name without extension>.srm
 *   tape  a tape image is loaded (path given as the next argument): the
 *         typed load must run one VSYNC per retro_run, with the core
 *         asking the frontend to fast-forward while the tape is read and
 *         handing fast-forward back once it is over
 *   pcg   a program in the main ROM area drives the PCG-8100: bursts of a
 *         1 kHz square must start at a steady spacing, the audio must not
 *         change when a state is saved, or saved and loaded, before every
 *         frame, and squares far above hearing must settle flat
 *   input a pad direction held across frames, then the disk swapper
 *         driven by L + Right: the keyboard matrix after every frame and
 *         the swapper calls must match between a straight run and one
 *         with a save+load before every frame
 *
 * Every case also saves one state into buffers holding different bytes
 * and requires identical results.
 *
 * No content or system files are needed. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libretro.h"

extern int quasi88_info_vsync_count(void);
extern int select_main_cpu;
extern int cpu_timing;
extern int dual_cpu_count;
extern unsigned char key_scan[0x10];
extern unsigned char *main_rom;
extern unsigned char *main_rom_n;

void __real_retro_disks_start(retro_environment_t cb, bool is_first_drive);
void __real_retro_disks_cycle(retro_environment_t cb, bool right);
void __real_retro_disks_set(retro_environment_t cb);

static unsigned swap_starts, swap_cycles, swap_sets;
static unsigned ff_on, ff_off;
static int      ff_state;

int __real_get_drive_ready(int drv);
static const char *scenario = "boot";
/* Without a disk ROM the sub-CPU keeps the FDC busy; report idle drives
 * so the tape case reaches its typed load */
int __wrap_get_drive_ready(int drv)
{
   if (!strcmp(scenario, "tape"))
      return 1;
   return __real_get_drive_ready(drv);
}
void __wrap_retro_disks_start(retro_environment_t cb, bool is_first_drive)
{
   swap_starts++;
   __real_retro_disks_start(cb, is_first_drive);
}
void __wrap_retro_disks_cycle(retro_environment_t cb, bool right)
{
   swap_cycles++;
   __real_retro_disks_cycle(cb, right);
}
void __wrap_retro_disks_set(retro_environment_t cb)
{
   swap_sets++;
   __real_retro_disks_set(cb);
}

void __real_sound_frame_update(void);

static unsigned mixes;
void __wrap_sound_frame_update(void)
{
   mixes++;
   __real_sound_frame_update();
}

#define WARMUP 40
#define TAPE_FRAMES 900
/* Audio is compared from here: the start-up mute is not in the state */
#define PCG_FIRST_COMPARED (40L * 796)
#define SAVE_AT 200
#define REPLAY 150

struct run_rec
{
   unsigned long vhash;
   unsigned long ahash;
   unsigned      samples;
   int           vsyncs;
   unsigned      mixes;
   unsigned      video_calls;
};

static struct run_rec cur;
static struct run_rec straight[REPLAY];
static int input_frame;
static unsigned samples_per_frame;

static unsigned long fnv(unsigned long h, const unsigned char *p, size_t n)
{
   size_t i;
   for (i = 0; i < n; i++)
   {
      h ^= p[i];
      h  = (h * 16777619UL) & 0xffffffffUL;
   }
   return h;
}

static bool env_cb(unsigned cmd, void *data)
{
   switch (cmd)
   {
      case RETRO_ENVIRONMENT_GET_SYSTEM_DIRECTORY:
      case RETRO_ENVIRONMENT_GET_SAVE_DIRECTORY:
      case RETRO_ENVIRONMENT_GET_CORE_ASSETS_DIRECTORY:
         *(const char**)data = ".";
         return true;
      case RETRO_ENVIRONMENT_SET_FASTFORWARDING_OVERRIDE:
      {
         const struct retro_fastforwarding_override *ff =
            (const struct retro_fastforwarding_override*)data;
         if (ff)
         {
            if (ff->fastforward)
               ff_on++;
            else
               ff_off++;
            ff_state = ff->fastforward;
         }
         return true;
      }
      case RETRO_ENVIRONMENT_GET_VARIABLE:
      {
         struct retro_variable *var = (struct retro_variable*)data;
         var->value = NULL;
         if (!strcmp(scenario, "pcg") && !strcmp(var->key, "q88_pcg-8100"))
            var->value = "enabled";
         return var->value != NULL;
      }
      default:
         break;
   }
   return false;
}

static void video_cb(const void *data, unsigned w, unsigned h, size_t pitch)
{
   unsigned y;
   cur.video_calls++;
   if (!data)
      return;
   for (y = 0; y < h; y++)
      cur.vhash = fnv(cur.vhash, (const unsigned char*)data + y * pitch, w * 2);
}

#define PCG_RUNS       400
#define PCG_MAX_SAMPLES (PCG_RUNS * 1600)
static short   *pcg_pcm;
static long     pcg_npcm;

static size_t audio_batch_cb(const int16_t *data, size_t frames)
{
   if (pcg_pcm)
   {
      size_t i;
      for (i = 0; i < frames && pcg_npcm < PCG_MAX_SAMPLES; i++)
         pcg_pcm[pcg_npcm++] = data[i * 2];
   }
   cur.samples += (unsigned)frames;
   cur.ahash    = fnv(cur.ahash, (const unsigned char*)data, frames * 4);
   return frames;
}

static void audio_cb(int16_t l, int16_t r) { (void)l; (void)r; }
static void poll_cb(void) { }
static int16_t input_cb(unsigned port, unsigned dev, unsigned idx, unsigned id)
{
   (void)idx;
   if (strcmp(scenario, "input") || port != 0 || dev != RETRO_DEVICE_JOYPAD)
      return 0;
   switch (id)
   {
      case RETRO_DEVICE_ID_JOYPAD_RIGHT:
         /* held 50..89; tapped 120..124 while L is down */
         return (input_frame >= 50 && input_frame < 90)
             || (input_frame >= 120 && input_frame < 125);
      case RETRO_DEVICE_ID_JOYPAD_L:
         return input_frame >= 110 && input_frame < 140;
      default:
         break;
   }
   return 0;
}

#define INPUT_FRAMES 160

static unsigned char key_trace[2][INPUT_FRAMES][0x10];

static int input_scenario(void)
{
   unsigned starts[2], cycles[2], sets[2];
   size_t   size = retro_serialize_size();
   void    *state = malloc(size);
   void    *tmp   = malloc(size);
   int      pass, bad = 0;

   if (!state || !tmp || !retro_serialize(state, size))
   {
      printf("FAIL input: serialize\n");
      return 0;
   }
   for (pass = 0; pass < 2; pass++)
   {
      if (!retro_unserialize(state, size))
      {
         printf("FAIL input: unserialize\n");
         return 0;
      }
      swap_starts = swap_cycles = swap_sets = 0;
      for (input_frame = 0; input_frame < INPUT_FRAMES; input_frame++)
      {
         if (pass && (!retro_serialize(tmp, size) || !retro_unserialize(tmp, size)))
         {
            printf("FAIL input: serialize round trip at %d\n", input_frame);
            return 0;
         }
         retro_run();
         memcpy(key_trace[pass][input_frame], key_scan, sizeof(key_scan));
      }
      starts[pass] = swap_starts;
      cycles[pass] = swap_cycles;
      sets[pass]   = swap_sets;
   }
   for (input_frame = 0; input_frame < INPUT_FRAMES; input_frame++)
      if (memcmp(key_trace[0][input_frame], key_trace[1][input_frame], sizeof(key_scan)))
      {
         if (!bad)
            printf("FAIL input: keyboard matrix differs from frame %d with a load before every frame\n", input_frame);
         bad++;
      }
   if (starts[0] != starts[1] || cycles[0] != cycles[1] || sets[0] != sets[1])
   {
      printf("FAIL input: disk swapper start/cycle/set %u/%u/%u straight, %u/%u/%u with a load before every frame\n",
            starts[0], cycles[0], sets[0], starts[1], cycles[1], sets[1]);
      bad++;
   }
   if (starts[0] != 1 || cycles[0] != 1 || sets[0] != 1)
   {
      printf("FAIL input: disk swapper start/cycle/set %u/%u/%u, expected 1/1/1\n",
            starts[0], cycles[0], sets[0]);
      bad++;
   }
   free(tmp);
   free(state);
   return bad == 0;
}

static void apply_scenario(int frame)
{
   if (frame < WARMUP)
      return;
   if (!strcmp(scenario, "main"))
      select_main_cpu = 1;
   else if (!strcmp(scenario, "dual"))
   {
      cpu_timing      = 1;
      select_main_cpu = 1;
      dual_cpu_count  = 1000000;
   }
}

static int run_frame(int frame)
{
   int v0;

   apply_scenario(frame);
   memset(&cur, 0, sizeof(cur));
   cur.vhash = cur.ahash = 2166136261UL;
   mixes     = 0;
   v0        = quasi88_info_vsync_count();
   retro_run();
   cur.vsyncs = quasi88_info_vsync_count() - v0;
   cur.mixes  = mixes;

   if (cur.video_calls != 1)
   {
      printf("FAIL %s frame %d: %u video frames pushed\n", scenario, frame, cur.video_calls);
      return 0;
   }
   if (cur.samples != cur.mixes * samples_per_frame)
   {
      printf("FAIL %s frame %d: %u samples pushed for %u mixes of %u\n",
            scenario, frame, cur.samples, cur.mixes, samples_per_frame);
      return 0;
   }
   return 1;
}

static int same_run(const struct run_rec *a, const struct run_rec *b)
{
   return a->vhash == b->vhash && a->ahash == b->ahash && a->samples == b->samples
       && a->vsyncs == b->vsyncs && a->mixes == b->mixes;
}

static int replay(const void *state, size_t size, int load_every_frame)
{
   int   i;
   int   bad = 0;
   void *tmp = malloc(size);

   if (!tmp || !retro_unserialize(state, size))
   {
      printf("FAIL %s: unserialize\n", scenario);
      free(tmp);
      return 0;
   }
   for (i = 0; i < REPLAY; i++)
   {
      if (load_every_frame)
      {
         if (!retro_serialize(tmp, size) || !retro_unserialize(tmp, size))
         {
            printf("FAIL %s: serialize round trip at +%d\n", scenario, i);
            bad++;
            break;
         }
      }
      if (!run_frame(SAVE_AT + i))
         bad++;
      else if (!same_run(&cur, &straight[i]))
      {
         if (bad < 4)
            printf("FAIL %s %s +%d: vsync %d/%d mixes %u/%u video %s audio %s\n",
                  scenario, load_every_frame ? "save/load every frame" : "replay", i,
                  straight[i].vsyncs, cur.vsyncs, straight[i].mixes, cur.mixes,
                  straight[i].vhash == cur.vhash ? "same" : "differs",
                  straight[i].ahash == cur.ahash ? "same" : "differs");
         bad++;
      }
   }
   free(tmp);
   return bad == 0;
}

/* PIT channel 0 in mode 3 at count (bytes 6 and 10); output enable on
 * port 02h switched on and off by CPU delay loops (from byte 13), or left
 * on (bytes 13..16 then JR $) */
static unsigned char pcg_prog[] = {
   0xF3,
   0x3E, 0x36, 0xD3, 0x0F,
   0x3E, 0x9A, 0xD3, 0x0C,
   0x3E, 0x0F, 0xD3, 0x0C,
   0x3E, 0x08, 0xD3, 0x02,
   0x01, 0xD0, 0x07,
   0x0B, 0x78, 0xB1, 0x20, 0xFB,
   0x3E, 0x00, 0xD3, 0x02,
   0x01, 0xD0, 0x07,
   0x0B, 0x78, 0xB1, 0x20, 0xFB,
   0x18, 0xE2
};

static void pcg_load_program(unsigned count, int bursts)
{
   pcg_prog[6]  = (unsigned char)(count & 0xff);
   pcg_prog[10] = (unsigned char)(count >> 8);
   pcg_prog[17] = bursts ? 0x01 : 0x18;	/* JR $ when held on */
   pcg_prog[18] = bursts ? 0xD0 : 0xFE;
   memcpy(main_rom, pcg_prog, sizeof(pcg_prog));
   memcpy(main_rom_n, pcg_prog, sizeof(pcg_prog));
   retro_reset();
}

static int pcg_scenario(void)
{
   static const unsigned ultrasonic[] = { 40, 20, 16, 10, 2 };
   size_t size = retro_serialize_size();
   void  *s0   = malloc(size);
   void  *tmp  = malloc(size);
   short *pass[3];
   long   n[3];
   long   k, last = -1, since = 0, lo = 1L << 30, hi = 0;
   int    p, i, bursts = 0, ok = 1;

   pcg_load_program(3994, 1);
   if (!s0 || !tmp || !retro_serialize(s0, size))
      return 0;
   for (p = 0; p < 3; p++)
   {
      pass[p]  = (short*)malloc(PCG_MAX_SAMPLES * sizeof(short));
      pcg_pcm  = pass[p];
      pcg_npcm = 0;
      retro_unserialize(s0, size);
      for (i = 0; i < PCG_RUNS; i++)
      {
         if (p == 1)
            retro_serialize(tmp, size);
         if (p == 2 && (!retro_serialize(tmp, size) || !retro_unserialize(tmp, size)))
            return 0;
         retro_run();
      }
      n[p] = pcg_npcm;
   }
   pcg_pcm = NULL;

   /* A burst starts at the first rising edge after a quiet stretch */
   for (k = PCG_FIRST_COMPARED + 1; k < n[0]; k++)
   {
      if (pass[0][k] - pass[0][k - 1] > 1000)
      {
         if (since > 300)
         {
            if (last >= 0)
            {
               if (k - last < lo) lo = k - last;
               if (k - last > hi) hi = k - last;
            }
            last = k;
            bursts++;
         }
         since = 0;
      }
      else
         since++;
   }
   if (bursts < 200 || hi - lo > 1)
   {
      printf("FAIL pcg: %d bursts, start spacing %ld..%ld samples\n", bursts, lo, hi);
      ok = 0;
   }

   for (p = 1; p < 3; p++)
   {
      long diff = 0, first = -1;
      for (k = PCG_FIRST_COMPARED; k < n[0] && k < n[p]; k++)
         if (pass[0][k] != pass[p][k])
         {
            if (first < 0)
               first = k;
            diff++;
         }
      if (diff || n[p] != n[0])
      {
         printf("FAIL pcg: %ld samples differ (first at %ld) when a state is %s before every frame\n",
               diff, first, p == 1 ? "saved" : "saved and loaded");
         ok = 0;
      }
      free(pass[p]);
   }
   free(pass[0]);

   for (i = 0; i < (int)(sizeof(ultrasonic) / sizeof(ultrasonic[0])); i++)
   {
      short buf_lo = 32767, buf_hi = -32768;
      short *pcm = (short*)malloc(PCG_MAX_SAMPLES * sizeof(short));

      pcg_load_program(ultrasonic[i], 0);
      pcg_pcm  = pcm;
      pcg_npcm = 0;
      for (k = 0; k < 310; k++)
         retro_run();
      pcg_pcm = NULL;
      for (k = 300 * 796; k < 310 * 796 && k < pcg_npcm; k++)
      {
         if (pcm[k] < buf_lo) buf_lo = pcm[k];
         if (pcm[k] > buf_hi) buf_hi = pcm[k];
      }
      if (buf_lo < -256 || buf_hi > 256)
      {
         printf("FAIL pcg: count %u settles to %d..%d instead of near 0\n",
               ultrasonic[i], buf_lo, buf_hi);
         ok = 0;
      }
      free(pcm);
   }

   free(tmp);
   free(s0);
   return ok;
}

static int state_bytes_stable(void)
{
   size_t         size = retro_serialize_size();
   unsigned char *a    = (unsigned char*)malloc(size);
   unsigned char *b    = (unsigned char*)malloc(size);
   int            ok   = 0;

   if (a && b)
   {
      memset(a, 0x00, size);
      memset(b, 0xa5, size);
      if (!retro_serialize(a, size) || !retro_serialize(b, size))
         printf("FAIL %s: serialize\n", scenario);
      else if (memcmp(a, b, size))
         printf("FAIL %s: a state depends on what its buffer held before\n", scenario);
      else
         ok = 1;
   }
   free(a);
   free(b);
   return ok;
}

static int disk_scenario(const char *image)
{
   char        srm[512];
   const char *base = strrchr(image, '/');
   const char *dot;
   size_t      len;
   FILE       *f;

   base = base ? base + 1 : image;
   dot  = strrchr(base, '.');
   len  = dot ? (size_t)(dot - base) : strlen(base);
   if (len + 6 > sizeof(srm))
      return 0;
   memcpy(srm, "./", 2);
   memcpy(srm + 2, base, len);
   strcpy(srm + 2 + len, ".srm");

   f = fopen(srm, "rb");
   if (!f)
   {
      printf("FAIL disk: %s was not created for %s\n", srm, image);
      return 0;
   }
   fclose(f);
   remove(srm);
   return 1;
}

int main(int argc, char **argv)
{
   struct retro_system_av_info av;
   double spf;
   size_t size;
   void  *state;
   int    i;
   int    ok = 1;

   if (argc > 1)
      scenario = argv[1];
   if ((strcmp(scenario, "boot") && strcmp(scenario, "main") && strcmp(scenario, "dual")
         && strcmp(scenario, "input") && strcmp(scenario, "disk") && strcmp(scenario, "tape")
         && strcmp(scenario, "pcg"))
         || ((!strcmp(scenario, "disk") || !strcmp(scenario, "tape")) && argc < 3))
   {
      printf("usage: %s boot|main|dual|input|pcg|disk <image>|tape <image>\n", argv[0]);
      return 2;
   }

   retro_set_environment(env_cb);
   retro_set_video_refresh(video_cb);
   retro_set_audio_sample(audio_cb);
   retro_set_audio_sample_batch(audio_batch_cb);
   retro_set_input_poll(poll_cb);
   retro_set_input_state(input_cb);
   retro_init();
   if (!strcmp(scenario, "disk"))
   {
      struct retro_game_info info;
      memset(&info, 0, sizeof(info));
      info.path = argv[2];
      if (!retro_load_game(&info))
      {
         printf("FAIL: retro_load_game %s\n", argv[2]);
         return 1;
      }
      for (i = 0; i < 60; i++)
         retro_run();
      ok = disk_scenario(argv[2]) && state_bytes_stable();
      retro_unload_game();
      retro_deinit();
      printf("%s %s %s\n", ok ? "PASS" : "FAIL", scenario, argv[2]);
      return ok ? 0 : 1;
   }
   if (!strcmp(scenario, "tape"))
   {
      struct retro_game_info info;
      memset(&info, 0, sizeof(info));
      info.path = argv[2];
      if (!retro_load_game(&info))
      {
         printf("FAIL: retro_load_game %s\n", argv[2]);
         return 1;
      }
      retro_get_system_av_info(&av);
      samples_per_frame = (unsigned)(av.timing.sample_rate / av.timing.fps + 0.5);
      for (i = 0; i < TAPE_FRAMES; i++)
      {
         ok &= run_frame(i);
         if (cur.mixes > 1)
         {
            printf("FAIL tape frame %d: %u VSYNCs of audio mixed in one retro_run\n", i, cur.mixes);
            ok = 0;
            break;
         }
      }
      if (!ff_on || !ff_off)
      {
         printf("FAIL tape: fast-forward requested %u times, released %u times\n", ff_on, ff_off);
         ok = 0;
      }
      ok &= state_bytes_stable();
      retro_unload_game();
      if (ff_state)
      {
         printf("FAIL tape: fast-forward still held after unload\n");
         ok = 0;
      }
      retro_deinit();
      printf("%s %s %s\n", ok ? "PASS" : "FAIL", scenario, argv[2]);
      return ok ? 0 : 1;
   }
   if (!retro_load_game(NULL))
   {
      printf("FAIL: retro_load_game\n");
      return 1;
   }

   retro_get_system_av_info(&av);
   spf               = av.timing.sample_rate / av.timing.fps;
   samples_per_frame = (unsigned)(spf + 0.5);
   if (spf - samples_per_frame > 1e-6 || samples_per_frame - spf > 1e-6)
   {
      printf("FAIL: sample_rate %.3f / fps %.3f = %.4f samples per frame\n",
            av.timing.sample_rate, av.timing.fps, spf);
      ok = 0;
   }

   if (!strcmp(scenario, "pcg"))
   {
      ok &= pcg_scenario();
      ok &= state_bytes_stable();
      retro_unload_game();
      retro_deinit();
      printf("%s %s\n", ok ? "PASS" : "FAIL", scenario);
      return ok ? 0 : 1;
   }

   if (!strcmp(scenario, "input"))
   {
      ok &= input_scenario();
      ok &= state_bytes_stable();
      retro_unload_game();
      retro_deinit();
      printf("%s %s\n", ok ? "PASS" : "FAIL", scenario);
      return ok ? 0 : 1;
   }

   for (i = 0; i < SAVE_AT; i++)
      ok &= run_frame(i);
   ok &= state_bytes_stable();

   size  = retro_serialize_size();
   state = malloc(size);
   if (!state || !retro_serialize(state, size))
   {
      printf("FAIL %s: serialize\n", scenario);
      return 1;
   }
   for (i = 0; i < REPLAY; i++)
   {
      ok &= run_frame(SAVE_AT + i);
      straight[i] = cur;
   }

   ok &= replay(state, size, 0);
   ok &= replay(state, size, 1);

   free(state);
   retro_unload_game();
   retro_deinit();

   printf("%s %s\n", ok ? "PASS" : "FAIL", scenario);
   return ok ? 0 : 1;
}
