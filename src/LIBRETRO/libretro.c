#include <stdarg.h>
#include <string.h>

#include <libretro.h>
#include <file/file_path.h>
#include <lists/dir_list.h>
#include <streams/file_stream.h>
#include <string/stdstring.h>

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

#define INT16 int16_t
#include "../snddrv/src/sound.h"
INT16 *finalmix;
int samples_this_frame;

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
static struct retro_rumble_interface rumble;
static retro_video_refresh_t video_cb;

static const struct retro_subsystem_rom_info pc88_disk[] = {
   { "Disk 1", "d88", true, false, true, NULL, 1 },
   { "Disk 2", "d88", true, false, true, NULL, 1 },
   { NULL }
};

static const struct retro_subsystem_info subsystems[] = {
   { "2-Disk Game", "pc88_2_disk", pc88_disk, 2, 0x0101 },
   /* { "Tape", "pc88_tape", pc88_tape, 2, 0x0102 }, TODO */
   { NULL }
};

static uint32_t  frames           = 0;
static bool     *key_buffer       = NULL;
static bool     *pad_buffer       = NULL;
static bool      rumble_enabled   = true;
static char      system_dir[4096] = { '\0' };

void display_message(const char *msg)
{
   char *str = (char*)calloc(4096, sizeof(char));
   struct retro_message rmsg;

   snprintf(str, 4096, "%s", msg);
   rmsg.frames = 300;
   rmsg.msg = str;
   environ_cb(RETRO_ENVIRONMENT_SET_MESSAGE, &rmsg);
}

void handle_key(uint8_t key, uint16_t retro_key)
{
   bool key_on = input_state_cb(0, RETRO_DEVICE_KEYBOARD, 0, retro_key);
   
   if (!pad_buffer[key])
   {
      if (!key_buffer[key] && key_on)
      {
         quasi88_key(key, 1);
         key_buffer[key] = true;
      }
      else if (!key_on)
      {
         quasi88_key(key, 0);
         key_buffer[key] = false;
      }
   }
}

void handle_pad(uint8_t key, uint16_t retro_button, uint8_t pad)
{
   bool button_on = input_state_cb(pad, RETRO_DEVICE_JOYPAD, 0, retro_button);
   
   if (!key_buffer[key])
   {
      if (!pad_buffer[key] && button_on)
      {
         quasi88_key(key, 1);
         pad_buffer[key] = true;
      }
      else if (!button_on)
      {
         quasi88_key(key, 0);
         pad_buffer[key] = false;
      }
   }
}

void handle_input()
{
   uint8_t i;
   
   input_poll_cb();

   /* Simple default remappings for joypad, these are temporary and a bit arbitrary */
   handle_pad(KEY88_KP_8,   RETRO_DEVICE_ID_JOYPAD_UP,     0);
   handle_pad(KEY88_KP_2,   RETRO_DEVICE_ID_JOYPAD_DOWN,   0);
   handle_pad(KEY88_KP_4,   RETRO_DEVICE_ID_JOYPAD_LEFT,   0);
   handle_pad(KEY88_KP_6,   RETRO_DEVICE_ID_JOYPAD_RIGHT,  0);
   handle_pad(KEY88_Z,      RETRO_DEVICE_ID_JOYPAD_A,      0);
   handle_pad(KEY88_X,      RETRO_DEVICE_ID_JOYPAD_B,      0);
   handle_pad(KEY88_SPACE,  RETRO_DEVICE_ID_JOYPAD_Y,      0);
   handle_pad(KEY88_RETURN, RETRO_DEVICE_ID_JOYPAD_START,  0);
   handle_pad(KEY88_I,      RETRO_DEVICE_ID_JOYPAD_SELECT, 0);

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
   /* What do these do? How do we best map them to the keyboard?
   handle_key(KEY88_INS_DEL,     RETROK_);
   handle_key(KEY88_GRAPH,       RETROK_);
   handle_key(KEY88_KANA,        RETROK_);
   */
   handle_key(KEY88_SHIFT,       RETROK_RSHIFT);
   handle_key(KEY88_CTRL,        RETROK_RCTRL);
   handle_key(KEY88_STOP,        RETROK_BREAK);
   handle_key(KEY88_ESC,         RETROK_ESCAPE);
   handle_key(KEY88_TAB,         RETROK_TAB);
   handle_key(KEY88_DOWN,        RETROK_DOWN);
   handle_key(KEY88_LEFT,        RETROK_LEFT);
   /*
   handle_key(KEY88_HELP,        RETROK_);
   handle_key(KEY88_COPY,        RETROK_);
   */
   handle_key(KEY88_CAPS,        RETROK_CAPSLOCK);
   /*
   handle_key(KEY88_ROLLUP,      RETROK_);
   handle_key(KEY88_ROLLDOWN,    RETROK_);
   */
   handle_key(KEY88_BS,          RETROK_BACKSPACE);
   handle_key(KEY88_INS,         RETROK_INSERT);
   handle_key(KEY88_DEL,         RETROK_DELETE);
   /*
   handle_key(KEY88_HENKAN,      RETROK_);
   handle_key(KEY88_KETTEI,      RETROK_);
   handle_key(KEY88_PC,          RETROK_);
   handle_key(KEY88_ZENKAKU,     RETROK_);
   */
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
   for (i = 0; i < 8; i++)
      handle_key(KEY88_F6 + i, RETROK_F1 + i);

   /* Joypads */
   mouse_mode = 3;
   handle_pad(KEY88_PAD1_UP,    RETRO_DEVICE_ID_JOYPAD_UP,    0);
   handle_pad(KEY88_PAD1_DOWN,  RETRO_DEVICE_ID_JOYPAD_DOWN,  0);
   handle_pad(KEY88_PAD1_LEFT,  RETRO_DEVICE_ID_JOYPAD_LEFT,  0);
   handle_pad(KEY88_PAD1_RIGHT, RETRO_DEVICE_ID_JOYPAD_RIGHT, 0);
   handle_pad(KEY88_PAD1_A,     RETRO_DEVICE_ID_JOYPAD_A,     0);
   handle_pad(KEY88_PAD1_B,     RETRO_DEVICE_ID_JOYPAD_B,     0);
   
   handle_pad(KEY88_PAD2_UP,    RETRO_DEVICE_ID_JOYPAD_UP,    1);
   handle_pad(KEY88_PAD2_DOWN,  RETRO_DEVICE_ID_JOYPAD_DOWN,  1);
   handle_pad(KEY88_PAD2_LEFT,  RETRO_DEVICE_ID_JOYPAD_LEFT,  1);
   handle_pad(KEY88_PAD2_RIGHT, RETRO_DEVICE_ID_JOYPAD_RIGHT, 1);
   handle_pad(KEY88_PAD2_A,     RETRO_DEVICE_ID_JOYPAD_A,     1);
   handle_pad(KEY88_PAD2_B,     RETRO_DEVICE_ID_JOYPAD_B,     1);
}

void handle_rumble()
{
   if (rumble_enabled && (!get_drive_ready(0) || !get_drive_ready(1)))
   {
      rumble.set_rumble_state(0, RETRO_RUMBLE_STRONG, 65535);
      rumble.set_rumble_state(0, RETRO_RUMBLE_WEAK, 65535 / 32);
   }
   else
      rumble.set_rumble_state(0, RETRO_RUMBLE_STRONG, 0);
}

void init_variables()
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
   
   var.key = "q88_cpu_clock";
   
   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
   {
      cmt_speed = 0;
      if (!strncmp(var.value, "4 MHz", 2))
      {
         boot_clock_4mhz = CLOCK_4MHZ;
         cpu_clock_mhz = CONST_4MHZ_CLOCK;
      }
      else if (!strncmp(var.value, "8 MHz", 2))
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
      else if (!strncmp(var.value, "1 MHz (underclock)", 2))
      {
         boot_clock_4mhz = CLOCK_4MHZ;
         cpu_clock_mhz = CONST_4MHZ_CLOCK * 0.25;
      }
      else if (!strncmp(var.value, "2 MHz (underclock)", 2))
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

   var.key = "q88_save_to_disk_image";

   if (!save_to_disk_image && environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
      save_to_disk_image = (!strcmp(var.value, "enabled")) ? true : false;
  
   var.key = "q88_rumble";
   
   if (environ_cb(RETRO_ENVIRONMENT_GET_RUMBLE_INTERFACE, &rumble))
   {
      if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE, &var) && var.value)
         rumble_enabled = (!strcmp(var.value, "disabled")) ? false : true;
   }
   else
      rumble_enabled = false;
}

bool load_system_file(char *filename, byte *rom_data, uint32_t rom_size)
{
   char rom_filename[4096];

   snprintf(rom_filename, 4096, "%s%cquasi88%c%s", system_dir, SLASH, SLASH, filename);
   rom_filename[sizeof(rom_filename) - 1] = '\0';
   if (filestream_exists(rom_filename))
   {
      RFILE *file = filestream_open(rom_filename, RETRO_VFS_FILE_ACCESS_READ, RETRO_VFS_FILE_ACCESS_HINT_NONE);

      if (file)
      {
         filestream_read(file, rom_data, rom_size);
         filestream_close(file);
      }
      if (log_cb)
         log_cb(RETRO_LOG_INFO, "[QUASI88]: Loaded %s from system_dir (0x%08X)\n", filename, rom_size);
   }
   else
   {
      if (log_cb)
         log_cb(RETRO_LOG_ERROR, "[QUASI88]: Couldn't find %s in system_dir\n", filename);
      return false;
   }
  
  return true;
}

/* libretro API */

void retro_init(void)
{
   char *dir = NULL;
   
   if (!environ_cb(RETRO_ENVIRONMENT_GET_LOG_INTERFACE, &log_cb))
      log_cb = NULL;
   if (!environ_cb(RETRO_ENVIRONMENT_GET_SYSTEM_DIRECTORY, &dir) || !dir)
   {
      if (log_cb)
         log_cb(RETRO_LOG_ERROR, "[QUASI88]: Couldn't find system dir\n");
   }
   else
   {
      snprintf(system_dir, sizeof(system_dir), "%s", dir);
      memory_allocate();
      if (!load_system_file("n88.rom", main_rom, 0x08000))
         display_message("Main BIOS not in system/quasi88");
      load_system_file("n88_0.rom",    main_rom_ext[0], 0x02000);
      load_system_file("n88_1.rom",    main_rom_ext[1], 0x02000);
      load_system_file("n88_2.rom",    main_rom_ext[2], 0x02000);
      load_system_file("n88_3.rom",    main_rom_ext[3], 0x02000);
      load_system_file("n88n.rom",     main_rom_n,      0x08000);
      load_system_file("disk.rom",     sub_romram,      0x02000);
      load_system_file("n88knj1.rom",  kanji_rom[0][0], 0x20000);
      load_system_file("n88knj2.rom",  kanji_rom[1][0], 0x20000);
      load_system_file("n88jisho.rom", jisho_rom[0],    0x80000);

      /* == Font files == */
      /* Font 1 */
      if (load_system_file("font.rom", font_mem, 0x01000))
      {
         font_loaded |= 1;
         memcpy(&font_mem[0x000], &kanji_rom[0][(1<<11)][0], 0x800);
         memcpy(&font_mem[0x800], &built_in_font_graph[0],   0x800);
      }
      else
         memcpy(&font_mem[0x000], &built_in_font_ANK[0],     0x800);

      /* Font 2 */
      if (load_system_file("font2.rom", font_mem2, 0x01000))
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
      if (load_system_file("font3.rom", font_mem3, 0x01000))
      {
         font_loaded |= 4;
         memcpy(&font_mem3[0x800], &built_in_font_graph[0],  0x800);
      }
      else
         memset(&font_mem3[0], 0, 0x1000);
   }

   /* Assume false if the path exists, this is updated after */
   if (!string_is_empty(save_path))
      save_to_disk_image = false;
   else
      save_to_disk_image = true;
  
   struct retro_input_descriptor desc[] = {
      { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT,   "Left Keypad" },
      { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP,     "Up Keypad" },
      { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN,   "Down Keypad" },
      { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT,  "Right Keypad" },
      { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A,      "Z Key" },
      { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B,      "X Key" },
      { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_Y,      "Space Key" },
      { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_START,  "Return Key" },
      { 0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_SELECT, "I Key" },

      { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_LEFT,   "D Key" },
      { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP,     "R Key" },
      { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_DOWN,   "F Key" },
      { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_RIGHT,  "G Key" },
      { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_A,      "Tab Key" },
      { 1, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_B,      "Q Key" },

      { 0 },
   };
   environ_cb(RETRO_ENVIRONMENT_SET_INPUT_DESCRIPTORS, desc);
   key_buffer = (bool*)calloc(KEY88_END, sizeof(bool));
   pad_buffer = (bool*)calloc(KEY88_END, sizeof(bool));
   init_variables();
}

void retro_reset(void)
{
   init_variables();
   frames = 0;
   quasi88_reset(NULL);
}

bool retro_load_game(const struct retro_game_info *info)
{
   init_variables();
   quasi88_start();
   quasi88_disk_eject_all();
   if (info && !string_is_empty(info->path))
      quasi88_disk_insert(DRIVE_1, info->path, 0, 0);
   quasi88_reset(NULL);
   quasi88_exec();
   
   return true;
}

bool retro_load_game_special(unsigned type, const struct retro_game_info *info, size_t num_info)
{
   if (num_info == 2)
   {
      if (!retro_load_game(&info[0]))
         return false;
      if (!string_is_empty(info[1].path))
         quasi88_disk_insert(DRIVE_2, info[1].path, 0, 0);
      quasi88_reset(NULL);
      return true;
   }
 
   return false;
}

void retro_unload_game()
{
   
}

void retro_run(void)
{
   handle_input();
   quasi88_loop();
   quasi88_loop();
   handle_rumble();
   video_cb(screen_buf, WIDTH, HEIGHT, WIDTH * 2);
   
   /* Prevent a loud audio pop */
   if (frames > FRAMES_BEFORE_AUDIO)
      audio_batch_cb(finalmix, samples_this_frame);
   frames++;
}

void retro_get_system_info(struct retro_system_info *info)
{
   memset(info, 0, sizeof(*info));
   info->library_name     = "QUASI88";
   info->library_version  = "0.6.4";
   info->need_fullpath    = false;
   info->valid_extensions = "d88";
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
   info->timing.fps            = 60;
   info->timing.sample_rate    = 44100;
}

void retro_deinit()
{
   quasi88_stop(TRUE);
   free(key_buffer);
   key_buffer = NULL;
   free(pad_buffer);
   pad_buffer = NULL;
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

#define USER_DISKS_STRING_SIZE 4096
bool init_user_disk_list(char *user_disks_string)
{
   if (!environ_cb)
      return false;
   else
   {
      char user_disks_temp[USER_DISKS_STRING_SIZE];
	  
	  strncpy(user_disks_string, "User disk; ", USER_DISKS_STRING_SIZE);
	  user_disks_temp[0] = '\0';
	  environ_cb(RETRO_ENVIRONMENT_GET_SAVE_DIRECTORY, &save_path);
	  if (!string_is_empty(save_path))
      {
         struct string_list* user_disks = dir_list_new(save_path, "d88", false, false, false, false);

         /* Trim fullpath from all filenames */
         for (uint8_t i = 0; i < user_disks->size; i++)
            string_list_set(user_disks, i, path_basename(user_disks->elems[i].data));
	 
         /* Convert list of files to string */
         string_list_join_concat(user_disks_temp, USER_DISKS_STRING_SIZE, user_disks, "|");
         strncat(user_disks_string, user_disks_temp, USER_DISKS_STRING_SIZE);
      }
      else
         return false;
   }
   
   return true;
}

void retro_set_environment(retro_environment_t cb)
{
   static char user_disks_string[USER_DISKS_STRING_SIZE];

   environ_cb = cb;
   user_disks_string[0] = '\0';
   init_user_disk_list(user_disks_string);
   static const struct retro_variable vars[] = 
   {
      { "q88_basic_mode", "Basic mode; N88 V2|N88 V1H|N88 V1S|N" },
      { "q88_cpu_clock", "CPU clock; 4 MHz|8 MHz|16 MHz (overclock)|32 MHz (overclock)|64 MHz (overclock)|1 MHz (underclock)|2 MHz (underclock)" },
      { "q88_use_fdc_wait", "Use FDC-Wait; disabled|enabled"},
      { "q88_pcg-8100", "Use PCG-8100; disabled|enabled"},
      { "q88_save_to_disk_image", "Save to disk image; disabled|enabled"},
      { "q88_user_disk", user_disks_string },
      { "q88_rumble", "Rumble on disk access; enabled|disabled"},
      { NULL, NULL },
   };
   static const struct retro_controller_description port[] = {
      { "Retro Joypad", RETRO_DEVICE_JOYPAD },
      { "Retro Keyboard", RETRO_DEVICE_KEYBOARD },
      { 0 },
   };
   static const struct retro_controller_info ports[] = {
      { port, 2 },
      { port, 2 },
      { NULL, 0 },
   };
   bool no_game = true;
   
   environ_cb = cb;
   cb(RETRO_ENVIRONMENT_SET_CONTROLLER_INFO, (void*)ports);
   cb(RETRO_ENVIRONMENT_SET_SUBSYSTEM_INFO, (void*)subsystems);
   cb(RETRO_ENVIRONMENT_SET_SUPPORT_NO_GAME, &no_game);
   cb(RETRO_ENVIRONMENT_SET_VARIABLES, (void*)vars);
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
   return 0;
}

bool retro_serialize(void *data, size_t size)
{
   return false;
}

bool retro_unserialize(const void *data, size_t size)
{
   return false;
}

void *retro_get_memory_data(unsigned type)
{
   if (type == RETRO_MEMORY_SYSTEM_RAM)
      return main_ram;
   else
      return NULL;
}

size_t retro_get_memory_size(unsigned type)
{
   if (type == RETRO_MEMORY_SYSTEM_RAM)
      return 0x10000;
   else
      return 0;
}

void retro_cheat_reset(void)
{
}

void retro_cheat_set(unsigned a, bool b, const char *c)
{
}