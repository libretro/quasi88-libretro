#include <ctype.h>
#include <stdarg.h>
#include <string.h>

#include <libretro.h>
#include <file/file_path.h>
#include <streams/file_stream.h>
#include <string/stdstring.h>

#ifdef _MSC_VER
#include <compat/msvc.h>
#endif

#include "quasi88.h"
#include "initval.h"
#include "pc88main.h"
#include "pc88sub.h"
#include "memory.h"
#include "font.h"
#include "emu.h"
#include "drive.h"
#include "event.h"
#include "keyboard.h"
#include "snddrv.h"
#include "screen.h"
#include "z80.h"
#include "intr.h"
#include "fdc.h"
#include "soundbd.h"
#include "pc88cpu.h"
#include "pseudo_bios.h"
#include "disks.h"
#include "libretro_core_options.h"
static bool libretro_supports_option_categories = false;

#include "libretro-file.h"
#include "suspend.h"

#define INT16 int16_t
#include "../snddrv/src/sound.h"
INT16 *finalmix;
int samples_this_frame;

/* Every mix produced during one retro_run, in order (stereo frames) */
#define AUDIO_BUF_FRAMES 44100
static INT16 audio_buf[AUDIO_BUF_FRAMES * 2];
static unsigned audio_buf_frames;

#include "filename.h"
char *save_path = NULL;
bool save_to_disk_image = false;

#define FRAMES_BEFORE_AUDIO 30

/* libretro callbacks */
static retro_audio_sample_t audio_cb;
static retro_audio_sample_batch_t audio_batch_cb;
static retro_environment_t environ_cb;
static retro_input_poll_t input_poll_cb;
static retro_input_state_t input_state_cb;
static retro_log_printf_t log_cb;
static retro_set_rumble_state_t rumble_cb;
static retro_video_refresh_t video_cb;

#define RETRO_MEMORY_TYPE_SHIFT         8
#define RETRO_MEMORY_SUBCLASS(base, id) (((id + 1) << RETRO_DEVICE_TYPE_SHIFT) | base)

#define RETRO_MEMORY_PC88_SYSTEM_RAM    (RETRO_MEMORY_SUBCLASS(RETRO_MEMORY_SYSTEM_RAM, 0))
#define RETRO_MEMORY_PC88_VIDEO_RAM     (RETRO_MEMORY_SUBCLASS(RETRO_MEMORY_VIDEO_RAM, 0))

static const struct retro_subsystem_memory_info pc88_memory[] = {
    { "ram",  RETRO_MEMORY_PC88_SYSTEM_RAM },
    { "vram", RETRO_MEMORY_PC88_VIDEO_RAM },
};

static const struct retro_subsystem_rom_info pc88_disk[] = {
   { "Disk 1", "d88", true, false, true, pc88_memory, 1 },
   { "Disk 2", "d88", true, false, true, pc88_memory, 1 },
   { "Disk 3", "d88", true, false, true, pc88_memory, 1 },
   { "Disk 4", "d88", true, false, true, pc88_memory, 1 },
   { "Disk 5", "d88", true, false, true, pc88_memory, 1 },
   { "Disk 6", "d88", true, false, true, pc88_memory, 1 },
   { NULL }
};

static const struct retro_subsystem_info subsystems[] = {
   { "2-Disk Game", "pc88_2_disk", pc88_disk, 2, 0x0101 },
   { "3-Disk Game", "pc88_3_disk", pc88_disk, 3, 0x0102 },
   { "4-Disk Game", "pc88_4_disk", pc88_disk, 4, 0x0103 },
   { "5-Disk Game", "pc88_5_disk", pc88_disk, 5, 0x0104 },
   { "6-Disk Game", "pc88_6_disk", pc88_disk, 6, 0x0105 },
   { NULL }
};

static const struct retro_controller_description port[] = {
   { "Retro Joypad",   RETRO_DEVICE_JOYPAD },
   { "Retro Keyboard", RETRO_DEVICE_KEYBOARD },
   { 0 },
};

static const struct retro_controller_info ports[] = {
   { port, 2 },
   { port, 2 },
   { NULL, 0 },
};

enum 
{
   N88_ROM,  EXT0_ROM, EXT1_ROM,  EXT2_ROM, EXT3_ROM,  N_ROM,     SUB_ROM,
   KNJ1_ROM, KNJ2_ROM, JISHO_ROM, FONT_ROM, FONT2_ROM, FONT3_ROM, ROM_END
};
const char *bios_filenames[ROM_END][4] = 
{
  { "N88.ROM",      "n88.rom",      "",           ""           },
  { "N88EXT0.ROM",  "n88ext0.rom",  "N88_0.ROM",  "n88_0.rom"  },
  { "N88EXT1.ROM",  "n88ext1.rom",  "N88_1.ROM",  "n88_1.rom"  },
  { "N88EXT2.ROM",  "n88ext2.rom",  "N88_2.ROM",  "n88_2.rom"  },
  { "N88EXT3.ROM",  "n88ext3.rom",  "N88_3.ROM",  "n88_3.rom"  },
  { "N88N.ROM",     "n88n.rom",     "N80.ROM",    "n80.rom"    },
  { "N88SUB.ROM",   "n88sub.rom",   "DISK.ROM",   "disk.rom"   },
  { "N88KNJ1.ROM",  "n88knj1.rom",  "KANJI1.ROM", "kanji1.rom" },
  { "N88KNJ2.ROM",  "n88knj2.rom",  "KANJI2.ROM", "kanji2.rom" },
  { "N88JISHO.ROM", "n88jisho.rom", "JISYO.ROM",  "jisyo.rom"  },
  { "FONT.ROM",     "font.rom",     "",           ""           },
  { "FONT2.ROM",    "font2.rom",    "",           ""           },
  { "FONT3.ROM",    "font3.rom",    "",           ""           }
};

static uint32_t  frames                         = 0;
static bool     *key_buffer                     = NULL;
static bool     *pad_buffer                     = NULL;
static bool      rumble_enabled                 = true;
static char      download_dir[OSD_MAX_FILENAME] = { '\0' };
static char      system_dir[OSD_MAX_FILENAME]   = { '\0' };

static void handle_key(uint8_t key, uint16_t retro_key)
{
   bool key_on = input_state_cb(0, RETRO_DEVICE_KEYBOARD, 0, retro_key);
   
   if (!pad_buffer[key])
   {
      if (!key_buffer[key] && key_on)
      {
         quasi88_key(key, 1);
         key_buffer[key] = true;
      }
      else if (key_buffer[key] && !key_on)
      {
         quasi88_key(key, 0);
         key_buffer[key] = false;
      }
   }
}

static void handle_pad(uint8_t key, uint16_t retro_button, uint8_t pad)
{
   bool button_on = input_state_cb(pad, RETRO_DEVICE_JOYPAD, 0, retro_button);
   
   if (!key_buffer[key])
   {
      if (!pad_buffer[key] && button_on)
      {
         quasi88_key(key, 1);
         pad_buffer[key] = true;
      }
      else if (pad_buffer[key] && !button_on)
      {
         quasi88_key(key, 0);
         pad_buffer[key] = false;
      }
   }
}

/* A game on tape is loaded from the BASIC prompt, as on the machine: by the
 * commands its file name gives in braces, as in "{V1 mode, MON R G8F00}", or
 * else by loading the BASIC program on it and running that. */
enum autotype_kind { AUTOTYPE_LINE, AUTOTYPE_KEY, AUTOTYPE_CTRL };

struct autotype_step
{
   enum autotype_kind kind;
   char text[32];
   bool reads_tape;
};

#define AUTOTYPE_MAX_STEPS   16
#define AUTOTYPE_BOOT_FRAMES 240
#define AUTOTYPE_KEY_FRAMES  3
#define AUTOTYPE_STEP_FRAMES 30
/* Machine frames a tape can stand still and still be loading: between blocks
 * a T88 tape holds timed silences */
#define TAPE_IDLE_FRAMES     330
/* Machine frames the motor can stop between blocks within one load */
#define MOTOR_IDLE_FRAMES    120
/* Frames run for each one shown while the tape is being read, so that a
 * load keeps its timing but takes seconds rather than minutes */
#define TAPE_TURBO_FRAMES    8

static struct autotype_step autotype_steps[AUTOTYPE_MAX_STEPS];
static int  autotype_count       = 0;
static int  autotype_step        = 0;
static int  autotype_char        = 0;
static int  autotype_wait        = 0;
/* Frames to wait once the key being typed is let go */
static int  autotype_pause       = 0;
static int  autotype_shift       = 0;
static int  autotype_held        = -1;
static bool autotype_tape        = false;
static long tape_last_pos        = -1;
static int  tape_still           = 0;
static int  motor_still          = 0;
/* The machine a file name's braces ask for: a BASIC mode and a clock in MHz */
static int  brace_basic          = -1;
static int  brace_clock          = 0;
static bool autotype_files_asked = false;
/* Whether the plan starts at the BASIC prompt, where N88-BASIC first asks
 * how many files to open */
static bool autotype_at_prompt   = false;
static char tape_path[OSD_MAX_FILENAME] = { '\0' };

static void autotype_add(enum autotype_kind kind, const char *text, bool reads_tape)
{
   struct autotype_step *step;

   if (autotype_count >= AUTOTYPE_MAX_STEPS)
      return;
   step = &autotype_steps[autotype_count++];
   step->kind = kind;
   strlcpy(step->text, text, sizeof(step->text));
   step->reads_tape = reads_tape;
}

static bool word_is(const char *word, const char *wanted)
{
   return string_is_equal_noncase(word, wanted);
}

static bool is_address(const char *word)
{
   size_t i;

   if (toupper((unsigned char)word[0]) != 'G' || !word[1])
      return false;
   for (i = 1; word[i]; i++)
      if (!isxdigit((unsigned char)word[i]))
         return false;
   return true;
}

static const char *after_prefix(const char *word, const char *prefix)
{
   for (; *prefix; word++, prefix++)
      if (tolower((unsigned char)*word) != tolower((unsigned char)*prefix))
         return NULL;
   return word;
}

/* An answer the game asks for as it starts: "pass=AHONOOH" or a number */
static const char *answer_in(const char *word)
{
   static const char *names[] = { "pass=", "password=", "Number=" };
   const char *value;
   size_t i;

   for (i = 0; i < sizeof(names) / sizeof(names[0]); i++)
      if ((value = after_prefix(word, names[i])) && *value)
         return value;
   for (i = 0; word[i]; i++)
      if (!isdigit((unsigned char)word[i]))
         return NULL;
   return i >= 4 ? word : NULL;
}

/* Words in braces that are commands rather than a file to run */
static bool is_command(const char *word)
{
   return word_is(word, "MON") || word_is(word, "RUN") || word_is(word, "R") || word_is(word, "L") ||
          word_is(word, "RDATA") || word_is(word, "LOAD") || word_is(word, "Ctrl-B") ||
          word_is(word, "Ctrl+B") || word_is(word, "press") || word_is(word, "F5") || is_address(word);
}

/* Reads the loading instructions from a file name. A tape with none is
 * loaded as BASIC; a disk with none starts itself. */
static void autotype_plan(const char *path, bool tape)
{
   char instructions[256] = { '\0' };
   char *words[64];
   int count = 0;
   int i;
   bool ran = false;
   bool answering = false;
   const char *open  = strchr(path_basename(path), '{');
   const char *close = open ? strchr(open, '}') : NULL;

   autotype_count     = 0;
   autotype_at_prompt = tape;
   brace_basic        = -1;
   brace_clock        = 0;

   if (open && close && close - open - 1 < (int)sizeof(instructions))
   {
      char *c = instructions;

      memcpy(instructions, open + 1, close - open - 1);
      while (*c && count < 64)
      {
         while (*c == ',' || *c == ' ')
            *c++ = '\0';
         if (!*c)
            break;
         words[count++] = c;
         while (*c && *c != ',' && *c != ' ')
            c++;
      }
   }

   for (i = 0; i < count; i++)
   {
      const char *word = words[i];
      const char *next = i + 1 < count ? words[i + 1] : "";

      if (word_is(next, "mode"))
      {
         if (word_is(word, "N") || word_is(word, "N80"))
            brace_basic = BASIC_N;
         else if (word_is(word, "V1") || word_is(word, "V1S"))
            brace_basic = BASIC_V1S;
         else if (word_is(word, "V1H"))
            brace_basic = BASIC_V1H;
         else if (word_is(word, "V2"))
            brace_basic = BASIC_V2;
         i++;
      }
      else if (word_is(word, "1MHz"))
         brace_clock = 1;
      else if (word_is(word, "4MHz"))
         brace_clock = 4;
      else if (word_is(word, "8MHz"))
         brace_clock = 8;
      /* Anything after a program is started would be typed into it */
      else if (ran)
         continue;
      /* The words after an answer are the game's next questions' answers */
      else if (!tape && (answer_in(word) || (answering && !is_command(word))))
      {
         autotype_add(AUTOTYPE_LINE, answer_in(word) ? answer_in(word) : word, false);
         answering = true;
      }
      else if (word_is(word, "LOAD") && *next && !word_is(next, "CAS") && !is_command(next))
      {
         char line[sizeof(autotype_steps[0].text)];

         snprintf(line, sizeof(line), "RUN\"%s\"", next);
         autotype_add(AUTOTYPE_LINE, line, false);
         autotype_at_prompt |= autotype_count == 1;
         ran = true;
         i++;
      }
      else if (word_is(word, "RUN") && *next && !is_command(next))
      {
         char line[sizeof(autotype_steps[0].text)];

         snprintf(line, sizeof(line), "RUN\"%s\"", next);
         autotype_add(AUTOTYPE_LINE, line, false);
         autotype_at_prompt |= autotype_count == 1;
         ran = true;
         i++;
      }
      else if (word_is(word, "RUN"))
      {
         autotype_add(AUTOTYPE_LINE, word, false);
         autotype_at_prompt |= autotype_count == 1;
         ran = true;
      }
      else if (word_is(word, "MON") || is_address(word))
         autotype_add(AUTOTYPE_LINE, word, false);
      else if (word_is(word, "R") || word_is(word, "L") || word_is(word, "RDATA"))
         autotype_add(AUTOTYPE_LINE, word, true);
      else if (word_is(word, "LOAD") && word_is(next, "CAS"))
      {
         autotype_add(AUTOTYPE_LINE, "LOAD\"CAS:\"", true);
         i++;
      }
      else if (word_is(word, "Ctrl-B") || word_is(word, "Ctrl+B"))
         autotype_add(AUTOTYPE_CTRL, "B", false);
      else if (word_is(word, "press") && strlen(next) == 1)
      {
         autotype_add(AUTOTYPE_KEY, next, false);
         i++;
      }
      else if (word_is(word, "F5"))
         autotype_add(AUTOTYPE_KEY, "\x05", false);
   }

   if (!tape)
      return;
   if (autotype_count == 0)
      autotype_add(AUTOTYPE_LINE, "LOAD\"CAS:\"", true);
   /* A BASIC program loaded last is there to be run */
   if (string_is_equal(autotype_steps[autotype_count - 1].text, "LOAD\"CAS:\""))
      autotype_add(AUTOTYPE_LINE, "RUN", false);
}

static void autotype_start(void)
{
   /* N88-BASIC first asks how many files to open; N-BASIC goes straight to Ok */
   autotype_files_asked = autotype_at_prompt && boot_basic != BASIC_N;
   autotype_step       = 0;
   autotype_char       = 0;
   autotype_wait       = AUTOTYPE_BOOT_FRAMES;
   autotype_pause      = 0;
   autotype_held       = -1;
   autotype_shift      = 0;
   autotype_tape       = false;
   tape_last_pos       = -1;
   tape_still          = TAPE_IDLE_FRAMES;
   motor_still         = MOTOR_IDLE_FRAMES;
}

/* Counts the machine frames since the tape last moved */
static void tape_tick(void)
{
   long cur, end;

   if (!tape_path[0])
      return;
   if (sys_ctrl & 0x08)
      motor_still = 0;
   else if (motor_still < MOTOR_IDLE_FRAMES)
      motor_still++;
   sio_tape_pos(&cur, &end);
   /* A T88 gap is timed with the tape standing still */
   if (cur != tape_last_pos || sio_tape_in_gap())
   {
      tape_last_pos = cur;
      tape_still    = 0;
   }
   else if (tape_still < TAPE_IDLE_FRAMES)
      tape_still++;
}

/* Whether a program is reading the tape: its motor has turned and the tape
 * has moved lately. A loader stops the motor between blocks. */
static bool tape_loading(void)
{
   return tape_path[0] && motor_still < MOTOR_IDLE_FRAMES && tape_still < TAPE_IDLE_FRAMES;
}

/* The key that types a character, and whether it needs shift */
static int key_for(char c, bool *shift)
{
   *shift = false;
   if (c == '\x05')
      return KEY88_F5;
   if (c == '"')
   {
      *shift = true;
      return KEY88_2;
   }
   if (c >= 'a' && c <= 'z')
      return KEY88_A + (c - 'a');
   *shift = c >= 'A' && c <= 'Z';
   return (unsigned char)c;
}

static void release_typed_key(void)
{
   if (autotype_held >= 0)
      quasi88_key(autotype_held, 0);
   if (autotype_shift)
      quasi88_key(autotype_shift, 0);
   autotype_held  = -1;
   autotype_shift = 0;
}

static void handle_autotype(void)
{
   const struct autotype_step *step;
   char c;
   bool shift;

   if (autotype_wait > 0)
   {
      autotype_wait--;
      return;
   }
   if (autotype_held >= 0)
   {
      release_typed_key();
      autotype_wait  = AUTOTYPE_KEY_FRAMES + autotype_pause;
      autotype_pause = 0;
      return;
   }
   if (autotype_step >= autotype_count)
      return;
   /* Nothing is typed while the tape is being read */
   if (tape_loading())
      return;

   if (autotype_files_asked)
   {
      autotype_files_asked = false;
      autotype_held = KEY88_RETURN;
      quasi88_key(KEY88_RETURN, 1);
      autotype_wait  = AUTOTYPE_KEY_FRAMES;
      autotype_pause = 2 * AUTOTYPE_STEP_FRAMES;
      return;
   }

   step = &autotype_steps[autotype_step];

   /* A read is over once nothing is reading the tape */
   if (autotype_tape)
   {
      autotype_tape = false;
      autotype_step++;
      autotype_char = 0;
      autotype_wait = AUTOTYPE_STEP_FRAMES;
      return;
   }

   if (step->kind == AUTOTYPE_CTRL || step->kind == AUTOTYPE_KEY)
   {
      if (step->kind == AUTOTYPE_CTRL)
      {
         autotype_shift = KEY88_CTRL;
         quasi88_key(KEY88_CTRL, 1);
      }
      autotype_held = key_for(step->text[0], &shift);
      quasi88_key(autotype_held, 1);
      autotype_step++;
      autotype_wait = AUTOTYPE_KEY_FRAMES;
      if (autotype_step < autotype_count)
         autotype_pause = AUTOTYPE_STEP_FRAMES;
      return;
   }

   c = step->text[autotype_char];
   if (c)
   {
      autotype_char++;
      autotype_held = key_for(c, &shift);
      if (shift)
      {
         autotype_shift = KEY88_SHIFT;
         quasi88_key(KEY88_SHIFT, 1);
      }
      quasi88_key(autotype_held, 1);
      autotype_wait = AUTOTYPE_KEY_FRAMES;
      return;
   }

   /* The end of a line */
   autotype_held = KEY88_RETURN;
   quasi88_key(KEY88_RETURN, 1);
   autotype_wait = AUTOTYPE_KEY_FRAMES;
   if (step->reads_tape)
   {
      autotype_tape = true;
      tape_still    = 0;
      motor_still   = 0;
      /* The command starts the motor once it is entered */
      autotype_pause = AUTOTYPE_STEP_FRAMES;
   }
   else
   {
      autotype_step++;
      autotype_char  = 0;
      autotype_pause = AUTOTYPE_STEP_FRAMES;
   }
}

/* What a state keeps of the typing and the tape watch, so that run-ahead and
 * rewind take them back with the machine */
struct autotype_state
{
   char    magic[4];
   int32_t step, chr, wait, pause, shift, held, files_asked, tape;
   int32_t at_prompt;
   int32_t tape_still, motor_still, tape_last_pos;
};

#define AUTOTYPE_STATE_MAGIC "QATS"

static void autotype_save(struct autotype_state *out)
{
   memcpy(out->magic, AUTOTYPE_STATE_MAGIC, 4);
   out->step          = autotype_step;
   out->chr           = autotype_char;
   out->wait          = autotype_wait;
   out->pause         = autotype_pause;
   out->shift         = autotype_shift;
   out->held          = autotype_held;
   out->files_asked   = autotype_files_asked;
   out->at_prompt     = autotype_at_prompt;
   out->tape          = autotype_tape;
   out->tape_still    = tape_still;
   out->motor_still   = motor_still;
   out->tape_last_pos = (int32_t)tape_last_pos;
}

static void autotype_load(const struct autotype_state *in)
{
   if (memcmp(in->magic, AUTOTYPE_STATE_MAGIC, 4) != 0)
      return;
   autotype_step        = in->step;
   autotype_char        = in->chr;
   autotype_wait        = in->wait;
   autotype_pause       = in->pause;
   autotype_shift       = in->shift;
   autotype_held        = in->held;
   autotype_files_asked = in->files_asked != 0;
   autotype_at_prompt   = in->at_prompt != 0;
   autotype_tape        = in->tape != 0;
   tape_still           = in->tape_still;
   motor_still          = in->motor_still;
   tape_last_pos        = in->tape_last_pos;
   /* Loading the machine released the key being typed */
   if (autotype_shift)
      quasi88_key(autotype_shift, 1);
   if (autotype_held >= 0)
      quasi88_key(autotype_held, 1);
}

static bool is_tape(const char *path)
{
   const char *ext = path_get_extension(path);
   return ext && (string_is_equal_noncase(ext, "t88") || string_is_equal_noncase(ext, "cmt"));
}

static void apply_braces(void)
{
   if (brace_basic >= 0)
      boot_basic = brace_basic;
   if (brace_clock == 1)
   {
      boot_clock_4mhz = CLOCK_4MHZ;
      cpu_clock_mhz   = CONST_4MHZ_CLOCK * 0.25;
   }
   else if (brace_clock == 4)
   {
      boot_clock_4mhz = CLOCK_4MHZ;
      cpu_clock_mhz   = CONST_4MHZ_CLOCK;
   }
   else if (brace_clock == 8)
   {
      boot_clock_4mhz = CLOCK_8MHZ;
      cpu_clock_mhz   = CONST_8MHZ_CLOCK;
   }
}

/* Disk swapper button state, kept apart from the emulated key state so
   that a savestate load (which releases every emulated key) leaves it alone */
static bool swap_drive_held[2];
static bool swap_left_held;
static bool swap_right_held;

static bool handle_disk_swap(bool is_first_drive, unsigned button)
{
   bool *held = &swap_drive_held[is_first_drive ? 0 : 1];

   if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, button))
   {
      bool right = input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT) != 0;
      bool left  = input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT) != 0;

      /* On press, start swapper */
      if (!*held)
      {
         retro_disks_start(environ_cb, is_first_drive);
         *held = true;
      }
      else if (right && !swap_right_held)
      {
         retro_disks_cycle(environ_cb, true);
         swap_right_held = true;
      }
      else if (left && !swap_left_held)
      {
         retro_disks_cycle(environ_cb, false);
         swap_left_held = true;
      }
      else if (!right && !left)
      {
         swap_left_held  = false;
         swap_right_held = false;
      }

      return true;
   }
   else if (*held)
   {
      /* On release, set the new disk */
      *held = false;
      retro_disks_set(environ_cb);

      return true;
   }

   return false;
}

static void handle_input(void)
{
   uint8_t i;
   
   input_poll_cb();

   /* Ignore other input while swapping disks */
   if (handle_disk_swap(true, RETRO_DEVICE_ID_JOYPAD_L) || handle_disk_swap(false, RETRO_DEVICE_ID_JOYPAD_R))
      return;

   /* Simple default remappings for joypad, these are temporary and a bit arbitrary */
   handle_pad(KEY88_KP_8,    RETRO_DEVICE_ID_JOYPAD_UP,     0);
   handle_pad(KEY88_KP_2,    RETRO_DEVICE_ID_JOYPAD_DOWN,   0);
   handle_pad(KEY88_KP_4,    RETRO_DEVICE_ID_JOYPAD_LEFT,   0);
   handle_pad(KEY88_KP_6,    RETRO_DEVICE_ID_JOYPAD_RIGHT,  0);
   handle_pad(KEY88_X,       RETRO_DEVICE_ID_JOYPAD_A,      0);
   handle_pad(KEY88_Z,       RETRO_DEVICE_ID_JOYPAD_B,      0);
   handle_pad(KEY88_SHIFTL,  RETRO_DEVICE_ID_JOYPAD_X,      0);
   handle_pad(KEY88_SPACE,   RETRO_DEVICE_ID_JOYPAD_Y,      0);
   handle_pad(KEY88_RETURN,  RETRO_DEVICE_ID_JOYPAD_START,  0);
   handle_pad(KEY88_RETURNL, RETRO_DEVICE_ID_JOYPAD_START,  0);
   handle_pad(KEY88_RETURNR, RETRO_DEVICE_ID_JOYPAD_START,  0);
   handle_pad(KEY88_I,       RETRO_DEVICE_ID_JOYPAD_SELECT, 0);

   handle_pad(KEY88_R,      RETRO_DEVICE_ID_JOYPAD_UP,     1);
   handle_pad(KEY88_F,      RETRO_DEVICE_ID_JOYPAD_DOWN,   1);
   handle_pad(KEY88_D,      RETRO_DEVICE_ID_JOYPAD_LEFT,   1);
   handle_pad(KEY88_G,      RETRO_DEVICE_ID_JOYPAD_RIGHT,  1);
   handle_pad(KEY88_TAB,    RETRO_DEVICE_ID_JOYPAD_A,      1);
   handle_pad(KEY88_Q,      RETRO_DEVICE_ID_JOYPAD_B,      1);
   
   /* Basics, numbers */
   for (i = 0; i < 64; i++)
      handle_key(i, i);
   for (i = 0; i < 6; i++)
      handle_key(KEY88_BRACKETLEFT + i, RETROK_LEFTBRACKET + i);
   for (i = 0; i < 4; i++)
      handle_key(KEY88_BRACELEFT + i, RETROK_LEFTBRACE + i);
   handle_key(KEY88_RETURN,      RETROK_RETURN);
   handle_key(KEY88_HOME,        RETROK_HOME);
   handle_key(KEY88_UP,          RETROK_UP);
   handle_key(KEY88_RIGHT,       RETROK_RIGHT);
   handle_key(KEY88_INS_DEL,     RETROK_BACKSPACE);
   handle_key(KEY88_GRAPH,       RETROK_LALT);
   handle_key(KEY88_KANA,        RETROK_LSUPER);
   handle_key(KEY88_SHIFT,       RETROK_RSHIFT);
   handle_key(KEY88_CTRL,        RETROK_RCTRL);
   handle_key(KEY88_STOP,        RETROK_BREAK);
   handle_key(KEY88_ESC,         RETROK_ESCAPE);
   handle_key(KEY88_TAB,         RETROK_TAB);
   handle_key(KEY88_DOWN,        RETROK_DOWN);
   handle_key(KEY88_LEFT,        RETROK_LEFT);
   handle_key(KEY88_HELP,        RETROK_END);
   handle_key(KEY88_COPY,        RETROK_PRINT);
   handle_key(KEY88_CAPS,        RETROK_CAPSLOCK);
   handle_key(KEY88_ROLLUP,      RETROK_PAGEUP);
   handle_key(KEY88_ROLLDOWN,    RETROK_PAGEDOWN);
   handle_key(KEY88_BS,          RETROK_BACKSPACE);
   handle_key(KEY88_INS,         RETROK_INSERT);
   handle_key(KEY88_DEL,         RETROK_DELETE);
   /*
   handle_key(KEY88_HENKAN,      RETROK_);
   handle_key(KEY88_KETTEI,      RETROK_);
   handle_key(KEY88_PC,          RETROK_);
   */
   handle_key(KEY88_ZENKAKU,     RETROK_RALT);
   handle_key(KEY88_RETURNL,     RETROK_RETURN);
   handle_key(KEY88_RETURNR,     RETROK_RETURN);
   handle_key(KEY88_SHIFTL,      RETROK_LSHIFT);
   handle_key(KEY88_SHIFTR,      RETROK_RSHIFT);
   
   /* Keypad */
   for (i = 0; i < 10; i++)
      handle_key(KEY88_KP_0 + i, RETROK_KP0 + i);
   handle_key(KEY88_KP_MULTIPLY, RETROK_KP_MULTIPLY);
   handle_key(KEY88_KP_ADD,      RETROK_KP_PLUS);
   handle_key(KEY88_KP_EQUAL,    RETROK_KP_EQUALS);
   handle_key(KEY88_KP_COMMA,    RETROK_KP_ENTER);
   handle_key(KEY88_KP_PERIOD,   RETROK_KP_PERIOD);
   handle_key(KEY88_KP_SUB,      RETROK_KP_MINUS);
   handle_key(KEY88_KP_DIVIDE,   RETROK_KP_DIVIDE);
   
   /* Alphabet */
   for (i = 0; i < 26; i++)
      handle_key(KEY88_A + i, RETROK_a + i);

   /* Function keys */
   for (i = 0; i < 5; i++)
      handle_key(KEY88_F1 + i, RETROK_F1 + i);
   for (i = 0; i < 5; i++)
      handle_key(KEY88_F6 + i, RETROK_F6 + i);

   /* Joypads */
   mouse_mode = 3;
   handle_key(KEY88_PAD1_UP,    RETRO_DEVICE_ID_JOYPAD_UP);
   handle_key(KEY88_PAD1_DOWN,  RETRO_DEVICE_ID_JOYPAD_DOWN);
   handle_key(KEY88_PAD1_LEFT,  RETRO_DEVICE_ID_JOYPAD_LEFT);
   handle_key(KEY88_PAD1_RIGHT, RETRO_DEVICE_ID_JOYPAD_RIGHT);
   handle_key(KEY88_PAD1_A,     RETRO_DEVICE_ID_JOYPAD_A);
   handle_key(KEY88_PAD1_B,     RETRO_DEVICE_ID_JOYPAD_B);
   
   handle_key(KEY88_PAD2_UP,    RETRO_DEVICE_ID_JOYPAD_UP);
   handle_key(KEY88_PAD2_DOWN,  RETRO_DEVICE_ID_JOYPAD_DOWN);
   handle_key(KEY88_PAD2_LEFT,  RETRO_DEVICE_ID_JOYPAD_LEFT);
   handle_key(KEY88_PAD2_RIGHT, RETRO_DEVICE_ID_JOYPAD_RIGHT);
   handle_key(KEY88_PAD2_A,     RETRO_DEVICE_ID_JOYPAD_A);
   handle_key(KEY88_PAD2_B,     RETRO_DEVICE_ID_JOYPAD_B);
}

static void handle_rumble(void)
{
   if (rumble_enabled && (!get_drive_ready(0) || !get_drive_ready(1)))
   {
      rumble_cb(0, RETRO_RUMBLE_STRONG, 65535);
      rumble_cb(0, RETRO_RUMBLE_WEAK, 65535 / 32);
   }
   else
   {
      rumble_cb(0, RETRO_RUMBLE_STRONG, 0);
      rumble_cb(0, RETRO_RUMBLE_WEAK, 0);
   }
}

static void init_variables(void)
{
   struct retro_variable var = {0};

   var.key = "q88_basic_mode";

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      if (strcmp(var.value, "N88 V2") == 0)
         boot_basic = BASIC_V2;
      else if (strcmp(var.value, "N88 V1H") == 0)
         boot_basic = BASIC_V1H;
      else if (strcmp(var.value, "N88 V1S") == 0)
         boot_basic = BASIC_V1S;
      else if (strcmp(var.value, "N") == 0)
         boot_basic = BASIC_N;
      else
         boot_basic = BASIC_V1S;
   }

   var.key = "q88_sub_cpu_mode";

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      cpu_timing = atoi(var.value);
   }

   var.key = "q88_cpu_clock";
   
   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      cmt_speed = 0;
      if (!strncmp(var.value, "4 MHz", 1))
      {
         boot_clock_4mhz = CLOCK_4MHZ;
         cpu_clock_mhz = CONST_4MHZ_CLOCK;
      }
      else if (!strncmp(var.value, "8 MHz", 1))
      {
         boot_clock_4mhz = CLOCK_8MHZ;
         cpu_clock_mhz = CONST_8MHZ_CLOCK;
      }
      else if (!strncmp(var.value, "16 MHz (overclock)", 2))
      {
         boot_clock_4mhz = CLOCK_8MHZ;
         cpu_clock_mhz = CONST_8MHZ_CLOCK * 2.0;
      }
      else if (!strncmp(var.value, "32 MHz (overclock)", 2))
      {
         boot_clock_4mhz = CLOCK_8MHZ;
         cpu_clock_mhz = CONST_8MHZ_CLOCK * 4.0;
      }
      else if (!strncmp(var.value, "64 MHz (overclock)", 2))
      {
         boot_clock_4mhz = CLOCK_8MHZ;
         cpu_clock_mhz = CONST_8MHZ_CLOCK * 8.0;
      }
      else if (!strncmp(var.value, "1 MHz (underclock)", 1))
      {
         boot_clock_4mhz = CLOCK_4MHZ;
         cpu_clock_mhz = CONST_4MHZ_CLOCK * 0.25;
      }
      else if (!strncmp(var.value, "2 MHz (underclock)", 1))
      {
         boot_clock_4mhz = CLOCK_4MHZ;
         cpu_clock_mhz = CONST_4MHZ_CLOCK * 0.50;
      }
      else
      {
         boot_clock_4mhz = CLOCK_4MHZ;
         cpu_clock_mhz = CONST_4MHZ_CLOCK;
      }
   }
   
   var.key = "q88_use_fdc_wait";
   
   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
      fdc_wait = (!strcmp(var.value, "enabled")) ? TRUE : FALSE;
   else
      fdc_wait = false;
  
   var.key = "q88_sound_board";
   
   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
      sound_board = (!strcmp(var.value, "OPNA")) ? SOUND_II : SOUND_I;
   else
      sound_board = SOUND_I;
  
   var.key = "q88_pcg-8100";
   
   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
      use_pcg = (!strcmp(var.value, "enabled")) ? TRUE : FALSE;
   else
      use_pcg = FALSE;

   var.key = "q88_screen_size";

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
      screen_size = (!strcmp(var.value, "half")) ? SCREEN_SIZE_HALF : SCREEN_SIZE_FULL;
   else
      screen_size = SCREEN_SIZE_FULL;

   var.key = "q88_save_to_disk_image";

   if (!save_to_disk_image && environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
      save_to_disk_image = (!strcmp(var.value, "enabled")) ? true : false;

   var.key = "q88_rumble";

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
      rumble_enabled = (!strcmp(var.value, "disabled")) ? false : true;
}

static bool load_system_file(uint8_t bios_index, byte *rom_data, uint32_t rom_size)
{
   char filename[256];
   char rom_filename[OSD_MAX_FILENAME];
   uint8_t i;

   for (i = 0; i < 4; i++)
   {
      if (string_is_empty(bios_filenames[bios_index][i]))
         continue;

      strncpy(filename, bios_filenames[bios_index][i], sizeof(filename) - 1);

      /* Look in the download directory first... */
      if (!filestream_exists(rom_filename) && !string_is_empty(download_dir))
         snprintf(rom_filename, sizeof(rom_filename), "%s%c%s", download_dir, SLASH, filename);

      /* ...then try system/quasi88... */
      if (!string_is_empty(system_dir))
         snprintf(rom_filename, sizeof(rom_filename), "%s%cquasi88%c%s", system_dir, SLASH, SLASH, filename);

      /* ...then the system folder itself. */
      if (!filestream_exists(rom_filename) && !string_is_empty(system_dir))
         snprintf(rom_filename, sizeof(rom_filename), "%s%c%s", system_dir, SLASH, filename);

      /* File still wasn't found, give up */
      if (!filestream_exists(rom_filename))
      {
         if (log_cb)
            log_cb(RETRO_LOG_ERROR, "[QUASI88]: Couldn't find %s\n", filename);
      }
      else
      {
         RFILE *file = filestream_open(rom_filename, RETRO_VFS_FILE_ACCESS_READ, RETRO_VFS_FILE_ACCESS_HINT_NONE);

         if (file)
         {
            filestream_read(file, rom_data, rom_size);
            filestream_close(file);
            if (log_cb)
               log_cb(RETRO_LOG_INFO, "[QUASI88]: Loaded %s (0x%08X)\n", rom_filename, rom_size);

            return true;
         }
      }
   }
  
   return false;
}

/* libretro API */

void retro_init(void)
{
   char *dir = NULL;
   struct retro_rumble_interface rumble;

   struct retro_input_descriptor desc[] = {
      { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT,   "Left (Keypad 4)" },
      { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP,     "Up (Keypad 8)" },
      { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN,   "Down (Keypad 2)" },
      { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT,  "Right (Keypad 6)" },
      { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A,      "X Key" },
      { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B,      "Z Key" },
      { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_X,      "Left Shift" },
      { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_Y,      "Space Key" },
      { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_START,  "Return Key" },
      { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_SELECT, "I Key" },
      { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_L,      "Change drive 1 disk" },
      { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_R,      "Change drive 2 disk" },

      { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT,   "D Key" },
      { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP,     "R Key" },
      { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN,   "F Key" },
      { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT,  "G Key" },
      { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A,      "Tab Key" },
      { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B,      "Q Key" },

      { 0 },
   };

   if (environ_cb(RETRO_ENVIRONMENT_GET_RUMBLE_INTERFACE, &rumble))
      rumble_cb = rumble.set_rumble_state;

   /* Set up paths */
   if (!environ_cb(RETRO_ENVIRONMENT_GET_LOG_INTERFACE, &log_cb))
      log_cb = NULL;
   if (!environ_cb(RETRO_ENVIRONMENT_GET_SYSTEM_DIRECTORY, &dir))
   {
      if (log_cb)
         log_cb(RETRO_LOG_ERROR, "[QUASI88]: Couldn't find system dir\n");
   }
   else
      snprintf(system_dir, sizeof(system_dir), "%s", dir);

   if (!environ_cb(RETRO_ENVIRONMENT_GET_CORE_ASSETS_DIRECTORY, &dir))
   {
      if (log_cb)
         log_cb(RETRO_LOG_ERROR, "[QUASI88]: Couldn't find download dir\n");
   }
   else
      snprintf(download_dir, sizeof(download_dir), "%s", dir);

   memory_allocate();

   /* Fallback on pseudo BIOS if needed */
   if (!load_system_file(N88_ROM, main_rom,   0x08000))
      memcpy(main_rom, &pbios_n88, 0x08000);
   if (!load_system_file(SUB_ROM, sub_romram, 0x00800))
      memcpy(sub_romram, &pbios_disk, 0x00800);
   rom_version = ROM_VERSION;
   load_system_file(EXT0_ROM,  main_rom_ext[0], 0x02000);
   load_system_file(EXT1_ROM,  main_rom_ext[1], 0x02000);
   load_system_file(EXT2_ROM,  main_rom_ext[2], 0x02000);
   load_system_file(EXT3_ROM,  main_rom_ext[3], 0x02000);
   load_system_file(N_ROM,     main_rom_n,      0x08000);
   load_system_file(KNJ1_ROM,  kanji_rom[0][0], 0x20000);
   load_system_file(KNJ2_ROM,  kanji_rom[1][0], 0x20000);
   load_system_file(JISHO_ROM, jisho_rom[0],    0x80000);

   /* == Font files == */
   /* Font 1 */
   if (load_system_file(FONT_ROM, font_mem, 0x01000))
   {
      font_loaded |= 1;
      memcpy(&font_mem[0x000], &kanji_rom[0][(1<<11)][0], 0x800);
      memcpy(&font_mem[0x800], &built_in_font_graph[0],   0x800);
   }
   else
      memcpy(&font_mem[0x000], &built_in_font_ANK[0],     0x800);

   /* Font 2 */
   if (load_system_file(FONT2_ROM, font_mem2, 0x01000))
   {
      font_loaded |= 2;
      memcpy(&font_mem2[0x000], &built_in_font_ANH[0],    0x800);
   }
   else
   {
      memcpy(&font_mem2[0x000], &built_in_font_ANH[0],    0x800);
      memcpy(&font_mem2[0x800], &built_in_font_graph[0],  0x800);
   }

   /* Font 3 */
   if (load_system_file(FONT3_ROM, font_mem3, 0x01000))
   {
      font_loaded |= 4;
      memcpy(&font_mem3[0x800], &built_in_font_graph[0],  0x800);
   }
   else
      memset(&font_mem3[0], 0, 0x1000);

   /* Assume false if the path exists, this is updated after */
   if (environ_cb(RETRO_ENVIRONMENT_GET_SAVE_DIRECTORY, &save_path) && !string_is_empty(save_path))
      save_to_disk_image = false;
   else
      save_to_disk_image = true;
  
   environ_cb(RETRO_ENVIRONMENT_SET_INPUT_DESCRIPTORS, desc);
   key_buffer = (bool*)calloc(KEY88_END, sizeof(bool));
   pad_buffer = (bool*)calloc(KEY88_END, sizeof(bool));
   init_variables();
   retro_disks_init();
}

void retro_reset(void)
{
   init_variables();
   apply_braces();
   frames = 0;
   if (tape_path[0])
      quasi88_load_tape_insert(tape_path);
   if (autotype_count > 0)
      autotype_start();
   quasi88_reset(NULL);
}

static bool load_m3u(const char *filename)
{
   char basedir[OSD_MAX_FILENAME];
   char line[OSD_MAX_FILENAME];
   char name[OSD_MAX_FILENAME];
   char *search_char;
   uint8_t loaded_disks = 0;
   OSD_FILE *playlist_file;

   /* Get directory the M3U was loaded from */
   strcpy(basedir, filename);
   path_basedir(basedir);

   playlist_file = osd_fopen(0, filename, "r");
   /* Couldn't open the specified M3U */
   if (!playlist_file)
      return false;

   while (osd_fgets(line, sizeof(line), playlist_file))
   {
      /* Commented line */
      if (line[0] == '#')
         continue;

      /* Find and replace line breaks */
      search_char = strchr(line, '\r');
      if (search_char)
         *search_char = '\0';
      search_char = strchr(line, '\n');
      if (search_char)
         *search_char = '\0';

      if (line[0] != '\0')
      {
         /* Try it as a relative path first */
         snprintf(name, sizeof(name), "%s%s", basedir, line);

         /* Doesn't exist, try as an absolute path now */
         if (osd_file_stat(name) == FILE_STAT_NOEXIST)
         {
            strncpy(name, line, sizeof(name));

            /* Give up */
            if (osd_file_stat(name) == FILE_STAT_NOEXIST)
               continue;
         }
         retro_disks_append(name);
         loaded_disks++;
      }
   }
   osd_fclose(playlist_file);
   retro_disks_ready();

   return loaded_disks != 0;
}

bool retro_load_game(const struct retro_game_info *info)
{
   init_variables();
   quasi88_start();
   quasi88_disk_eject_all();

   tape_path[0]   = '\0';
   autotype_count = 0;
   brace_basic    = -1;
   brace_clock    = 0;
   if (info && !string_is_empty(info->path))
   {
      if (strstr(info->path, ".m3u") != NULL)
         load_m3u(info->path);
      else if (is_tape(info->path))
      {
         /* A tape restored every frame doesn't load the same, so run-ahead,
          * which restores a state each frame, can't be used with one */
         uint64_t quirks = RETRO_SERIALIZATION_QUIRK_INCOMPLETE;

         environ_cb(RETRO_ENVIRONMENT_SET_SERIALIZATION_QUIRKS, &quirks);
         strlcpy(tape_path, info->path, sizeof(tape_path));
         autotype_plan(info->path, true);
         quasi88_load_tape_insert(tape_path);
      }
      else
      {
         autotype_plan(info->path, false);
         retro_disks_append(info->path);
         quasi88_disk_insert(DRIVE_1, info->path, 0, 0);
      }
   }
   apply_braces();
   if (autotype_count > 0)
      autotype_start();
   quasi88_reset(NULL);
   quasi88_exec();
   
   return true;
}

bool retro_load_game_special(unsigned type, const struct retro_game_info *info, size_t num_info)
{
   uint8_t i;

   init_variables();
   quasi88_start();
   quasi88_disk_eject_all();

   for (i = 0; i < num_info; i++)
   {
      if (info && !string_is_empty(info[i].path))
         retro_disks_append(info[i].path);
   }
   retro_disks_ready();
   quasi88_reset(NULL);
   quasi88_exec();

   return true;
}

void retro_unload_game(void)
{
}

void retro_audio_append(const INT16 *buf, int count)
{
   unsigned room = AUDIO_BUF_FRAMES - audio_buf_frames;
   unsigned n    = (count > 0) ? (unsigned)count : 0;

   if (n > room)
      n = room;
   memcpy(audio_buf + audio_buf_frames * 2, buf, n * 2 * sizeof(INT16));
   audio_buf_frames += n;
}

void retro_run(void)
{
   int stat;
   int frame;
   int count = 1;

   handle_input();
   handle_autotype();
   /* A held key would repeat if the machine ran ahead */
   if (tape_loading() && autotype_held < 0)
      count = TAPE_TURBO_FRAMES;
   audio_buf_frames = 0;
   for (frame = 0; frame < count; frame++)
   {
      /* Run the emulation loop until one VSYNC period has completed */
      do
      {
         stat = quasi88_loop();
      } while (stat == QUASI88_LOOP_BUSY);
      tape_tick();
   }
   if (rumble_cb)
      handle_rumble();
   video_cb(screen_buf, WIDTH, HEIGHT, WIDTH * 2);

   /* Prevent a loud audio pop */
   if (frames <= FRAMES_BEFORE_AUDIO)
      memset(audio_buf, 0, audio_buf_frames * 2 * sizeof(INT16));
   if (audio_buf_frames)
      audio_batch_cb(audio_buf, audio_buf_frames);
   frames++;
}

void retro_get_system_info(struct retro_system_info *info)
{
   memset(info, 0, sizeof(*info));
   info->library_name     = "QUASI88";
#ifndef GIT_VERSION
#define GIT_VERSION ""
#endif
   info->library_version  = "0.6.4" GIT_VERSION;
   info->need_fullpath    = false;
   info->valid_extensions = "d88|m3u|t88|cmt";
   info->block_extract    = false;
}

void retro_get_system_av_info(struct retro_system_av_info *info)
{
   memset(info, 0, sizeof(*info));
   info->geometry.base_width   = WIDTH;
   info->geometry.base_height  = HEIGHT;
   info->geometry.max_width    = WIDTH;
   info->geometry.max_height   = HEIGHT;
   info->geometry.aspect_ratio = 1.6;
   info->timing.fps            = vsync_freq_hz;
   info->timing.sample_rate    = (int)(44100 / vsync_freq_hz) * vsync_freq_hz;
}

void retro_deinit(void)
{
   /* Stop the emulator */
   quasi88_stop(TRUE);

   /* Free our input buffers */
   if (key_buffer)
      free(key_buffer);
   if (pad_buffer)
      free(pad_buffer);
   key_buffer = NULL;
   pad_buffer = NULL;

   /* Free all our file handles */
   osd_fcloseall();
}

unsigned retro_get_region(void)
{
   return RETRO_REGION_NTSC;
}

unsigned retro_api_version(void)
{
   return RETRO_API_VERSION;
}

void retro_set_controller_port_device(unsigned in_port, unsigned device)
{
}

void retro_set_environment(retro_environment_t cb)
{
   bool no_game                   = true;
   enum retro_pixel_format rgb565 = RETRO_PIXEL_FORMAT_RGB565;
   struct retro_vfs_interface_info vfs_interface_info;
   
   environ_cb                     = cb;

   cb(RETRO_ENVIRONMENT_SET_CONTROLLER_INFO, (void*)ports);
   cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT,    &rgb565);
   cb(RETRO_ENVIRONMENT_SET_SUBSYSTEM_INFO,  (void*)subsystems);
   cb(RETRO_ENVIRONMENT_SET_SUPPORT_NO_GAME, &no_game);
   
   /* Set localized core options if available */
   libretro_set_core_options(environ_cb,
                             &libretro_supports_option_categories);

   vfs_interface_info.required_interface_version = FILESTREAM_REQUIRED_VFS_VERSION;
   vfs_interface_info.iface = NULL;
   if (cb(RETRO_ENVIRONMENT_GET_VFS_INTERFACE, &vfs_interface_info)) {
     filestream_vfs_init(&vfs_interface_info);
   }
}

void retro_set_audio_sample(retro_audio_sample_t cb)
{
   audio_cb = cb;
}

void retro_set_audio_sample_batch(retro_audio_sample_batch_t cb)
{
   audio_batch_cb = cb;
}

void retro_set_input_poll(retro_input_poll_t cb)
{
   input_poll_cb = cb;
}

void retro_set_input_state(retro_input_state_t cb)
{
   input_state_cb = cb;
}

void retro_set_video_refresh(retro_video_refresh_t cb)
{
   video_cb = cb;
}

size_t retro_serialize_size(void)
{
   return 0x70000;
}

/* TODO: Not safe across endianness yet! */
bool retro_serialize(void *data, size_t size)
{
   long used;
   int success;
   OSD_FILE *fp;

   if (size < sizeof(struct autotype_state))
      return false;
   fp = osd_file_mem(data, size - sizeof(struct autotype_state), 1);
   if (!fp)
      return false;

   success = statesave_by_fp (fp);

   /* Clear what the state does not use, so equal states are equal bytes */
   used = osd_ftell(fp);
   if (used >= 0 && (size_t)used < size - sizeof(struct autotype_state))
      memset((char*)data + used, 0, size - sizeof(struct autotype_state) - (size_t)used);

   autotype_save((struct autotype_state *)((char *)data + size - sizeof(struct autotype_state)));

   if (osd_file_did_overflow(fp))
   {
      log_cb(RETRO_LOG_ERROR, "OSD file overflown\n");
      success = false;
   }

   osd_fclose(fp);

   return success;
}

bool retro_unserialize(const void *data, size_t size)
{
   int success;
   OSD_FILE *fp = osd_file_mem(data, size, 0);
   if (!fp)
     return false;

   pc88main_term();
   pc88sub_term();

   success = stateload_by_fp (fp);

   osd_fclose(fp);

   pc88main_init(INIT_STATELOAD);
   pc88sub_init(INIT_STATELOAD);

   /* Redraw everything on the next frame without advancing display state */
   screen_set_dirty_frame();
   screen_set_dirty_palette();

   /* Loading a state releases every key, so press the held ones again */
   if (key_buffer)
      memset(key_buffer, 0, KEY88_END * sizeof(bool));
   if (pad_buffer)
      memset(pad_buffer, 0, KEY88_END * sizeof(bool));

   /* The state names the tape and how far it was read: open it there again,
    * as QUASI88's own state loading does */
   if (file_tape[CLOAD][0])
      sio_open_tapeload(file_tape[CLOAD]);

   if (size >= sizeof(struct autotype_state))
   {
      struct autotype_state state;

      memcpy(&state, (const char *)data + size - sizeof(state), sizeof(state));
      autotype_load(&state);
   }

   return success;
}

void *retro_get_memory_data(unsigned type)
{
   switch (type)
   {
      case RETRO_MEMORY_SYSTEM_RAM:
      case RETRO_MEMORY_PC88_SYSTEM_RAM:
         return main_ram;
      case RETRO_MEMORY_VIDEO_RAM:
      case RETRO_MEMORY_PC88_VIDEO_RAM:
         return main_vram;
      default:
         break;
   }

   return NULL;
}

size_t retro_get_memory_size(unsigned type)
{
   switch (type)
   {
      case RETRO_MEMORY_SYSTEM_RAM:
      case RETRO_MEMORY_PC88_SYSTEM_RAM:
         return 0x10000;
      case RETRO_MEMORY_VIDEO_RAM:
      case RETRO_MEMORY_PC88_VIDEO_RAM:
         return 0x10000;
      default:
         break;
   }

   return 0;
}

void retro_cheat_reset(void)
{
}

void retro_cheat_set(unsigned a, bool b, const char *c)
{
}
