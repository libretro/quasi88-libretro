/* Frame contract test for the quasi88 core.
 *
 * Links the core's objects statically and checks, for every retro_run:
 *   - exactly one video frame is pushed;
 *   - every audio mix produced during the run is pushed once, in order
 *     (samples pushed == mixes * samples per frame);
 *   - fps and sample_rate describe a whole number of samples per frame.
 *
 * Scenarios, selected on the command line:
 *   boot  power-on without media: the sub-CPU paces frames
 *   main  main CPU only: VSYNC paces frames
 *   dual  sub-CPU mode 1 with both CPUs stepping: VSYNC and the sub-CPU
 *         load counter both end frames
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

void __real_sound_frame_update(void);

static unsigned mixes;
void __wrap_sound_frame_update(void)
{
   mixes++;
   __real_sound_frame_update();
}

#define WARMUP 40
#define FRAMES 350

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
static const char *scenario = "boot";
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
      case RETRO_ENVIRONMENT_GET_VARIABLE:
      {
         struct retro_variable *var = (struct retro_variable*)data;
         var->value = NULL;
         return false;
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

static size_t audio_batch_cb(const int16_t *data, size_t frames)
{
   cur.samples += (unsigned)frames;
   cur.ahash    = fnv(cur.ahash, (const unsigned char*)data, frames * 4);
   return frames;
}

static void audio_cb(int16_t l, int16_t r) { (void)l; (void)r; }
static void poll_cb(void) { }
static int16_t input_cb(unsigned port, unsigned dev, unsigned idx, unsigned id)
{
   (void)port; (void)dev; (void)idx; (void)id;
   return 0;
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

int main(int argc, char **argv)
{
   struct retro_system_av_info av;
   double spf;
   int    i;
   int    ok = 1;

   if (argc > 1)
      scenario = argv[1];
   if (strcmp(scenario, "boot") && strcmp(scenario, "main") && strcmp(scenario, "dual"))
   {
      printf("usage: %s boot|main|dual\n", argv[0]);
      return 2;
   }

   retro_set_environment(env_cb);
   retro_set_video_refresh(video_cb);
   retro_set_audio_sample(audio_cb);
   retro_set_audio_sample_batch(audio_batch_cb);
   retro_set_input_poll(poll_cb);
   retro_set_input_state(input_cb);
   retro_init();
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

   for (i = 0; i < FRAMES; i++)
      ok &= run_frame(i);

   retro_unload_game();
   retro_deinit();

   printf("%s %s\n", ok ? "PASS" : "FAIL", scenario);
   return ok ? 0 : 1;
}
