#include <stdint.h>

#include "libretro_options.h"

static const struct retro_subsystem_rom_info pc88_disk[] = {
   { "Disk 1", "d88", true, false, true, NULL, 1 },
   { "Disk 2", "d88", true, false, true, NULL, 1 },
   { "Disk 3", "d88", true, false, true, NULL, 1 },
   { "Disk 4", "d88", true, false, true, NULL, 1 },
   { "Disk 5", "d88", true, false, true, NULL, 1 },
   { "Disk 6", "d88", true, false, true, NULL, 1 },
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

static const struct retro_controller_description port[] = 
{
   { "Retro Joypad",   RETRO_DEVICE_JOYPAD },
   { "Retro Keyboard", RETRO_DEVICE_KEYBOARD },
   { 0 },
};

static const struct retro_controller_info ports[] = 
{
   { port, 2 },
   { port, 2 },
   { NULL, 0 },
};

static const struct retro_variable variables_old[] = 
{
   { "q88_basic_mode",         "Basic mode; N88 V2|N88 V1H|N88 V1S|N" },
   { "q88_cpu_clock",          "CPU clock; 4 MHz|8 MHz|16 MHz (overclock)|32 MHz (overclock)|64 MHz (overclock)|1 MHz (underclock)|2 MHz (underclock)" },
   { "q88_sound_board",        "Sound board; OPN|OPNA"},
   { "q88_use_fdc_wait",       "Use FDC-Wait; enabled|disabled"},
   { "q88_pcg-8100",           "Use PCG-8100; disabled|enabled"},
   { "q88_save_to_disk_image", "Save to disk image; disabled|enabled"},
   { "q88_rumble",             "Rumble on disk access; enabled|disabled"},
#if defined(PSP) || defined(_3DS)
   { "q88_screen_size",        "Screen size; half|full"},
#else
   { "q88_screen_size",        "Screen size; full|half"},
#endif
   { NULL, NULL },
};

static const struct retro_core_option_definition variables_en_us[] = 
{
   { 
      "q88_basic_mode", 
      "BASIC mode", 
      "Recommended: N88 V2/V1H for PC-8800 series software, N for PC-8000 series software.", 
      {
         { "N88 V2",  "N88-BASIC V2" },
         { "N88 V1H", "N88-BASIC V1H" },
         { "N88 V1S", "N88-BASIC V1S" },
         { "N",       "N-BASIC" },
         { NULL, NULL }
      },
      "N88 V2"
   },

   { 
      "q88_cpu_clock", 
      "CPU", 
      "Recommended: 4MHz or 8MHz. Some software may run too fast with an 8MHz CPU.",
      {
         { "4",  "4 MHz (NEC µPD780)" },
         { "8",  "8 MHz (NEC µPD70008)" },
         { "16", "16 MHz (overclock)" },
         { "32", "32 MHz (overclock)" },
         { "64", "64 MHz (overclock)" },
         { "1",  "1 MHz (underclock)" },
         { "2",  "2 MHz (underclock)" },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      "Sound board", 
      "Recommended: OPNA. Some software will sound different when using OPN hardware.",
      {
         { "OPN",  "OPN (Yamaha YM2203)" },
         { "OPNA", "OPNA (Yamaha YM2608)"},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      "Use FDC-Wait", 
      "Recommended: ON. Enables more accurate IO timing for the floppy disk controller.",
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_pcg-8100", 
      "Use PCG-8100", 
      "Recommended: OFF. May be required for some PC-8000 series software.",
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   {
      "q88_save_to_disk_image", 
      "Save to disk image", 
      "Recommended: OFF. Allows the core to rewrite data to the inserted floppy disk(s). Will only work with unzipped content.",
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   { 
      "q88_rumble", 
      "Rumble on disk access", 
      "Recommended: ON. Imitates the read sounds on the floppy disk controller using the controller's rumble.",
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_screen_size", 
      "Screen size", 
#if defined (PSP)
      "Recommended: Half. Allows the core to scale the image down. Recommended for the PSP screen.",
#elif defined (_3DS)
      "Recommended: Half. Allows the core to scale the image down. Recommended for the Nintendo 3DS screen.",
#else
      "Recommended: Full. Allows the core to scale the image down. Only recommended for display heights below 400.",
#endif
      {
         { "full",  "Full (640x400)" },
         { "half",  "Half (320x200)" },
         { NULL, NULL }
      },
#if defined (PSP) || defined (_3DS)
      "half"
#else
      "full"
#endif
   },

   { NULL, NULL, NULL, {{0}}, NULL }
};

static retro_core_options_intl variables_intl = { &variables_en_us, NULL };

void quasi88_set_environment(retro_environment_t cb)
{
   unsigned core_options_version      = 0;
   bool     no_game                   = true;
   enum     retro_pixel_format rgb565 = RETRO_PIXEL_FORMAT_RGB565;

   cb(RETRO_ENVIRONMENT_SET_CONTROLLER_INFO, (void*)ports);
   cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT,    &rgb565);
   cb(RETRO_ENVIRONMENT_SET_SUBSYSTEM_INFO,  (void*)subsystems);
   cb(RETRO_ENVIRONMENT_SET_SUPPORT_NO_GAME, &no_game);

   /* TODO: Code for determining the frontend's language should go here. */
   variables_intl.local = &variables_en_us;

   if (cb(RETRO_ENVIRONMENT_GET_CORE_OPTIONS_VERSION, &core_options_version) && core_options_version > 0)
      cb(RETRO_ENVIRONMENT_SET_CORE_OPTIONS_INTL, (void*)variables_intl);
   else
      cb(RETRO_ENVIRONMENT_SET_VARIABLES, (void*)variables_old);
}
