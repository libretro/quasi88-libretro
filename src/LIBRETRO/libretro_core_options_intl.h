#ifndef LIBRETRO_CORE_OPTIONS_INTL_H__
#define LIBRETRO_CORE_OPTIONS_INTL_H__

#if defined(_MSC_VER) && (_MSC_VER >= 1500 && _MSC_VER < 1900)
/* https://support.microsoft.com/en-us/kb/980263 */
#pragma execution_character_set("utf-8")
#pragma warning(disable:4566)
#endif

#include <libretro.h>

/*
 ********************************
 * VERSION: 2.0
 ********************************
 *
 * - 2.0: Add support for core options v2 interface
 * - 1.3: Move translations to libretro_core_options_intl.h
 *        - libretro_core_options_intl.h includes BOM and utf-8
 *          fix for MSVC 2010-2013
 *        - Added HAVE_NO_LANGEXTRA flag to disable translations
 *          on platforms/compilers without BOM support
 * - 1.2: Use core options v1 interface when
 *        RETRO_ENVIRONMENT_GET_CORE_OPTIONS_VERSION is >= 1
 *        (previously required RETRO_ENVIRONMENT_GET_CORE_OPTIONS_VERSION == 1)
 * - 1.1: Support generation of core options v0 retro_core_option_value
 *        arrays containing options with a single value
 * - 1.0: First commit
*/

#ifdef __cplusplus
extern "C" {
#endif

/*
 ********************************
 * Core Option Definitions
 ********************************
*/
/* RETRO_LANGUAGE_AR */

#define Q88_BASIC_MODE_LABEL_AR NULL
#define Q88_BASIC_MODE_INFO_0_AR NULL
#define OPTION_VAL_N88_V2_AR NULL
#define OPTION_VAL_N88_V1H_AR NULL
#define OPTION_VAL_N88_V1S_AR NULL
#define OPTION_VAL_N_AR NULL
#define Q88_SUB_CPU_MODE_LABEL_AR NULL
#define Q88_SUB_CPU_MODE_INFO_0_AR NULL
#define OPTION_VAL_0_AR NULL
#define OPTION_VAL_1_AR NULL
#define OPTION_VAL_2_AR NULL
#define Q88_CPU_CLOCK_LABEL_AR NULL
#define Q88_CPU_CLOCK_INFO_0_AR NULL
#define OPTION_VAL_4_AR NULL
#define OPTION_VAL_8_AR NULL
#define OPTION_VAL_16_AR NULL
#define OPTION_VAL_32_AR NULL
#define OPTION_VAL_64_AR NULL
#define OPTION_VAL_1_O2_AR NULL
#define OPTION_VAL_2_O2_AR NULL
#define Q88_SOUND_BOARD_LABEL_AR NULL
#define Q88_SOUND_BOARD_INFO_0_AR NULL
#define OPTION_VAL_OPN_AR NULL
#define OPTION_VAL_OPNA_AR NULL
#define Q88_USE_FDC_WAIT_LABEL_AR NULL
#define Q88_USE_FDC_WAIT_INFO_0_AR NULL
#define Q88_PCG_8100_LABEL_AR NULL
#define Q88_PCG_8100_INFO_0_AR NULL
#define Q88_SAVE_TO_DISK_IMAGE_LABEL_AR NULL
#define Q88_SAVE_TO_DISK_IMAGE_INFO_0_AR NULL
#define Q88_RUMBLE_LABEL_AR NULL
#define Q88_RUMBLE_INFO_0_AR NULL
#define Q88_SCREEN_SIZE_LABEL_AR NULL
#define Q88_SCREEN_SIZE_INFO_0_AR NULL
#define Q88_SCREEN_SIZE_INFO_1_AR NULL
#define Q88_SCREEN_SIZE_INFO_2_AR NULL
#define OPTION_VAL_FULL_AR NULL
#define OPTION_VAL_HALF_AR NULL

struct retro_core_option_v2_category option_cats_ar[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_ar[] = {
   { 
      "q88_basic_mode", 
      Q88_BASIC_MODE_LABEL_AR,
      NULL, 
      Q88_BASIC_MODE_INFO_0_AR,
      NULL,
      NULL,
      {
         { "N88 V2",  OPTION_VAL_N88_V2_AR },
         { "N88 V1H", OPTION_VAL_N88_V1H_AR },
         { "N88 V1S", OPTION_VAL_N88_V1S_AR },
         { "N",       OPTION_VAL_N_AR },
         { NULL, NULL }
      },
      "N88 V2"
   },

   { 
      "q88_sub_cpu_mode",
      Q88_SUB_CPU_MODE_LABEL_AR,
      NULL,
      Q88_SUB_CPU_MODE_INFO_0_AR,
      NULL,
      NULL,
      {
         { "0", OPTION_VAL_0_AR},
         { "1", OPTION_VAL_1_AR},
         { "2", OPTION_VAL_2_AR},
         { NULL, NULL },
      },
      "0"
   },

   { 
      "q88_cpu_clock", 
      Q88_CPU_CLOCK_LABEL_AR,
      NULL, 
      Q88_CPU_CLOCK_INFO_0_AR,
      NULL,
      NULL,
      {
         { "4",  OPTION_VAL_4_AR },
         { "8",  OPTION_VAL_8_AR },
         { "16", OPTION_VAL_16_AR },
         { "32", OPTION_VAL_32_AR },
         { "64", OPTION_VAL_64_AR },
         { "1",  OPTION_VAL_1_O2_AR },
         { "2",  OPTION_VAL_2_O2_AR },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      Q88_SOUND_BOARD_LABEL_AR,
      NULL, 
      Q88_SOUND_BOARD_INFO_0_AR,
      NULL,
      NULL,
      {
         { "OPN",  OPTION_VAL_OPN_AR },
         { "OPNA", OPTION_VAL_OPNA_AR},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      Q88_USE_FDC_WAIT_LABEL_AR,
      NULL, 
      Q88_USE_FDC_WAIT_INFO_0_AR,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_pcg-8100", 
      Q88_PCG_8100_LABEL_AR,
      NULL, 
      Q88_PCG_8100_INFO_0_AR,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   {
      "q88_save_to_disk_image", 
      Q88_SAVE_TO_DISK_IMAGE_LABEL_AR,
      NULL, 
      Q88_SAVE_TO_DISK_IMAGE_INFO_0_AR,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   { 
      "q88_rumble", 
      Q88_RUMBLE_LABEL_AR,
      NULL, 
      Q88_RUMBLE_INFO_0_AR,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_screen_size", 
      Q88_SCREEN_SIZE_LABEL_AR,
      NULL, 
#if defined (PSP)
      Q88_SCREEN_SIZE_INFO_0_AR,
#elif defined (_3DS)
      Q88_SCREEN_SIZE_INFO_1_AR,
#else
      Q88_SCREEN_SIZE_INFO_2_AR,
#endif
      NULL,
      NULL,
      {
         { "full",  OPTION_VAL_FULL_AR },
         { "half",  OPTION_VAL_HALF_AR },
         { NULL, NULL }
      },
#if defined (PSP) || defined (_3DS)
      "half"
#else
      "full"
#endif
   },

   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_ar = {
   option_cats_ar,
   option_defs_ar
};

/* RETRO_LANGUAGE_AST */

#define Q88_BASIC_MODE_LABEL_AST NULL
#define Q88_BASIC_MODE_INFO_0_AST NULL
#define OPTION_VAL_N88_V2_AST NULL
#define OPTION_VAL_N88_V1H_AST NULL
#define OPTION_VAL_N88_V1S_AST NULL
#define OPTION_VAL_N_AST NULL
#define Q88_SUB_CPU_MODE_LABEL_AST NULL
#define Q88_SUB_CPU_MODE_INFO_0_AST NULL
#define OPTION_VAL_0_AST NULL
#define OPTION_VAL_1_AST NULL
#define OPTION_VAL_2_AST NULL
#define Q88_CPU_CLOCK_LABEL_AST NULL
#define Q88_CPU_CLOCK_INFO_0_AST NULL
#define OPTION_VAL_4_AST NULL
#define OPTION_VAL_8_AST NULL
#define OPTION_VAL_16_AST NULL
#define OPTION_VAL_32_AST NULL
#define OPTION_VAL_64_AST NULL
#define OPTION_VAL_1_O2_AST NULL
#define OPTION_VAL_2_O2_AST NULL
#define Q88_SOUND_BOARD_LABEL_AST NULL
#define Q88_SOUND_BOARD_INFO_0_AST NULL
#define OPTION_VAL_OPN_AST NULL
#define OPTION_VAL_OPNA_AST NULL
#define Q88_USE_FDC_WAIT_LABEL_AST NULL
#define Q88_USE_FDC_WAIT_INFO_0_AST NULL
#define Q88_PCG_8100_LABEL_AST NULL
#define Q88_PCG_8100_INFO_0_AST NULL
#define Q88_SAVE_TO_DISK_IMAGE_LABEL_AST NULL
#define Q88_SAVE_TO_DISK_IMAGE_INFO_0_AST NULL
#define Q88_RUMBLE_LABEL_AST NULL
#define Q88_RUMBLE_INFO_0_AST NULL
#define Q88_SCREEN_SIZE_LABEL_AST NULL
#define Q88_SCREEN_SIZE_INFO_0_AST NULL
#define Q88_SCREEN_SIZE_INFO_1_AST NULL
#define Q88_SCREEN_SIZE_INFO_2_AST NULL
#define OPTION_VAL_FULL_AST NULL
#define OPTION_VAL_HALF_AST NULL

struct retro_core_option_v2_category option_cats_ast[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_ast[] = {
   { 
      "q88_basic_mode", 
      Q88_BASIC_MODE_LABEL_AST,
      NULL, 
      Q88_BASIC_MODE_INFO_0_AST,
      NULL,
      NULL,
      {
         { "N88 V2",  OPTION_VAL_N88_V2_AST },
         { "N88 V1H", OPTION_VAL_N88_V1H_AST },
         { "N88 V1S", OPTION_VAL_N88_V1S_AST },
         { "N",       OPTION_VAL_N_AST },
         { NULL, NULL }
      },
      "N88 V2"
   },

   { 
      "q88_sub_cpu_mode",
      Q88_SUB_CPU_MODE_LABEL_AST,
      NULL,
      Q88_SUB_CPU_MODE_INFO_0_AST,
      NULL,
      NULL,
      {
         { "0", OPTION_VAL_0_AST},
         { "1", OPTION_VAL_1_AST},
         { "2", OPTION_VAL_2_AST},
         { NULL, NULL },
      },
      "0"
   },

   { 
      "q88_cpu_clock", 
      Q88_CPU_CLOCK_LABEL_AST,
      NULL, 
      Q88_CPU_CLOCK_INFO_0_AST,
      NULL,
      NULL,
      {
         { "4",  OPTION_VAL_4_AST },
         { "8",  OPTION_VAL_8_AST },
         { "16", OPTION_VAL_16_AST },
         { "32", OPTION_VAL_32_AST },
         { "64", OPTION_VAL_64_AST },
         { "1",  OPTION_VAL_1_O2_AST },
         { "2",  OPTION_VAL_2_O2_AST },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      Q88_SOUND_BOARD_LABEL_AST,
      NULL, 
      Q88_SOUND_BOARD_INFO_0_AST,
      NULL,
      NULL,
      {
         { "OPN",  OPTION_VAL_OPN_AST },
         { "OPNA", OPTION_VAL_OPNA_AST},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      Q88_USE_FDC_WAIT_LABEL_AST,
      NULL, 
      Q88_USE_FDC_WAIT_INFO_0_AST,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_pcg-8100", 
      Q88_PCG_8100_LABEL_AST,
      NULL, 
      Q88_PCG_8100_INFO_0_AST,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   {
      "q88_save_to_disk_image", 
      Q88_SAVE_TO_DISK_IMAGE_LABEL_AST,
      NULL, 
      Q88_SAVE_TO_DISK_IMAGE_INFO_0_AST,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   { 
      "q88_rumble", 
      Q88_RUMBLE_LABEL_AST,
      NULL, 
      Q88_RUMBLE_INFO_0_AST,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_screen_size", 
      Q88_SCREEN_SIZE_LABEL_AST,
      NULL, 
#if defined (PSP)
      Q88_SCREEN_SIZE_INFO_0_AST,
#elif defined (_3DS)
      Q88_SCREEN_SIZE_INFO_1_AST,
#else
      Q88_SCREEN_SIZE_INFO_2_AST,
#endif
      NULL,
      NULL,
      {
         { "full",  OPTION_VAL_FULL_AST },
         { "half",  OPTION_VAL_HALF_AST },
         { NULL, NULL }
      },
#if defined (PSP) || defined (_3DS)
      "half"
#else
      "full"
#endif
   },

   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_ast = {
   option_cats_ast,
   option_defs_ast
};

/* RETRO_LANGUAGE_CA */

#define Q88_BASIC_MODE_LABEL_CA NULL
#define Q88_BASIC_MODE_INFO_0_CA NULL
#define OPTION_VAL_N88_V2_CA NULL
#define OPTION_VAL_N88_V1H_CA NULL
#define OPTION_VAL_N88_V1S_CA NULL
#define OPTION_VAL_N_CA NULL
#define Q88_SUB_CPU_MODE_LABEL_CA NULL
#define Q88_SUB_CPU_MODE_INFO_0_CA NULL
#define OPTION_VAL_0_CA NULL
#define OPTION_VAL_1_CA NULL
#define OPTION_VAL_2_CA NULL
#define Q88_CPU_CLOCK_LABEL_CA NULL
#define Q88_CPU_CLOCK_INFO_0_CA NULL
#define OPTION_VAL_4_CA NULL
#define OPTION_VAL_8_CA NULL
#define OPTION_VAL_16_CA NULL
#define OPTION_VAL_32_CA NULL
#define OPTION_VAL_64_CA NULL
#define OPTION_VAL_1_O2_CA NULL
#define OPTION_VAL_2_O2_CA NULL
#define Q88_SOUND_BOARD_LABEL_CA NULL
#define Q88_SOUND_BOARD_INFO_0_CA NULL
#define OPTION_VAL_OPN_CA NULL
#define OPTION_VAL_OPNA_CA NULL
#define Q88_USE_FDC_WAIT_LABEL_CA NULL
#define Q88_USE_FDC_WAIT_INFO_0_CA NULL
#define Q88_PCG_8100_LABEL_CA NULL
#define Q88_PCG_8100_INFO_0_CA NULL
#define Q88_SAVE_TO_DISK_IMAGE_LABEL_CA NULL
#define Q88_SAVE_TO_DISK_IMAGE_INFO_0_CA NULL
#define Q88_RUMBLE_LABEL_CA NULL
#define Q88_RUMBLE_INFO_0_CA NULL
#define Q88_SCREEN_SIZE_LABEL_CA NULL
#define Q88_SCREEN_SIZE_INFO_0_CA NULL
#define Q88_SCREEN_SIZE_INFO_1_CA NULL
#define Q88_SCREEN_SIZE_INFO_2_CA NULL
#define OPTION_VAL_FULL_CA NULL
#define OPTION_VAL_HALF_CA NULL

struct retro_core_option_v2_category option_cats_ca[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_ca[] = {
   { 
      "q88_basic_mode", 
      Q88_BASIC_MODE_LABEL_CA,
      NULL, 
      Q88_BASIC_MODE_INFO_0_CA,
      NULL,
      NULL,
      {
         { "N88 V2",  OPTION_VAL_N88_V2_CA },
         { "N88 V1H", OPTION_VAL_N88_V1H_CA },
         { "N88 V1S", OPTION_VAL_N88_V1S_CA },
         { "N",       OPTION_VAL_N_CA },
         { NULL, NULL }
      },
      "N88 V2"
   },

   { 
      "q88_sub_cpu_mode",
      Q88_SUB_CPU_MODE_LABEL_CA,
      NULL,
      Q88_SUB_CPU_MODE_INFO_0_CA,
      NULL,
      NULL,
      {
         { "0", OPTION_VAL_0_CA},
         { "1", OPTION_VAL_1_CA},
         { "2", OPTION_VAL_2_CA},
         { NULL, NULL },
      },
      "0"
   },

   { 
      "q88_cpu_clock", 
      Q88_CPU_CLOCK_LABEL_CA,
      NULL, 
      Q88_CPU_CLOCK_INFO_0_CA,
      NULL,
      NULL,
      {
         { "4",  OPTION_VAL_4_CA },
         { "8",  OPTION_VAL_8_CA },
         { "16", OPTION_VAL_16_CA },
         { "32", OPTION_VAL_32_CA },
         { "64", OPTION_VAL_64_CA },
         { "1",  OPTION_VAL_1_O2_CA },
         { "2",  OPTION_VAL_2_O2_CA },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      Q88_SOUND_BOARD_LABEL_CA,
      NULL, 
      Q88_SOUND_BOARD_INFO_0_CA,
      NULL,
      NULL,
      {
         { "OPN",  OPTION_VAL_OPN_CA },
         { "OPNA", OPTION_VAL_OPNA_CA},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      Q88_USE_FDC_WAIT_LABEL_CA,
      NULL, 
      Q88_USE_FDC_WAIT_INFO_0_CA,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_pcg-8100", 
      Q88_PCG_8100_LABEL_CA,
      NULL, 
      Q88_PCG_8100_INFO_0_CA,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   {
      "q88_save_to_disk_image", 
      Q88_SAVE_TO_DISK_IMAGE_LABEL_CA,
      NULL, 
      Q88_SAVE_TO_DISK_IMAGE_INFO_0_CA,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   { 
      "q88_rumble", 
      Q88_RUMBLE_LABEL_CA,
      NULL, 
      Q88_RUMBLE_INFO_0_CA,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_screen_size", 
      Q88_SCREEN_SIZE_LABEL_CA,
      NULL, 
#if defined (PSP)
      Q88_SCREEN_SIZE_INFO_0_CA,
#elif defined (_3DS)
      Q88_SCREEN_SIZE_INFO_1_CA,
#else
      Q88_SCREEN_SIZE_INFO_2_CA,
#endif
      NULL,
      NULL,
      {
         { "full",  OPTION_VAL_FULL_CA },
         { "half",  OPTION_VAL_HALF_CA },
         { NULL, NULL }
      },
#if defined (PSP) || defined (_3DS)
      "half"
#else
      "full"
#endif
   },

   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_ca = {
   option_cats_ca,
   option_defs_ca
};

/* RETRO_LANGUAGE_CHS */

#define Q88_BASIC_MODE_LABEL_CHS NULL
#define Q88_BASIC_MODE_INFO_0_CHS NULL
#define OPTION_VAL_N88_V2_CHS NULL
#define OPTION_VAL_N88_V1H_CHS NULL
#define OPTION_VAL_N88_V1S_CHS NULL
#define OPTION_VAL_N_CHS NULL
#define Q88_SUB_CPU_MODE_LABEL_CHS NULL
#define Q88_SUB_CPU_MODE_INFO_0_CHS NULL
#define OPTION_VAL_0_CHS NULL
#define OPTION_VAL_1_CHS NULL
#define OPTION_VAL_2_CHS NULL
#define Q88_CPU_CLOCK_LABEL_CHS NULL
#define Q88_CPU_CLOCK_INFO_0_CHS NULL
#define OPTION_VAL_4_CHS NULL
#define OPTION_VAL_8_CHS NULL
#define OPTION_VAL_16_CHS NULL
#define OPTION_VAL_32_CHS NULL
#define OPTION_VAL_64_CHS NULL
#define OPTION_VAL_1_O2_CHS NULL
#define OPTION_VAL_2_O2_CHS NULL
#define Q88_SOUND_BOARD_LABEL_CHS NULL
#define Q88_SOUND_BOARD_INFO_0_CHS NULL
#define OPTION_VAL_OPN_CHS NULL
#define OPTION_VAL_OPNA_CHS NULL
#define Q88_USE_FDC_WAIT_LABEL_CHS NULL
#define Q88_USE_FDC_WAIT_INFO_0_CHS NULL
#define Q88_PCG_8100_LABEL_CHS NULL
#define Q88_PCG_8100_INFO_0_CHS NULL
#define Q88_SAVE_TO_DISK_IMAGE_LABEL_CHS NULL
#define Q88_SAVE_TO_DISK_IMAGE_INFO_0_CHS NULL
#define Q88_RUMBLE_LABEL_CHS NULL
#define Q88_RUMBLE_INFO_0_CHS NULL
#define Q88_SCREEN_SIZE_LABEL_CHS NULL
#define Q88_SCREEN_SIZE_INFO_0_CHS NULL
#define Q88_SCREEN_SIZE_INFO_1_CHS NULL
#define Q88_SCREEN_SIZE_INFO_2_CHS NULL
#define OPTION_VAL_FULL_CHS NULL
#define OPTION_VAL_HALF_CHS NULL

struct retro_core_option_v2_category option_cats_chs[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_chs[] = {
   { 
      "q88_basic_mode", 
      Q88_BASIC_MODE_LABEL_CHS,
      NULL, 
      Q88_BASIC_MODE_INFO_0_CHS,
      NULL,
      NULL,
      {
         { "N88 V2",  OPTION_VAL_N88_V2_CHS },
         { "N88 V1H", OPTION_VAL_N88_V1H_CHS },
         { "N88 V1S", OPTION_VAL_N88_V1S_CHS },
         { "N",       OPTION_VAL_N_CHS },
         { NULL, NULL }
      },
      "N88 V2"
   },

   { 
      "q88_sub_cpu_mode",
      Q88_SUB_CPU_MODE_LABEL_CHS,
      NULL,
      Q88_SUB_CPU_MODE_INFO_0_CHS,
      NULL,
      NULL,
      {
         { "0", OPTION_VAL_0_CHS},
         { "1", OPTION_VAL_1_CHS},
         { "2", OPTION_VAL_2_CHS},
         { NULL, NULL },
      },
      "0"
   },

   { 
      "q88_cpu_clock", 
      Q88_CPU_CLOCK_LABEL_CHS,
      NULL, 
      Q88_CPU_CLOCK_INFO_0_CHS,
      NULL,
      NULL,
      {
         { "4",  OPTION_VAL_4_CHS },
         { "8",  OPTION_VAL_8_CHS },
         { "16", OPTION_VAL_16_CHS },
         { "32", OPTION_VAL_32_CHS },
         { "64", OPTION_VAL_64_CHS },
         { "1",  OPTION_VAL_1_O2_CHS },
         { "2",  OPTION_VAL_2_O2_CHS },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      Q88_SOUND_BOARD_LABEL_CHS,
      NULL, 
      Q88_SOUND_BOARD_INFO_0_CHS,
      NULL,
      NULL,
      {
         { "OPN",  OPTION_VAL_OPN_CHS },
         { "OPNA", OPTION_VAL_OPNA_CHS},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      Q88_USE_FDC_WAIT_LABEL_CHS,
      NULL, 
      Q88_USE_FDC_WAIT_INFO_0_CHS,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_pcg-8100", 
      Q88_PCG_8100_LABEL_CHS,
      NULL, 
      Q88_PCG_8100_INFO_0_CHS,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   {
      "q88_save_to_disk_image", 
      Q88_SAVE_TO_DISK_IMAGE_LABEL_CHS,
      NULL, 
      Q88_SAVE_TO_DISK_IMAGE_INFO_0_CHS,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   { 
      "q88_rumble", 
      Q88_RUMBLE_LABEL_CHS,
      NULL, 
      Q88_RUMBLE_INFO_0_CHS,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_screen_size", 
      Q88_SCREEN_SIZE_LABEL_CHS,
      NULL, 
#if defined (PSP)
      Q88_SCREEN_SIZE_INFO_0_CHS,
#elif defined (_3DS)
      Q88_SCREEN_SIZE_INFO_1_CHS,
#else
      Q88_SCREEN_SIZE_INFO_2_CHS,
#endif
      NULL,
      NULL,
      {
         { "full",  OPTION_VAL_FULL_CHS },
         { "half",  OPTION_VAL_HALF_CHS },
         { NULL, NULL }
      },
#if defined (PSP) || defined (_3DS)
      "half"
#else
      "full"
#endif
   },

   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_chs = {
   option_cats_chs,
   option_defs_chs
};

/* RETRO_LANGUAGE_CHT */

#define Q88_BASIC_MODE_LABEL_CHT NULL
#define Q88_BASIC_MODE_INFO_0_CHT NULL
#define OPTION_VAL_N88_V2_CHT NULL
#define OPTION_VAL_N88_V1H_CHT NULL
#define OPTION_VAL_N88_V1S_CHT NULL
#define OPTION_VAL_N_CHT NULL
#define Q88_SUB_CPU_MODE_LABEL_CHT NULL
#define Q88_SUB_CPU_MODE_INFO_0_CHT NULL
#define OPTION_VAL_0_CHT NULL
#define OPTION_VAL_1_CHT NULL
#define OPTION_VAL_2_CHT NULL
#define Q88_CPU_CLOCK_LABEL_CHT NULL
#define Q88_CPU_CLOCK_INFO_0_CHT NULL
#define OPTION_VAL_4_CHT NULL
#define OPTION_VAL_8_CHT NULL
#define OPTION_VAL_16_CHT NULL
#define OPTION_VAL_32_CHT NULL
#define OPTION_VAL_64_CHT NULL
#define OPTION_VAL_1_O2_CHT NULL
#define OPTION_VAL_2_O2_CHT NULL
#define Q88_SOUND_BOARD_LABEL_CHT NULL
#define Q88_SOUND_BOARD_INFO_0_CHT NULL
#define OPTION_VAL_OPN_CHT NULL
#define OPTION_VAL_OPNA_CHT NULL
#define Q88_USE_FDC_WAIT_LABEL_CHT NULL
#define Q88_USE_FDC_WAIT_INFO_0_CHT NULL
#define Q88_PCG_8100_LABEL_CHT NULL
#define Q88_PCG_8100_INFO_0_CHT NULL
#define Q88_SAVE_TO_DISK_IMAGE_LABEL_CHT NULL
#define Q88_SAVE_TO_DISK_IMAGE_INFO_0_CHT NULL
#define Q88_RUMBLE_LABEL_CHT NULL
#define Q88_RUMBLE_INFO_0_CHT NULL
#define Q88_SCREEN_SIZE_LABEL_CHT NULL
#define Q88_SCREEN_SIZE_INFO_0_CHT NULL
#define Q88_SCREEN_SIZE_INFO_1_CHT NULL
#define Q88_SCREEN_SIZE_INFO_2_CHT NULL
#define OPTION_VAL_FULL_CHT NULL
#define OPTION_VAL_HALF_CHT NULL

struct retro_core_option_v2_category option_cats_cht[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_cht[] = {
   { 
      "q88_basic_mode", 
      Q88_BASIC_MODE_LABEL_CHT,
      NULL, 
      Q88_BASIC_MODE_INFO_0_CHT,
      NULL,
      NULL,
      {
         { "N88 V2",  OPTION_VAL_N88_V2_CHT },
         { "N88 V1H", OPTION_VAL_N88_V1H_CHT },
         { "N88 V1S", OPTION_VAL_N88_V1S_CHT },
         { "N",       OPTION_VAL_N_CHT },
         { NULL, NULL }
      },
      "N88 V2"
   },

   { 
      "q88_sub_cpu_mode",
      Q88_SUB_CPU_MODE_LABEL_CHT,
      NULL,
      Q88_SUB_CPU_MODE_INFO_0_CHT,
      NULL,
      NULL,
      {
         { "0", OPTION_VAL_0_CHT},
         { "1", OPTION_VAL_1_CHT},
         { "2", OPTION_VAL_2_CHT},
         { NULL, NULL },
      },
      "0"
   },

   { 
      "q88_cpu_clock", 
      Q88_CPU_CLOCK_LABEL_CHT,
      NULL, 
      Q88_CPU_CLOCK_INFO_0_CHT,
      NULL,
      NULL,
      {
         { "4",  OPTION_VAL_4_CHT },
         { "8",  OPTION_VAL_8_CHT },
         { "16", OPTION_VAL_16_CHT },
         { "32", OPTION_VAL_32_CHT },
         { "64", OPTION_VAL_64_CHT },
         { "1",  OPTION_VAL_1_O2_CHT },
         { "2",  OPTION_VAL_2_O2_CHT },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      Q88_SOUND_BOARD_LABEL_CHT,
      NULL, 
      Q88_SOUND_BOARD_INFO_0_CHT,
      NULL,
      NULL,
      {
         { "OPN",  OPTION_VAL_OPN_CHT },
         { "OPNA", OPTION_VAL_OPNA_CHT},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      Q88_USE_FDC_WAIT_LABEL_CHT,
      NULL, 
      Q88_USE_FDC_WAIT_INFO_0_CHT,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_pcg-8100", 
      Q88_PCG_8100_LABEL_CHT,
      NULL, 
      Q88_PCG_8100_INFO_0_CHT,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   {
      "q88_save_to_disk_image", 
      Q88_SAVE_TO_DISK_IMAGE_LABEL_CHT,
      NULL, 
      Q88_SAVE_TO_DISK_IMAGE_INFO_0_CHT,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   { 
      "q88_rumble", 
      Q88_RUMBLE_LABEL_CHT,
      NULL, 
      Q88_RUMBLE_INFO_0_CHT,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_screen_size", 
      Q88_SCREEN_SIZE_LABEL_CHT,
      NULL, 
#if defined (PSP)
      Q88_SCREEN_SIZE_INFO_0_CHT,
#elif defined (_3DS)
      Q88_SCREEN_SIZE_INFO_1_CHT,
#else
      Q88_SCREEN_SIZE_INFO_2_CHT,
#endif
      NULL,
      NULL,
      {
         { "full",  OPTION_VAL_FULL_CHT },
         { "half",  OPTION_VAL_HALF_CHT },
         { NULL, NULL }
      },
#if defined (PSP) || defined (_3DS)
      "half"
#else
      "full"
#endif
   },

   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_cht = {
   option_cats_cht,
   option_defs_cht
};

/* RETRO_LANGUAGE_CS */

#define Q88_BASIC_MODE_LABEL_CS NULL
#define Q88_BASIC_MODE_INFO_0_CS NULL
#define OPTION_VAL_N88_V2_CS NULL
#define OPTION_VAL_N88_V1H_CS NULL
#define OPTION_VAL_N88_V1S_CS NULL
#define OPTION_VAL_N_CS NULL
#define Q88_SUB_CPU_MODE_LABEL_CS NULL
#define Q88_SUB_CPU_MODE_INFO_0_CS NULL
#define OPTION_VAL_0_CS NULL
#define OPTION_VAL_1_CS NULL
#define OPTION_VAL_2_CS NULL
#define Q88_CPU_CLOCK_LABEL_CS NULL
#define Q88_CPU_CLOCK_INFO_0_CS NULL
#define OPTION_VAL_4_CS NULL
#define OPTION_VAL_8_CS NULL
#define OPTION_VAL_16_CS NULL
#define OPTION_VAL_32_CS NULL
#define OPTION_VAL_64_CS NULL
#define OPTION_VAL_1_O2_CS NULL
#define OPTION_VAL_2_O2_CS NULL
#define Q88_SOUND_BOARD_LABEL_CS NULL
#define Q88_SOUND_BOARD_INFO_0_CS NULL
#define OPTION_VAL_OPN_CS NULL
#define OPTION_VAL_OPNA_CS NULL
#define Q88_USE_FDC_WAIT_LABEL_CS NULL
#define Q88_USE_FDC_WAIT_INFO_0_CS NULL
#define Q88_PCG_8100_LABEL_CS NULL
#define Q88_PCG_8100_INFO_0_CS NULL
#define Q88_SAVE_TO_DISK_IMAGE_LABEL_CS NULL
#define Q88_SAVE_TO_DISK_IMAGE_INFO_0_CS NULL
#define Q88_RUMBLE_LABEL_CS NULL
#define Q88_RUMBLE_INFO_0_CS NULL
#define Q88_SCREEN_SIZE_LABEL_CS NULL
#define Q88_SCREEN_SIZE_INFO_0_CS NULL
#define Q88_SCREEN_SIZE_INFO_1_CS NULL
#define Q88_SCREEN_SIZE_INFO_2_CS NULL
#define OPTION_VAL_FULL_CS NULL
#define OPTION_VAL_HALF_CS NULL

struct retro_core_option_v2_category option_cats_cs[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_cs[] = {
   { 
      "q88_basic_mode", 
      Q88_BASIC_MODE_LABEL_CS,
      NULL, 
      Q88_BASIC_MODE_INFO_0_CS,
      NULL,
      NULL,
      {
         { "N88 V2",  OPTION_VAL_N88_V2_CS },
         { "N88 V1H", OPTION_VAL_N88_V1H_CS },
         { "N88 V1S", OPTION_VAL_N88_V1S_CS },
         { "N",       OPTION_VAL_N_CS },
         { NULL, NULL }
      },
      "N88 V2"
   },

   { 
      "q88_sub_cpu_mode",
      Q88_SUB_CPU_MODE_LABEL_CS,
      NULL,
      Q88_SUB_CPU_MODE_INFO_0_CS,
      NULL,
      NULL,
      {
         { "0", OPTION_VAL_0_CS},
         { "1", OPTION_VAL_1_CS},
         { "2", OPTION_VAL_2_CS},
         { NULL, NULL },
      },
      "0"
   },

   { 
      "q88_cpu_clock", 
      Q88_CPU_CLOCK_LABEL_CS,
      NULL, 
      Q88_CPU_CLOCK_INFO_0_CS,
      NULL,
      NULL,
      {
         { "4",  OPTION_VAL_4_CS },
         { "8",  OPTION_VAL_8_CS },
         { "16", OPTION_VAL_16_CS },
         { "32", OPTION_VAL_32_CS },
         { "64", OPTION_VAL_64_CS },
         { "1",  OPTION_VAL_1_O2_CS },
         { "2",  OPTION_VAL_2_O2_CS },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      Q88_SOUND_BOARD_LABEL_CS,
      NULL, 
      Q88_SOUND_BOARD_INFO_0_CS,
      NULL,
      NULL,
      {
         { "OPN",  OPTION_VAL_OPN_CS },
         { "OPNA", OPTION_VAL_OPNA_CS},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      Q88_USE_FDC_WAIT_LABEL_CS,
      NULL, 
      Q88_USE_FDC_WAIT_INFO_0_CS,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_pcg-8100", 
      Q88_PCG_8100_LABEL_CS,
      NULL, 
      Q88_PCG_8100_INFO_0_CS,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   {
      "q88_save_to_disk_image", 
      Q88_SAVE_TO_DISK_IMAGE_LABEL_CS,
      NULL, 
      Q88_SAVE_TO_DISK_IMAGE_INFO_0_CS,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   { 
      "q88_rumble", 
      Q88_RUMBLE_LABEL_CS,
      NULL, 
      Q88_RUMBLE_INFO_0_CS,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_screen_size", 
      Q88_SCREEN_SIZE_LABEL_CS,
      NULL, 
#if defined (PSP)
      Q88_SCREEN_SIZE_INFO_0_CS,
#elif defined (_3DS)
      Q88_SCREEN_SIZE_INFO_1_CS,
#else
      Q88_SCREEN_SIZE_INFO_2_CS,
#endif
      NULL,
      NULL,
      {
         { "full",  OPTION_VAL_FULL_CS },
         { "half",  OPTION_VAL_HALF_CS },
         { NULL, NULL }
      },
#if defined (PSP) || defined (_3DS)
      "half"
#else
      "full"
#endif
   },

   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_cs = {
   option_cats_cs,
   option_defs_cs
};

/* RETRO_LANGUAGE_CY */

#define Q88_BASIC_MODE_LABEL_CY NULL
#define Q88_BASIC_MODE_INFO_0_CY NULL
#define OPTION_VAL_N88_V2_CY NULL
#define OPTION_VAL_N88_V1H_CY NULL
#define OPTION_VAL_N88_V1S_CY NULL
#define OPTION_VAL_N_CY NULL
#define Q88_SUB_CPU_MODE_LABEL_CY NULL
#define Q88_SUB_CPU_MODE_INFO_0_CY NULL
#define OPTION_VAL_0_CY NULL
#define OPTION_VAL_1_CY NULL
#define OPTION_VAL_2_CY NULL
#define Q88_CPU_CLOCK_LABEL_CY NULL
#define Q88_CPU_CLOCK_INFO_0_CY NULL
#define OPTION_VAL_4_CY NULL
#define OPTION_VAL_8_CY NULL
#define OPTION_VAL_16_CY NULL
#define OPTION_VAL_32_CY NULL
#define OPTION_VAL_64_CY NULL
#define OPTION_VAL_1_O2_CY NULL
#define OPTION_VAL_2_O2_CY NULL
#define Q88_SOUND_BOARD_LABEL_CY NULL
#define Q88_SOUND_BOARD_INFO_0_CY NULL
#define OPTION_VAL_OPN_CY NULL
#define OPTION_VAL_OPNA_CY NULL
#define Q88_USE_FDC_WAIT_LABEL_CY NULL
#define Q88_USE_FDC_WAIT_INFO_0_CY NULL
#define Q88_PCG_8100_LABEL_CY NULL
#define Q88_PCG_8100_INFO_0_CY NULL
#define Q88_SAVE_TO_DISK_IMAGE_LABEL_CY NULL
#define Q88_SAVE_TO_DISK_IMAGE_INFO_0_CY NULL
#define Q88_RUMBLE_LABEL_CY NULL
#define Q88_RUMBLE_INFO_0_CY NULL
#define Q88_SCREEN_SIZE_LABEL_CY NULL
#define Q88_SCREEN_SIZE_INFO_0_CY NULL
#define Q88_SCREEN_SIZE_INFO_1_CY NULL
#define Q88_SCREEN_SIZE_INFO_2_CY NULL
#define OPTION_VAL_FULL_CY NULL
#define OPTION_VAL_HALF_CY NULL

struct retro_core_option_v2_category option_cats_cy[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_cy[] = {
   { 
      "q88_basic_mode", 
      Q88_BASIC_MODE_LABEL_CY,
      NULL, 
      Q88_BASIC_MODE_INFO_0_CY,
      NULL,
      NULL,
      {
         { "N88 V2",  OPTION_VAL_N88_V2_CY },
         { "N88 V1H", OPTION_VAL_N88_V1H_CY },
         { "N88 V1S", OPTION_VAL_N88_V1S_CY },
         { "N",       OPTION_VAL_N_CY },
         { NULL, NULL }
      },
      "N88 V2"
   },

   { 
      "q88_sub_cpu_mode",
      Q88_SUB_CPU_MODE_LABEL_CY,
      NULL,
      Q88_SUB_CPU_MODE_INFO_0_CY,
      NULL,
      NULL,
      {
         { "0", OPTION_VAL_0_CY},
         { "1", OPTION_VAL_1_CY},
         { "2", OPTION_VAL_2_CY},
         { NULL, NULL },
      },
      "0"
   },

   { 
      "q88_cpu_clock", 
      Q88_CPU_CLOCK_LABEL_CY,
      NULL, 
      Q88_CPU_CLOCK_INFO_0_CY,
      NULL,
      NULL,
      {
         { "4",  OPTION_VAL_4_CY },
         { "8",  OPTION_VAL_8_CY },
         { "16", OPTION_VAL_16_CY },
         { "32", OPTION_VAL_32_CY },
         { "64", OPTION_VAL_64_CY },
         { "1",  OPTION_VAL_1_O2_CY },
         { "2",  OPTION_VAL_2_O2_CY },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      Q88_SOUND_BOARD_LABEL_CY,
      NULL, 
      Q88_SOUND_BOARD_INFO_0_CY,
      NULL,
      NULL,
      {
         { "OPN",  OPTION_VAL_OPN_CY },
         { "OPNA", OPTION_VAL_OPNA_CY},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      Q88_USE_FDC_WAIT_LABEL_CY,
      NULL, 
      Q88_USE_FDC_WAIT_INFO_0_CY,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_pcg-8100", 
      Q88_PCG_8100_LABEL_CY,
      NULL, 
      Q88_PCG_8100_INFO_0_CY,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   {
      "q88_save_to_disk_image", 
      Q88_SAVE_TO_DISK_IMAGE_LABEL_CY,
      NULL, 
      Q88_SAVE_TO_DISK_IMAGE_INFO_0_CY,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   { 
      "q88_rumble", 
      Q88_RUMBLE_LABEL_CY,
      NULL, 
      Q88_RUMBLE_INFO_0_CY,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_screen_size", 
      Q88_SCREEN_SIZE_LABEL_CY,
      NULL, 
#if defined (PSP)
      Q88_SCREEN_SIZE_INFO_0_CY,
#elif defined (_3DS)
      Q88_SCREEN_SIZE_INFO_1_CY,
#else
      Q88_SCREEN_SIZE_INFO_2_CY,
#endif
      NULL,
      NULL,
      {
         { "full",  OPTION_VAL_FULL_CY },
         { "half",  OPTION_VAL_HALF_CY },
         { NULL, NULL }
      },
#if defined (PSP) || defined (_3DS)
      "half"
#else
      "full"
#endif
   },

   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_cy = {
   option_cats_cy,
   option_defs_cy
};

/* RETRO_LANGUAGE_DA */

#define Q88_BASIC_MODE_LABEL_DA NULL
#define Q88_BASIC_MODE_INFO_0_DA NULL
#define OPTION_VAL_N88_V2_DA NULL
#define OPTION_VAL_N88_V1H_DA NULL
#define OPTION_VAL_N88_V1S_DA NULL
#define OPTION_VAL_N_DA NULL
#define Q88_SUB_CPU_MODE_LABEL_DA NULL
#define Q88_SUB_CPU_MODE_INFO_0_DA NULL
#define OPTION_VAL_0_DA NULL
#define OPTION_VAL_1_DA NULL
#define OPTION_VAL_2_DA NULL
#define Q88_CPU_CLOCK_LABEL_DA NULL
#define Q88_CPU_CLOCK_INFO_0_DA NULL
#define OPTION_VAL_4_DA NULL
#define OPTION_VAL_8_DA NULL
#define OPTION_VAL_16_DA NULL
#define OPTION_VAL_32_DA NULL
#define OPTION_VAL_64_DA NULL
#define OPTION_VAL_1_O2_DA NULL
#define OPTION_VAL_2_O2_DA NULL
#define Q88_SOUND_BOARD_LABEL_DA NULL
#define Q88_SOUND_BOARD_INFO_0_DA NULL
#define OPTION_VAL_OPN_DA NULL
#define OPTION_VAL_OPNA_DA NULL
#define Q88_USE_FDC_WAIT_LABEL_DA NULL
#define Q88_USE_FDC_WAIT_INFO_0_DA NULL
#define Q88_PCG_8100_LABEL_DA NULL
#define Q88_PCG_8100_INFO_0_DA NULL
#define Q88_SAVE_TO_DISK_IMAGE_LABEL_DA NULL
#define Q88_SAVE_TO_DISK_IMAGE_INFO_0_DA NULL
#define Q88_RUMBLE_LABEL_DA NULL
#define Q88_RUMBLE_INFO_0_DA NULL
#define Q88_SCREEN_SIZE_LABEL_DA NULL
#define Q88_SCREEN_SIZE_INFO_0_DA NULL
#define Q88_SCREEN_SIZE_INFO_1_DA NULL
#define Q88_SCREEN_SIZE_INFO_2_DA NULL
#define OPTION_VAL_FULL_DA NULL
#define OPTION_VAL_HALF_DA NULL

struct retro_core_option_v2_category option_cats_da[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_da[] = {
   { 
      "q88_basic_mode", 
      Q88_BASIC_MODE_LABEL_DA,
      NULL, 
      Q88_BASIC_MODE_INFO_0_DA,
      NULL,
      NULL,
      {
         { "N88 V2",  OPTION_VAL_N88_V2_DA },
         { "N88 V1H", OPTION_VAL_N88_V1H_DA },
         { "N88 V1S", OPTION_VAL_N88_V1S_DA },
         { "N",       OPTION_VAL_N_DA },
         { NULL, NULL }
      },
      "N88 V2"
   },

   { 
      "q88_sub_cpu_mode",
      Q88_SUB_CPU_MODE_LABEL_DA,
      NULL,
      Q88_SUB_CPU_MODE_INFO_0_DA,
      NULL,
      NULL,
      {
         { "0", OPTION_VAL_0_DA},
         { "1", OPTION_VAL_1_DA},
         { "2", OPTION_VAL_2_DA},
         { NULL, NULL },
      },
      "0"
   },

   { 
      "q88_cpu_clock", 
      Q88_CPU_CLOCK_LABEL_DA,
      NULL, 
      Q88_CPU_CLOCK_INFO_0_DA,
      NULL,
      NULL,
      {
         { "4",  OPTION_VAL_4_DA },
         { "8",  OPTION_VAL_8_DA },
         { "16", OPTION_VAL_16_DA },
         { "32", OPTION_VAL_32_DA },
         { "64", OPTION_VAL_64_DA },
         { "1",  OPTION_VAL_1_O2_DA },
         { "2",  OPTION_VAL_2_O2_DA },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      Q88_SOUND_BOARD_LABEL_DA,
      NULL, 
      Q88_SOUND_BOARD_INFO_0_DA,
      NULL,
      NULL,
      {
         { "OPN",  OPTION_VAL_OPN_DA },
         { "OPNA", OPTION_VAL_OPNA_DA},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      Q88_USE_FDC_WAIT_LABEL_DA,
      NULL, 
      Q88_USE_FDC_WAIT_INFO_0_DA,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_pcg-8100", 
      Q88_PCG_8100_LABEL_DA,
      NULL, 
      Q88_PCG_8100_INFO_0_DA,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   {
      "q88_save_to_disk_image", 
      Q88_SAVE_TO_DISK_IMAGE_LABEL_DA,
      NULL, 
      Q88_SAVE_TO_DISK_IMAGE_INFO_0_DA,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   { 
      "q88_rumble", 
      Q88_RUMBLE_LABEL_DA,
      NULL, 
      Q88_RUMBLE_INFO_0_DA,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_screen_size", 
      Q88_SCREEN_SIZE_LABEL_DA,
      NULL, 
#if defined (PSP)
      Q88_SCREEN_SIZE_INFO_0_DA,
#elif defined (_3DS)
      Q88_SCREEN_SIZE_INFO_1_DA,
#else
      Q88_SCREEN_SIZE_INFO_2_DA,
#endif
      NULL,
      NULL,
      {
         { "full",  OPTION_VAL_FULL_DA },
         { "half",  OPTION_VAL_HALF_DA },
         { NULL, NULL }
      },
#if defined (PSP) || defined (_3DS)
      "half"
#else
      "full"
#endif
   },

   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_da = {
   option_cats_da,
   option_defs_da
};

/* RETRO_LANGUAGE_DE */

#define Q88_BASIC_MODE_LABEL_DE NULL
#define Q88_BASIC_MODE_INFO_0_DE NULL
#define OPTION_VAL_N88_V2_DE NULL
#define OPTION_VAL_N88_V1H_DE NULL
#define OPTION_VAL_N88_V1S_DE NULL
#define OPTION_VAL_N_DE NULL
#define Q88_SUB_CPU_MODE_LABEL_DE NULL
#define Q88_SUB_CPU_MODE_INFO_0_DE NULL
#define OPTION_VAL_0_DE NULL
#define OPTION_VAL_1_DE NULL
#define OPTION_VAL_2_DE NULL
#define Q88_CPU_CLOCK_LABEL_DE NULL
#define Q88_CPU_CLOCK_INFO_0_DE NULL
#define OPTION_VAL_4_DE NULL
#define OPTION_VAL_8_DE NULL
#define OPTION_VAL_16_DE NULL
#define OPTION_VAL_32_DE NULL
#define OPTION_VAL_64_DE NULL
#define OPTION_VAL_1_O2_DE NULL
#define OPTION_VAL_2_O2_DE NULL
#define Q88_SOUND_BOARD_LABEL_DE NULL
#define Q88_SOUND_BOARD_INFO_0_DE NULL
#define OPTION_VAL_OPN_DE NULL
#define OPTION_VAL_OPNA_DE NULL
#define Q88_USE_FDC_WAIT_LABEL_DE NULL
#define Q88_USE_FDC_WAIT_INFO_0_DE NULL
#define Q88_PCG_8100_LABEL_DE NULL
#define Q88_PCG_8100_INFO_0_DE NULL
#define Q88_SAVE_TO_DISK_IMAGE_LABEL_DE NULL
#define Q88_SAVE_TO_DISK_IMAGE_INFO_0_DE NULL
#define Q88_RUMBLE_LABEL_DE NULL
#define Q88_RUMBLE_INFO_0_DE NULL
#define Q88_SCREEN_SIZE_LABEL_DE NULL
#define Q88_SCREEN_SIZE_INFO_0_DE NULL
#define Q88_SCREEN_SIZE_INFO_1_DE NULL
#define Q88_SCREEN_SIZE_INFO_2_DE NULL
#define OPTION_VAL_FULL_DE NULL
#define OPTION_VAL_HALF_DE NULL

struct retro_core_option_v2_category option_cats_de[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_de[] = {
   { 
      "q88_basic_mode", 
      Q88_BASIC_MODE_LABEL_DE,
      NULL, 
      Q88_BASIC_MODE_INFO_0_DE,
      NULL,
      NULL,
      {
         { "N88 V2",  OPTION_VAL_N88_V2_DE },
         { "N88 V1H", OPTION_VAL_N88_V1H_DE },
         { "N88 V1S", OPTION_VAL_N88_V1S_DE },
         { "N",       OPTION_VAL_N_DE },
         { NULL, NULL }
      },
      "N88 V2"
   },

   { 
      "q88_sub_cpu_mode",
      Q88_SUB_CPU_MODE_LABEL_DE,
      NULL,
      Q88_SUB_CPU_MODE_INFO_0_DE,
      NULL,
      NULL,
      {
         { "0", OPTION_VAL_0_DE},
         { "1", OPTION_VAL_1_DE},
         { "2", OPTION_VAL_2_DE},
         { NULL, NULL },
      },
      "0"
   },

   { 
      "q88_cpu_clock", 
      Q88_CPU_CLOCK_LABEL_DE,
      NULL, 
      Q88_CPU_CLOCK_INFO_0_DE,
      NULL,
      NULL,
      {
         { "4",  OPTION_VAL_4_DE },
         { "8",  OPTION_VAL_8_DE },
         { "16", OPTION_VAL_16_DE },
         { "32", OPTION_VAL_32_DE },
         { "64", OPTION_VAL_64_DE },
         { "1",  OPTION_VAL_1_O2_DE },
         { "2",  OPTION_VAL_2_O2_DE },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      Q88_SOUND_BOARD_LABEL_DE,
      NULL, 
      Q88_SOUND_BOARD_INFO_0_DE,
      NULL,
      NULL,
      {
         { "OPN",  OPTION_VAL_OPN_DE },
         { "OPNA", OPTION_VAL_OPNA_DE},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      Q88_USE_FDC_WAIT_LABEL_DE,
      NULL, 
      Q88_USE_FDC_WAIT_INFO_0_DE,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_pcg-8100", 
      Q88_PCG_8100_LABEL_DE,
      NULL, 
      Q88_PCG_8100_INFO_0_DE,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   {
      "q88_save_to_disk_image", 
      Q88_SAVE_TO_DISK_IMAGE_LABEL_DE,
      NULL, 
      Q88_SAVE_TO_DISK_IMAGE_INFO_0_DE,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   { 
      "q88_rumble", 
      Q88_RUMBLE_LABEL_DE,
      NULL, 
      Q88_RUMBLE_INFO_0_DE,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_screen_size", 
      Q88_SCREEN_SIZE_LABEL_DE,
      NULL, 
#if defined (PSP)
      Q88_SCREEN_SIZE_INFO_0_DE,
#elif defined (_3DS)
      Q88_SCREEN_SIZE_INFO_1_DE,
#else
      Q88_SCREEN_SIZE_INFO_2_DE,
#endif
      NULL,
      NULL,
      {
         { "full",  OPTION_VAL_FULL_DE },
         { "half",  OPTION_VAL_HALF_DE },
         { NULL, NULL }
      },
#if defined (PSP) || defined (_3DS)
      "half"
#else
      "full"
#endif
   },

   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_de = {
   option_cats_de,
   option_defs_de
};

/* RETRO_LANGUAGE_EL */

#define Q88_BASIC_MODE_LABEL_EL NULL
#define Q88_BASIC_MODE_INFO_0_EL NULL
#define OPTION_VAL_N88_V2_EL NULL
#define OPTION_VAL_N88_V1H_EL NULL
#define OPTION_VAL_N88_V1S_EL NULL
#define OPTION_VAL_N_EL NULL
#define Q88_SUB_CPU_MODE_LABEL_EL NULL
#define Q88_SUB_CPU_MODE_INFO_0_EL NULL
#define OPTION_VAL_0_EL NULL
#define OPTION_VAL_1_EL NULL
#define OPTION_VAL_2_EL NULL
#define Q88_CPU_CLOCK_LABEL_EL NULL
#define Q88_CPU_CLOCK_INFO_0_EL NULL
#define OPTION_VAL_4_EL NULL
#define OPTION_VAL_8_EL NULL
#define OPTION_VAL_16_EL NULL
#define OPTION_VAL_32_EL NULL
#define OPTION_VAL_64_EL NULL
#define OPTION_VAL_1_O2_EL NULL
#define OPTION_VAL_2_O2_EL NULL
#define Q88_SOUND_BOARD_LABEL_EL NULL
#define Q88_SOUND_BOARD_INFO_0_EL NULL
#define OPTION_VAL_OPN_EL NULL
#define OPTION_VAL_OPNA_EL NULL
#define Q88_USE_FDC_WAIT_LABEL_EL NULL
#define Q88_USE_FDC_WAIT_INFO_0_EL NULL
#define Q88_PCG_8100_LABEL_EL NULL
#define Q88_PCG_8100_INFO_0_EL NULL
#define Q88_SAVE_TO_DISK_IMAGE_LABEL_EL NULL
#define Q88_SAVE_TO_DISK_IMAGE_INFO_0_EL NULL
#define Q88_RUMBLE_LABEL_EL NULL
#define Q88_RUMBLE_INFO_0_EL NULL
#define Q88_SCREEN_SIZE_LABEL_EL NULL
#define Q88_SCREEN_SIZE_INFO_0_EL NULL
#define Q88_SCREEN_SIZE_INFO_1_EL NULL
#define Q88_SCREEN_SIZE_INFO_2_EL NULL
#define OPTION_VAL_FULL_EL NULL
#define OPTION_VAL_HALF_EL NULL

struct retro_core_option_v2_category option_cats_el[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_el[] = {
   { 
      "q88_basic_mode", 
      Q88_BASIC_MODE_LABEL_EL,
      NULL, 
      Q88_BASIC_MODE_INFO_0_EL,
      NULL,
      NULL,
      {
         { "N88 V2",  OPTION_VAL_N88_V2_EL },
         { "N88 V1H", OPTION_VAL_N88_V1H_EL },
         { "N88 V1S", OPTION_VAL_N88_V1S_EL },
         { "N",       OPTION_VAL_N_EL },
         { NULL, NULL }
      },
      "N88 V2"
   },

   { 
      "q88_sub_cpu_mode",
      Q88_SUB_CPU_MODE_LABEL_EL,
      NULL,
      Q88_SUB_CPU_MODE_INFO_0_EL,
      NULL,
      NULL,
      {
         { "0", OPTION_VAL_0_EL},
         { "1", OPTION_VAL_1_EL},
         { "2", OPTION_VAL_2_EL},
         { NULL, NULL },
      },
      "0"
   },

   { 
      "q88_cpu_clock", 
      Q88_CPU_CLOCK_LABEL_EL,
      NULL, 
      Q88_CPU_CLOCK_INFO_0_EL,
      NULL,
      NULL,
      {
         { "4",  OPTION_VAL_4_EL },
         { "8",  OPTION_VAL_8_EL },
         { "16", OPTION_VAL_16_EL },
         { "32", OPTION_VAL_32_EL },
         { "64", OPTION_VAL_64_EL },
         { "1",  OPTION_VAL_1_O2_EL },
         { "2",  OPTION_VAL_2_O2_EL },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      Q88_SOUND_BOARD_LABEL_EL,
      NULL, 
      Q88_SOUND_BOARD_INFO_0_EL,
      NULL,
      NULL,
      {
         { "OPN",  OPTION_VAL_OPN_EL },
         { "OPNA", OPTION_VAL_OPNA_EL},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      Q88_USE_FDC_WAIT_LABEL_EL,
      NULL, 
      Q88_USE_FDC_WAIT_INFO_0_EL,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_pcg-8100", 
      Q88_PCG_8100_LABEL_EL,
      NULL, 
      Q88_PCG_8100_INFO_0_EL,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   {
      "q88_save_to_disk_image", 
      Q88_SAVE_TO_DISK_IMAGE_LABEL_EL,
      NULL, 
      Q88_SAVE_TO_DISK_IMAGE_INFO_0_EL,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   { 
      "q88_rumble", 
      Q88_RUMBLE_LABEL_EL,
      NULL, 
      Q88_RUMBLE_INFO_0_EL,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_screen_size", 
      Q88_SCREEN_SIZE_LABEL_EL,
      NULL, 
#if defined (PSP)
      Q88_SCREEN_SIZE_INFO_0_EL,
#elif defined (_3DS)
      Q88_SCREEN_SIZE_INFO_1_EL,
#else
      Q88_SCREEN_SIZE_INFO_2_EL,
#endif
      NULL,
      NULL,
      {
         { "full",  OPTION_VAL_FULL_EL },
         { "half",  OPTION_VAL_HALF_EL },
         { NULL, NULL }
      },
#if defined (PSP) || defined (_3DS)
      "half"
#else
      "full"
#endif
   },

   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_el = {
   option_cats_el,
   option_defs_el
};

/* RETRO_LANGUAGE_EO */

#define Q88_BASIC_MODE_LABEL_EO NULL
#define Q88_BASIC_MODE_INFO_0_EO NULL
#define OPTION_VAL_N88_V2_EO NULL
#define OPTION_VAL_N88_V1H_EO NULL
#define OPTION_VAL_N88_V1S_EO NULL
#define OPTION_VAL_N_EO NULL
#define Q88_SUB_CPU_MODE_LABEL_EO NULL
#define Q88_SUB_CPU_MODE_INFO_0_EO NULL
#define OPTION_VAL_0_EO NULL
#define OPTION_VAL_1_EO NULL
#define OPTION_VAL_2_EO NULL
#define Q88_CPU_CLOCK_LABEL_EO NULL
#define Q88_CPU_CLOCK_INFO_0_EO NULL
#define OPTION_VAL_4_EO NULL
#define OPTION_VAL_8_EO NULL
#define OPTION_VAL_16_EO NULL
#define OPTION_VAL_32_EO NULL
#define OPTION_VAL_64_EO NULL
#define OPTION_VAL_1_O2_EO NULL
#define OPTION_VAL_2_O2_EO NULL
#define Q88_SOUND_BOARD_LABEL_EO NULL
#define Q88_SOUND_BOARD_INFO_0_EO NULL
#define OPTION_VAL_OPN_EO NULL
#define OPTION_VAL_OPNA_EO NULL
#define Q88_USE_FDC_WAIT_LABEL_EO NULL
#define Q88_USE_FDC_WAIT_INFO_0_EO NULL
#define Q88_PCG_8100_LABEL_EO NULL
#define Q88_PCG_8100_INFO_0_EO NULL
#define Q88_SAVE_TO_DISK_IMAGE_LABEL_EO NULL
#define Q88_SAVE_TO_DISK_IMAGE_INFO_0_EO NULL
#define Q88_RUMBLE_LABEL_EO NULL
#define Q88_RUMBLE_INFO_0_EO NULL
#define Q88_SCREEN_SIZE_LABEL_EO NULL
#define Q88_SCREEN_SIZE_INFO_0_EO NULL
#define Q88_SCREEN_SIZE_INFO_1_EO NULL
#define Q88_SCREEN_SIZE_INFO_2_EO NULL
#define OPTION_VAL_FULL_EO NULL
#define OPTION_VAL_HALF_EO NULL

struct retro_core_option_v2_category option_cats_eo[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_eo[] = {
   { 
      "q88_basic_mode", 
      Q88_BASIC_MODE_LABEL_EO,
      NULL, 
      Q88_BASIC_MODE_INFO_0_EO,
      NULL,
      NULL,
      {
         { "N88 V2",  OPTION_VAL_N88_V2_EO },
         { "N88 V1H", OPTION_VAL_N88_V1H_EO },
         { "N88 V1S", OPTION_VAL_N88_V1S_EO },
         { "N",       OPTION_VAL_N_EO },
         { NULL, NULL }
      },
      "N88 V2"
   },

   { 
      "q88_sub_cpu_mode",
      Q88_SUB_CPU_MODE_LABEL_EO,
      NULL,
      Q88_SUB_CPU_MODE_INFO_0_EO,
      NULL,
      NULL,
      {
         { "0", OPTION_VAL_0_EO},
         { "1", OPTION_VAL_1_EO},
         { "2", OPTION_VAL_2_EO},
         { NULL, NULL },
      },
      "0"
   },

   { 
      "q88_cpu_clock", 
      Q88_CPU_CLOCK_LABEL_EO,
      NULL, 
      Q88_CPU_CLOCK_INFO_0_EO,
      NULL,
      NULL,
      {
         { "4",  OPTION_VAL_4_EO },
         { "8",  OPTION_VAL_8_EO },
         { "16", OPTION_VAL_16_EO },
         { "32", OPTION_VAL_32_EO },
         { "64", OPTION_VAL_64_EO },
         { "1",  OPTION_VAL_1_O2_EO },
         { "2",  OPTION_VAL_2_O2_EO },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      Q88_SOUND_BOARD_LABEL_EO,
      NULL, 
      Q88_SOUND_BOARD_INFO_0_EO,
      NULL,
      NULL,
      {
         { "OPN",  OPTION_VAL_OPN_EO },
         { "OPNA", OPTION_VAL_OPNA_EO},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      Q88_USE_FDC_WAIT_LABEL_EO,
      NULL, 
      Q88_USE_FDC_WAIT_INFO_0_EO,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_pcg-8100", 
      Q88_PCG_8100_LABEL_EO,
      NULL, 
      Q88_PCG_8100_INFO_0_EO,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   {
      "q88_save_to_disk_image", 
      Q88_SAVE_TO_DISK_IMAGE_LABEL_EO,
      NULL, 
      Q88_SAVE_TO_DISK_IMAGE_INFO_0_EO,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   { 
      "q88_rumble", 
      Q88_RUMBLE_LABEL_EO,
      NULL, 
      Q88_RUMBLE_INFO_0_EO,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_screen_size", 
      Q88_SCREEN_SIZE_LABEL_EO,
      NULL, 
#if defined (PSP)
      Q88_SCREEN_SIZE_INFO_0_EO,
#elif defined (_3DS)
      Q88_SCREEN_SIZE_INFO_1_EO,
#else
      Q88_SCREEN_SIZE_INFO_2_EO,
#endif
      NULL,
      NULL,
      {
         { "full",  OPTION_VAL_FULL_EO },
         { "half",  OPTION_VAL_HALF_EO },
         { NULL, NULL }
      },
#if defined (PSP) || defined (_3DS)
      "half"
#else
      "full"
#endif
   },

   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_eo = {
   option_cats_eo,
   option_defs_eo
};

/* RETRO_LANGUAGE_ES */

#define Q88_BASIC_MODE_LABEL_ES "Modo BASIC"
#define Q88_BASIC_MODE_INFO_0_ES "Recomendación: N88-BASIC V2/V1H para el software para PC-8800, N-BASIC para el software para PC-8000.\n\- Si el software para PC-8800 se ejecuta demasiado rápido en un modo V2, prueba con un modo V1.\n\- El modo N-BASIC necesita los archivos de la BIOS. Puedes saber cuáles son en la información del núcleo."
#define OPTION_VAL_N88_V2_ES NULL
#define OPTION_VAL_N88_V1H_ES NULL
#define OPTION_VAL_N88_V1S_ES NULL
#define OPTION_VAL_N_ES NULL
#define Q88_SUB_CPU_MODE_LABEL_ES "Modo del subprocesador"
#define Q88_SUB_CPU_MODE_INFO_0_ES "Recomendación: ejecutar la sub-CPU solo al acceder al disquete."
#define OPTION_VAL_0_ES "Ejecutar la sub-CPU solo al acceder al disquete"
#define OPTION_VAL_1_ES "Ejecutar ambas CPU al acceder al disquete"
#define OPTION_VAL_2_ES "Ejecutar siempre ambas CPU"
#define Q88_CPU_CLOCK_LABEL_ES "Reloj de la CPU"
#define Q88_CPU_CLOCK_INFO_0_ES "Recomendación: 4 u 8 MHz. Algunas aplicaciones podrían ejecutarse demasiado rápido con una CPU a 8 MHz."
#define OPTION_VAL_4_ES NULL
#define OPTION_VAL_8_ES NULL
#define OPTION_VAL_16_ES "16 MHz (acelerar CPU)"
#define OPTION_VAL_32_ES "32 MHz (acelerar CPU)"
#define OPTION_VAL_64_ES "64 MHz (acelerar CPU)"
#define OPTION_VAL_1_O2_ES "1 MHz (ralentizar CPU)"
#define OPTION_VAL_2_O2_ES "2 MHz (underclockear)"
#define Q88_SOUND_BOARD_LABEL_ES "Tarjeta de sonido"
#define Q88_SOUND_BOARD_INFO_0_ES "Recomendación: OPNA. Algunas aplicaciones podrían tener un sonido alterado al utilizar un hardware OPN."
#define OPTION_VAL_OPN_ES NULL
#define OPTION_VAL_OPNA_ES NULL
#define Q88_USE_FDC_WAIT_LABEL_ES "Esperar al FDC"
#define Q88_USE_FDC_WAIT_INFO_0_ES "Recomendación: Sí. Mejora la sincronía del I/O con el controlador de la disquetera."
#define Q88_PCG_8100_LABEL_ES "Utilizar PCG-8100"
#define Q88_PCG_8100_INFO_0_ES "Recomendación: No. Algunas aplicaciones para PC-8000 sí podrían necesitarlo."
#define Q88_SAVE_TO_DISK_IMAGE_LABEL_ES "Guardar a una imagen de disquete"
#define Q88_SAVE_TO_DISK_IMAGE_INFO_0_ES "Recomendación: No. Cambia el método preferido por el núcleo para guardar datos.\n\- No: Los datos que se escriban en disquetes serán almacenados en un archivo aparte, en el directorio de guardados del front-end.\n\- Sí: Los datos se escribirán directamente en el(los) archivo(s) de disquete cargado(s). No se escribirán contenidos que estén en archivos .zip."
#define Q88_RUMBLE_LABEL_ES "Vibrar el mando al acceder al disquete"
#define Q88_RUMBLE_INFO_0_ES "Recomendación: No disponible. Imita los sonidos de lectura del controlador de la disquetera con la vibración del mando."
#define Q88_SCREEN_SIZE_LABEL_ES "Tamaño de la pantalla"
#define Q88_SCREEN_SIZE_INFO_0_ES "Recomendación: Baja resolución. Permite que el núcleo pueda hacer la imagen más pequeña (recomendado para la pantalla de PSP)."
#define Q88_SCREEN_SIZE_INFO_1_ES "Recomendación: Baja resolución. Permite que el núcleo pueda hacer la imagen más pequeña (recomendado para la pantalla de Nintendo 3DS)."
#define Q88_SCREEN_SIZE_INFO_2_ES "Recomendación: Resolución completa. Permite que el núcleo pueda hacer la imagen más pequeña (solo recomendado para pantallas con una altura inferior a 400 px)."
#define OPTION_VAL_FULL_ES "Resolución completa (640x400)"
#define OPTION_VAL_HALF_ES "Baja resolución (320x200)"

struct retro_core_option_v2_category option_cats_es[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_es[] = {
   { 
      "q88_basic_mode", 
      Q88_BASIC_MODE_LABEL_ES,
      NULL, 
      Q88_BASIC_MODE_INFO_0_ES,
      NULL,
      NULL,
      {
         { "N88 V2",  OPTION_VAL_N88_V2_ES },
         { "N88 V1H", OPTION_VAL_N88_V1H_ES },
         { "N88 V1S", OPTION_VAL_N88_V1S_ES },
         { "N",       OPTION_VAL_N_ES },
         { NULL, NULL }
      },
      "N88 V2"
   },

   { 
      "q88_sub_cpu_mode",
      Q88_SUB_CPU_MODE_LABEL_ES,
      NULL,
      Q88_SUB_CPU_MODE_INFO_0_ES,
      NULL,
      NULL,
      {
         { "0", OPTION_VAL_0_ES},
         { "1", OPTION_VAL_1_ES},
         { "2", OPTION_VAL_2_ES},
         { NULL, NULL },
      },
      "0"
   },

   { 
      "q88_cpu_clock", 
      Q88_CPU_CLOCK_LABEL_ES,
      NULL, 
      Q88_CPU_CLOCK_INFO_0_ES,
      NULL,
      NULL,
      {
         { "4",  OPTION_VAL_4_ES },
         { "8",  OPTION_VAL_8_ES },
         { "16", OPTION_VAL_16_ES },
         { "32", OPTION_VAL_32_ES },
         { "64", OPTION_VAL_64_ES },
         { "1",  OPTION_VAL_1_O2_ES },
         { "2",  OPTION_VAL_2_O2_ES },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      Q88_SOUND_BOARD_LABEL_ES,
      NULL, 
      Q88_SOUND_BOARD_INFO_0_ES,
      NULL,
      NULL,
      {
         { "OPN",  OPTION_VAL_OPN_ES },
         { "OPNA", OPTION_VAL_OPNA_ES},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      Q88_USE_FDC_WAIT_LABEL_ES,
      NULL, 
      Q88_USE_FDC_WAIT_INFO_0_ES,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_pcg-8100", 
      Q88_PCG_8100_LABEL_ES,
      NULL, 
      Q88_PCG_8100_INFO_0_ES,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   {
      "q88_save_to_disk_image", 
      Q88_SAVE_TO_DISK_IMAGE_LABEL_ES,
      NULL, 
      Q88_SAVE_TO_DISK_IMAGE_INFO_0_ES,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   { 
      "q88_rumble", 
      Q88_RUMBLE_LABEL_ES,
      NULL, 
      Q88_RUMBLE_INFO_0_ES,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_screen_size", 
      Q88_SCREEN_SIZE_LABEL_ES,
      NULL, 
#if defined (PSP)
      Q88_SCREEN_SIZE_INFO_0_ES,
#elif defined (_3DS)
      Q88_SCREEN_SIZE_INFO_1_ES,
#else
      Q88_SCREEN_SIZE_INFO_2_ES,
#endif
      NULL,
      NULL,
      {
         { "full",  OPTION_VAL_FULL_ES },
         { "half",  OPTION_VAL_HALF_ES },
         { NULL, NULL }
      },
#if defined (PSP) || defined (_3DS)
      "half"
#else
      "full"
#endif
   },

   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_es = {
   option_cats_es,
   option_defs_es
};

/* RETRO_LANGUAGE_FA */

#define Q88_BASIC_MODE_LABEL_FA NULL
#define Q88_BASIC_MODE_INFO_0_FA NULL
#define OPTION_VAL_N88_V2_FA NULL
#define OPTION_VAL_N88_V1H_FA NULL
#define OPTION_VAL_N88_V1S_FA NULL
#define OPTION_VAL_N_FA NULL
#define Q88_SUB_CPU_MODE_LABEL_FA NULL
#define Q88_SUB_CPU_MODE_INFO_0_FA NULL
#define OPTION_VAL_0_FA NULL
#define OPTION_VAL_1_FA NULL
#define OPTION_VAL_2_FA NULL
#define Q88_CPU_CLOCK_LABEL_FA NULL
#define Q88_CPU_CLOCK_INFO_0_FA NULL
#define OPTION_VAL_4_FA NULL
#define OPTION_VAL_8_FA NULL
#define OPTION_VAL_16_FA NULL
#define OPTION_VAL_32_FA NULL
#define OPTION_VAL_64_FA NULL
#define OPTION_VAL_1_O2_FA NULL
#define OPTION_VAL_2_O2_FA NULL
#define Q88_SOUND_BOARD_LABEL_FA NULL
#define Q88_SOUND_BOARD_INFO_0_FA NULL
#define OPTION_VAL_OPN_FA NULL
#define OPTION_VAL_OPNA_FA NULL
#define Q88_USE_FDC_WAIT_LABEL_FA NULL
#define Q88_USE_FDC_WAIT_INFO_0_FA NULL
#define Q88_PCG_8100_LABEL_FA NULL
#define Q88_PCG_8100_INFO_0_FA NULL
#define Q88_SAVE_TO_DISK_IMAGE_LABEL_FA NULL
#define Q88_SAVE_TO_DISK_IMAGE_INFO_0_FA NULL
#define Q88_RUMBLE_LABEL_FA NULL
#define Q88_RUMBLE_INFO_0_FA NULL
#define Q88_SCREEN_SIZE_LABEL_FA NULL
#define Q88_SCREEN_SIZE_INFO_0_FA NULL
#define Q88_SCREEN_SIZE_INFO_1_FA NULL
#define Q88_SCREEN_SIZE_INFO_2_FA NULL
#define OPTION_VAL_FULL_FA NULL
#define OPTION_VAL_HALF_FA NULL

struct retro_core_option_v2_category option_cats_fa[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_fa[] = {
   { 
      "q88_basic_mode", 
      Q88_BASIC_MODE_LABEL_FA,
      NULL, 
      Q88_BASIC_MODE_INFO_0_FA,
      NULL,
      NULL,
      {
         { "N88 V2",  OPTION_VAL_N88_V2_FA },
         { "N88 V1H", OPTION_VAL_N88_V1H_FA },
         { "N88 V1S", OPTION_VAL_N88_V1S_FA },
         { "N",       OPTION_VAL_N_FA },
         { NULL, NULL }
      },
      "N88 V2"
   },

   { 
      "q88_sub_cpu_mode",
      Q88_SUB_CPU_MODE_LABEL_FA,
      NULL,
      Q88_SUB_CPU_MODE_INFO_0_FA,
      NULL,
      NULL,
      {
         { "0", OPTION_VAL_0_FA},
         { "1", OPTION_VAL_1_FA},
         { "2", OPTION_VAL_2_FA},
         { NULL, NULL },
      },
      "0"
   },

   { 
      "q88_cpu_clock", 
      Q88_CPU_CLOCK_LABEL_FA,
      NULL, 
      Q88_CPU_CLOCK_INFO_0_FA,
      NULL,
      NULL,
      {
         { "4",  OPTION_VAL_4_FA },
         { "8",  OPTION_VAL_8_FA },
         { "16", OPTION_VAL_16_FA },
         { "32", OPTION_VAL_32_FA },
         { "64", OPTION_VAL_64_FA },
         { "1",  OPTION_VAL_1_O2_FA },
         { "2",  OPTION_VAL_2_O2_FA },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      Q88_SOUND_BOARD_LABEL_FA,
      NULL, 
      Q88_SOUND_BOARD_INFO_0_FA,
      NULL,
      NULL,
      {
         { "OPN",  OPTION_VAL_OPN_FA },
         { "OPNA", OPTION_VAL_OPNA_FA},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      Q88_USE_FDC_WAIT_LABEL_FA,
      NULL, 
      Q88_USE_FDC_WAIT_INFO_0_FA,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_pcg-8100", 
      Q88_PCG_8100_LABEL_FA,
      NULL, 
      Q88_PCG_8100_INFO_0_FA,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   {
      "q88_save_to_disk_image", 
      Q88_SAVE_TO_DISK_IMAGE_LABEL_FA,
      NULL, 
      Q88_SAVE_TO_DISK_IMAGE_INFO_0_FA,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   { 
      "q88_rumble", 
      Q88_RUMBLE_LABEL_FA,
      NULL, 
      Q88_RUMBLE_INFO_0_FA,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_screen_size", 
      Q88_SCREEN_SIZE_LABEL_FA,
      NULL, 
#if defined (PSP)
      Q88_SCREEN_SIZE_INFO_0_FA,
#elif defined (_3DS)
      Q88_SCREEN_SIZE_INFO_1_FA,
#else
      Q88_SCREEN_SIZE_INFO_2_FA,
#endif
      NULL,
      NULL,
      {
         { "full",  OPTION_VAL_FULL_FA },
         { "half",  OPTION_VAL_HALF_FA },
         { NULL, NULL }
      },
#if defined (PSP) || defined (_3DS)
      "half"
#else
      "full"
#endif
   },

   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_fa = {
   option_cats_fa,
   option_defs_fa
};

/* RETRO_LANGUAGE_FI */

#define Q88_BASIC_MODE_LABEL_FI NULL
#define Q88_BASIC_MODE_INFO_0_FI NULL
#define OPTION_VAL_N88_V2_FI NULL
#define OPTION_VAL_N88_V1H_FI NULL
#define OPTION_VAL_N88_V1S_FI NULL
#define OPTION_VAL_N_FI NULL
#define Q88_SUB_CPU_MODE_LABEL_FI NULL
#define Q88_SUB_CPU_MODE_INFO_0_FI NULL
#define OPTION_VAL_0_FI NULL
#define OPTION_VAL_1_FI NULL
#define OPTION_VAL_2_FI NULL
#define Q88_CPU_CLOCK_LABEL_FI NULL
#define Q88_CPU_CLOCK_INFO_0_FI "Suositus: 4 MHz tai 8 MHz. Jotkin ohjelmistot saattavat toimia liian nopeasti, jos asetus on 8 MHz."
#define OPTION_VAL_4_FI NULL
#define OPTION_VAL_8_FI NULL
#define OPTION_VAL_16_FI NULL
#define OPTION_VAL_32_FI NULL
#define OPTION_VAL_64_FI NULL
#define OPTION_VAL_1_O2_FI NULL
#define OPTION_VAL_2_O2_FI NULL
#define Q88_SOUND_BOARD_LABEL_FI NULL
#define Q88_SOUND_BOARD_INFO_0_FI NULL
#define OPTION_VAL_OPN_FI NULL
#define OPTION_VAL_OPNA_FI NULL
#define Q88_USE_FDC_WAIT_LABEL_FI NULL
#define Q88_USE_FDC_WAIT_INFO_0_FI NULL
#define Q88_PCG_8100_LABEL_FI NULL
#define Q88_PCG_8100_INFO_0_FI NULL
#define Q88_SAVE_TO_DISK_IMAGE_LABEL_FI NULL
#define Q88_SAVE_TO_DISK_IMAGE_INFO_0_FI NULL
#define Q88_RUMBLE_LABEL_FI NULL
#define Q88_RUMBLE_INFO_0_FI NULL
#define Q88_SCREEN_SIZE_LABEL_FI "Näytön koko"
#define Q88_SCREEN_SIZE_INFO_0_FI NULL
#define Q88_SCREEN_SIZE_INFO_1_FI NULL
#define Q88_SCREEN_SIZE_INFO_2_FI NULL
#define OPTION_VAL_FULL_FI NULL
#define OPTION_VAL_HALF_FI NULL

struct retro_core_option_v2_category option_cats_fi[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_fi[] = {
   { 
      "q88_basic_mode", 
      Q88_BASIC_MODE_LABEL_FI,
      NULL, 
      Q88_BASIC_MODE_INFO_0_FI,
      NULL,
      NULL,
      {
         { "N88 V2",  OPTION_VAL_N88_V2_FI },
         { "N88 V1H", OPTION_VAL_N88_V1H_FI },
         { "N88 V1S", OPTION_VAL_N88_V1S_FI },
         { "N",       OPTION_VAL_N_FI },
         { NULL, NULL }
      },
      "N88 V2"
   },

   { 
      "q88_sub_cpu_mode",
      Q88_SUB_CPU_MODE_LABEL_FI,
      NULL,
      Q88_SUB_CPU_MODE_INFO_0_FI,
      NULL,
      NULL,
      {
         { "0", OPTION_VAL_0_FI},
         { "1", OPTION_VAL_1_FI},
         { "2", OPTION_VAL_2_FI},
         { NULL, NULL },
      },
      "0"
   },

   { 
      "q88_cpu_clock", 
      Q88_CPU_CLOCK_LABEL_FI,
      NULL, 
      Q88_CPU_CLOCK_INFO_0_FI,
      NULL,
      NULL,
      {
         { "4",  OPTION_VAL_4_FI },
         { "8",  OPTION_VAL_8_FI },
         { "16", OPTION_VAL_16_FI },
         { "32", OPTION_VAL_32_FI },
         { "64", OPTION_VAL_64_FI },
         { "1",  OPTION_VAL_1_O2_FI },
         { "2",  OPTION_VAL_2_O2_FI },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      Q88_SOUND_BOARD_LABEL_FI,
      NULL, 
      Q88_SOUND_BOARD_INFO_0_FI,
      NULL,
      NULL,
      {
         { "OPN",  OPTION_VAL_OPN_FI },
         { "OPNA", OPTION_VAL_OPNA_FI},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      Q88_USE_FDC_WAIT_LABEL_FI,
      NULL, 
      Q88_USE_FDC_WAIT_INFO_0_FI,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_pcg-8100", 
      Q88_PCG_8100_LABEL_FI,
      NULL, 
      Q88_PCG_8100_INFO_0_FI,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   {
      "q88_save_to_disk_image", 
      Q88_SAVE_TO_DISK_IMAGE_LABEL_FI,
      NULL, 
      Q88_SAVE_TO_DISK_IMAGE_INFO_0_FI,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   { 
      "q88_rumble", 
      Q88_RUMBLE_LABEL_FI,
      NULL, 
      Q88_RUMBLE_INFO_0_FI,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_screen_size", 
      Q88_SCREEN_SIZE_LABEL_FI,
      NULL, 
#if defined (PSP)
      Q88_SCREEN_SIZE_INFO_0_FI,
#elif defined (_3DS)
      Q88_SCREEN_SIZE_INFO_1_FI,
#else
      Q88_SCREEN_SIZE_INFO_2_FI,
#endif
      NULL,
      NULL,
      {
         { "full",  OPTION_VAL_FULL_FI },
         { "half",  OPTION_VAL_HALF_FI },
         { NULL, NULL }
      },
#if defined (PSP) || defined (_3DS)
      "half"
#else
      "full"
#endif
   },

   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_fi = {
   option_cats_fi,
   option_defs_fi
};

/* RETRO_LANGUAGE_FR */

#define Q88_BASIC_MODE_LABEL_FR "Mode BASIC"
#define Q88_BASIC_MODE_INFO_0_FR "Recommandé : N88-BASIC V2/V1H pour les logiciels PC-8800, N-BASIC pour les logiciels PC-8000.\n\- Si un logiciel PC-8800 tourne trop rapidement en mode V2, utilisez le mode V1.\n\- Les fichiers de BIOS sont requis pour le mode N-BASIC. Voir les informations du cœur."
#define OPTION_VAL_N88_V2_FR NULL
#define OPTION_VAL_N88_V1H_FR NULL
#define OPTION_VAL_N88_V1S_FR NULL
#define OPTION_VAL_N_FR NULL
#define Q88_SUB_CPU_MODE_LABEL_FR "Mode du sous-processeur"
#define Q88_SUB_CPU_MODE_INFO_0_FR "Recommandé : faire tourner le sous-processeur uniquement lors de l'accès au disque."
#define OPTION_VAL_0_FR "Faire tourner le sous-processeur uniquement lors de l'accès au disque"
#define OPTION_VAL_1_FR "Faire tourner les deux processeurs lors de l'accès au disque"
#define OPTION_VAL_2_FR "Toujours utiliser les deux processeurs"
#define Q88_CPU_CLOCK_LABEL_FR "Horloge processeur"
#define Q88_CPU_CLOCK_INFO_0_FR "Recommandé : 4MHz ou 8MHz. Certains logiciels peuvent tourner trop rapidement avec un processeur à 8MHz."
#define OPTION_VAL_4_FR "4 MHz (NEC μPD780)"
#define OPTION_VAL_8_FR "8 MHz (NEC μPD70008)"
#define OPTION_VAL_16_FR NULL
#define OPTION_VAL_32_FR NULL
#define OPTION_VAL_64_FR NULL
#define OPTION_VAL_1_O2_FR NULL
#define OPTION_VAL_2_O2_FR NULL
#define Q88_SOUND_BOARD_LABEL_FR "Carte son"
#define Q88_SOUND_BOARD_INFO_0_FR "Recommandé : OPNA. Certains logiciels sonneront différemment lors de l'utilisation du matériel OPN."
#define OPTION_VAL_OPN_FR NULL
#define OPTION_VAL_OPNA_FR NULL
#define Q88_USE_FDC_WAIT_LABEL_FR "Attente du FDC"
#define Q88_USE_FDC_WAIT_INFO_0_FR "Recommandé : activé. Permet un délai d'entrées/sorties plus précis pour le contrôleur de disquette."
#define Q88_PCG_8100_LABEL_FR "Utiliser PCG-8100"
#define Q88_PCG_8100_INFO_0_FR "Recommandé : désactivé. Peut être requis pour certains logiciels PC-8000."
#define Q88_SAVE_TO_DISK_IMAGE_LABEL_FR "Sauvegarder vers une image disque"
#define Q88_SAVE_TO_DISK_IMAGE_INFO_0_FR "Recommandé : désactivé. Modifie le comportement de sauvegarde préféré du cœur.\n\- Désactivé : Les données écrites sur des disquettes seront stockées dans un fichier séparé dans le dossier de sauvegarde de l'interface.\n\- Activé : Les données seront écrites directement vers le(s) fichier(s) disque(s) chargé(s). Ne fonctionnera pas avec du contenu compressé en zip."
#define Q88_RUMBLE_LABEL_FR "Vibration lors de l'accès au disque"
#define Q88_RUMBLE_INFO_0_FR "Recommandé : non applicable. Imite les sons de lecture du contrôleur de disquette en utilisant la vibration de la manette."
#define Q88_SCREEN_SIZE_LABEL_FR "Taille de l'écran"
#define Q88_SCREEN_SIZE_INFO_0_FR "Recommandé : demi résolution. Permet au cœur de réduire la taille de l'image. Recommandé pour l'écran de la PSP."
#define Q88_SCREEN_SIZE_INFO_1_FR "Recommandé : demi résolution. Permet au cœur de réduire la taille de l'image. Recommandé pour l'écran de la Nintendo 3DS."
#define Q88_SCREEN_SIZE_INFO_2_FR "Recommandé : pleine résolution. Permet au cœur de réduire la taille de l'image. Uniquement recommandé pour les hauteurs d'affichage inférieures à 400."
#define OPTION_VAL_FULL_FR "Pleine résolution (640x400)"
#define OPTION_VAL_HALF_FR "Demi résolution (320x200)"

struct retro_core_option_v2_category option_cats_fr[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_fr[] = {
   { 
      "q88_basic_mode", 
      Q88_BASIC_MODE_LABEL_FR,
      NULL, 
      Q88_BASIC_MODE_INFO_0_FR,
      NULL,
      NULL,
      {
         { "N88 V2",  OPTION_VAL_N88_V2_FR },
         { "N88 V1H", OPTION_VAL_N88_V1H_FR },
         { "N88 V1S", OPTION_VAL_N88_V1S_FR },
         { "N",       OPTION_VAL_N_FR },
         { NULL, NULL }
      },
      "N88 V2"
   },

   { 
      "q88_sub_cpu_mode",
      Q88_SUB_CPU_MODE_LABEL_FR,
      NULL,
      Q88_SUB_CPU_MODE_INFO_0_FR,
      NULL,
      NULL,
      {
         { "0", OPTION_VAL_0_FR},
         { "1", OPTION_VAL_1_FR},
         { "2", OPTION_VAL_2_FR},
         { NULL, NULL },
      },
      "0"
   },

   { 
      "q88_cpu_clock", 
      Q88_CPU_CLOCK_LABEL_FR,
      NULL, 
      Q88_CPU_CLOCK_INFO_0_FR,
      NULL,
      NULL,
      {
         { "4",  OPTION_VAL_4_FR },
         { "8",  OPTION_VAL_8_FR },
         { "16", OPTION_VAL_16_FR },
         { "32", OPTION_VAL_32_FR },
         { "64", OPTION_VAL_64_FR },
         { "1",  OPTION_VAL_1_O2_FR },
         { "2",  OPTION_VAL_2_O2_FR },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      Q88_SOUND_BOARD_LABEL_FR,
      NULL, 
      Q88_SOUND_BOARD_INFO_0_FR,
      NULL,
      NULL,
      {
         { "OPN",  OPTION_VAL_OPN_FR },
         { "OPNA", OPTION_VAL_OPNA_FR},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      Q88_USE_FDC_WAIT_LABEL_FR,
      NULL, 
      Q88_USE_FDC_WAIT_INFO_0_FR,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_pcg-8100", 
      Q88_PCG_8100_LABEL_FR,
      NULL, 
      Q88_PCG_8100_INFO_0_FR,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   {
      "q88_save_to_disk_image", 
      Q88_SAVE_TO_DISK_IMAGE_LABEL_FR,
      NULL, 
      Q88_SAVE_TO_DISK_IMAGE_INFO_0_FR,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   { 
      "q88_rumble", 
      Q88_RUMBLE_LABEL_FR,
      NULL, 
      Q88_RUMBLE_INFO_0_FR,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_screen_size", 
      Q88_SCREEN_SIZE_LABEL_FR,
      NULL, 
#if defined (PSP)
      Q88_SCREEN_SIZE_INFO_0_FR,
#elif defined (_3DS)
      Q88_SCREEN_SIZE_INFO_1_FR,
#else
      Q88_SCREEN_SIZE_INFO_2_FR,
#endif
      NULL,
      NULL,
      {
         { "full",  OPTION_VAL_FULL_FR },
         { "half",  OPTION_VAL_HALF_FR },
         { NULL, NULL }
      },
#if defined (PSP) || defined (_3DS)
      "half"
#else
      "full"
#endif
   },

   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_fr = {
   option_cats_fr,
   option_defs_fr
};

/* RETRO_LANGUAGE_GL */

#define Q88_BASIC_MODE_LABEL_GL NULL
#define Q88_BASIC_MODE_INFO_0_GL NULL
#define OPTION_VAL_N88_V2_GL NULL
#define OPTION_VAL_N88_V1H_GL NULL
#define OPTION_VAL_N88_V1S_GL NULL
#define OPTION_VAL_N_GL NULL
#define Q88_SUB_CPU_MODE_LABEL_GL NULL
#define Q88_SUB_CPU_MODE_INFO_0_GL NULL
#define OPTION_VAL_0_GL NULL
#define OPTION_VAL_1_GL NULL
#define OPTION_VAL_2_GL NULL
#define Q88_CPU_CLOCK_LABEL_GL NULL
#define Q88_CPU_CLOCK_INFO_0_GL NULL
#define OPTION_VAL_4_GL NULL
#define OPTION_VAL_8_GL NULL
#define OPTION_VAL_16_GL NULL
#define OPTION_VAL_32_GL NULL
#define OPTION_VAL_64_GL NULL
#define OPTION_VAL_1_O2_GL NULL
#define OPTION_VAL_2_O2_GL NULL
#define Q88_SOUND_BOARD_LABEL_GL NULL
#define Q88_SOUND_BOARD_INFO_0_GL NULL
#define OPTION_VAL_OPN_GL NULL
#define OPTION_VAL_OPNA_GL NULL
#define Q88_USE_FDC_WAIT_LABEL_GL NULL
#define Q88_USE_FDC_WAIT_INFO_0_GL NULL
#define Q88_PCG_8100_LABEL_GL NULL
#define Q88_PCG_8100_INFO_0_GL NULL
#define Q88_SAVE_TO_DISK_IMAGE_LABEL_GL NULL
#define Q88_SAVE_TO_DISK_IMAGE_INFO_0_GL NULL
#define Q88_RUMBLE_LABEL_GL NULL
#define Q88_RUMBLE_INFO_0_GL NULL
#define Q88_SCREEN_SIZE_LABEL_GL NULL
#define Q88_SCREEN_SIZE_INFO_0_GL NULL
#define Q88_SCREEN_SIZE_INFO_1_GL NULL
#define Q88_SCREEN_SIZE_INFO_2_GL NULL
#define OPTION_VAL_FULL_GL NULL
#define OPTION_VAL_HALF_GL NULL

struct retro_core_option_v2_category option_cats_gl[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_gl[] = {
   { 
      "q88_basic_mode", 
      Q88_BASIC_MODE_LABEL_GL,
      NULL, 
      Q88_BASIC_MODE_INFO_0_GL,
      NULL,
      NULL,
      {
         { "N88 V2",  OPTION_VAL_N88_V2_GL },
         { "N88 V1H", OPTION_VAL_N88_V1H_GL },
         { "N88 V1S", OPTION_VAL_N88_V1S_GL },
         { "N",       OPTION_VAL_N_GL },
         { NULL, NULL }
      },
      "N88 V2"
   },

   { 
      "q88_sub_cpu_mode",
      Q88_SUB_CPU_MODE_LABEL_GL,
      NULL,
      Q88_SUB_CPU_MODE_INFO_0_GL,
      NULL,
      NULL,
      {
         { "0", OPTION_VAL_0_GL},
         { "1", OPTION_VAL_1_GL},
         { "2", OPTION_VAL_2_GL},
         { NULL, NULL },
      },
      "0"
   },

   { 
      "q88_cpu_clock", 
      Q88_CPU_CLOCK_LABEL_GL,
      NULL, 
      Q88_CPU_CLOCK_INFO_0_GL,
      NULL,
      NULL,
      {
         { "4",  OPTION_VAL_4_GL },
         { "8",  OPTION_VAL_8_GL },
         { "16", OPTION_VAL_16_GL },
         { "32", OPTION_VAL_32_GL },
         { "64", OPTION_VAL_64_GL },
         { "1",  OPTION_VAL_1_O2_GL },
         { "2",  OPTION_VAL_2_O2_GL },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      Q88_SOUND_BOARD_LABEL_GL,
      NULL, 
      Q88_SOUND_BOARD_INFO_0_GL,
      NULL,
      NULL,
      {
         { "OPN",  OPTION_VAL_OPN_GL },
         { "OPNA", OPTION_VAL_OPNA_GL},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      Q88_USE_FDC_WAIT_LABEL_GL,
      NULL, 
      Q88_USE_FDC_WAIT_INFO_0_GL,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_pcg-8100", 
      Q88_PCG_8100_LABEL_GL,
      NULL, 
      Q88_PCG_8100_INFO_0_GL,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   {
      "q88_save_to_disk_image", 
      Q88_SAVE_TO_DISK_IMAGE_LABEL_GL,
      NULL, 
      Q88_SAVE_TO_DISK_IMAGE_INFO_0_GL,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   { 
      "q88_rumble", 
      Q88_RUMBLE_LABEL_GL,
      NULL, 
      Q88_RUMBLE_INFO_0_GL,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_screen_size", 
      Q88_SCREEN_SIZE_LABEL_GL,
      NULL, 
#if defined (PSP)
      Q88_SCREEN_SIZE_INFO_0_GL,
#elif defined (_3DS)
      Q88_SCREEN_SIZE_INFO_1_GL,
#else
      Q88_SCREEN_SIZE_INFO_2_GL,
#endif
      NULL,
      NULL,
      {
         { "full",  OPTION_VAL_FULL_GL },
         { "half",  OPTION_VAL_HALF_GL },
         { NULL, NULL }
      },
#if defined (PSP) || defined (_3DS)
      "half"
#else
      "full"
#endif
   },

   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_gl = {
   option_cats_gl,
   option_defs_gl
};

/* RETRO_LANGUAGE_HE */

#define Q88_BASIC_MODE_LABEL_HE NULL
#define Q88_BASIC_MODE_INFO_0_HE NULL
#define OPTION_VAL_N88_V2_HE NULL
#define OPTION_VAL_N88_V1H_HE NULL
#define OPTION_VAL_N88_V1S_HE NULL
#define OPTION_VAL_N_HE NULL
#define Q88_SUB_CPU_MODE_LABEL_HE NULL
#define Q88_SUB_CPU_MODE_INFO_0_HE NULL
#define OPTION_VAL_0_HE NULL
#define OPTION_VAL_1_HE NULL
#define OPTION_VAL_2_HE NULL
#define Q88_CPU_CLOCK_LABEL_HE NULL
#define Q88_CPU_CLOCK_INFO_0_HE NULL
#define OPTION_VAL_4_HE NULL
#define OPTION_VAL_8_HE NULL
#define OPTION_VAL_16_HE NULL
#define OPTION_VAL_32_HE NULL
#define OPTION_VAL_64_HE NULL
#define OPTION_VAL_1_O2_HE NULL
#define OPTION_VAL_2_O2_HE NULL
#define Q88_SOUND_BOARD_LABEL_HE NULL
#define Q88_SOUND_BOARD_INFO_0_HE NULL
#define OPTION_VAL_OPN_HE NULL
#define OPTION_VAL_OPNA_HE NULL
#define Q88_USE_FDC_WAIT_LABEL_HE NULL
#define Q88_USE_FDC_WAIT_INFO_0_HE NULL
#define Q88_PCG_8100_LABEL_HE NULL
#define Q88_PCG_8100_INFO_0_HE NULL
#define Q88_SAVE_TO_DISK_IMAGE_LABEL_HE NULL
#define Q88_SAVE_TO_DISK_IMAGE_INFO_0_HE NULL
#define Q88_RUMBLE_LABEL_HE NULL
#define Q88_RUMBLE_INFO_0_HE NULL
#define Q88_SCREEN_SIZE_LABEL_HE NULL
#define Q88_SCREEN_SIZE_INFO_0_HE NULL
#define Q88_SCREEN_SIZE_INFO_1_HE NULL
#define Q88_SCREEN_SIZE_INFO_2_HE NULL
#define OPTION_VAL_FULL_HE NULL
#define OPTION_VAL_HALF_HE NULL

struct retro_core_option_v2_category option_cats_he[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_he[] = {
   { 
      "q88_basic_mode", 
      Q88_BASIC_MODE_LABEL_HE,
      NULL, 
      Q88_BASIC_MODE_INFO_0_HE,
      NULL,
      NULL,
      {
         { "N88 V2",  OPTION_VAL_N88_V2_HE },
         { "N88 V1H", OPTION_VAL_N88_V1H_HE },
         { "N88 V1S", OPTION_VAL_N88_V1S_HE },
         { "N",       OPTION_VAL_N_HE },
         { NULL, NULL }
      },
      "N88 V2"
   },

   { 
      "q88_sub_cpu_mode",
      Q88_SUB_CPU_MODE_LABEL_HE,
      NULL,
      Q88_SUB_CPU_MODE_INFO_0_HE,
      NULL,
      NULL,
      {
         { "0", OPTION_VAL_0_HE},
         { "1", OPTION_VAL_1_HE},
         { "2", OPTION_VAL_2_HE},
         { NULL, NULL },
      },
      "0"
   },

   { 
      "q88_cpu_clock", 
      Q88_CPU_CLOCK_LABEL_HE,
      NULL, 
      Q88_CPU_CLOCK_INFO_0_HE,
      NULL,
      NULL,
      {
         { "4",  OPTION_VAL_4_HE },
         { "8",  OPTION_VAL_8_HE },
         { "16", OPTION_VAL_16_HE },
         { "32", OPTION_VAL_32_HE },
         { "64", OPTION_VAL_64_HE },
         { "1",  OPTION_VAL_1_O2_HE },
         { "2",  OPTION_VAL_2_O2_HE },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      Q88_SOUND_BOARD_LABEL_HE,
      NULL, 
      Q88_SOUND_BOARD_INFO_0_HE,
      NULL,
      NULL,
      {
         { "OPN",  OPTION_VAL_OPN_HE },
         { "OPNA", OPTION_VAL_OPNA_HE},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      Q88_USE_FDC_WAIT_LABEL_HE,
      NULL, 
      Q88_USE_FDC_WAIT_INFO_0_HE,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_pcg-8100", 
      Q88_PCG_8100_LABEL_HE,
      NULL, 
      Q88_PCG_8100_INFO_0_HE,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   {
      "q88_save_to_disk_image", 
      Q88_SAVE_TO_DISK_IMAGE_LABEL_HE,
      NULL, 
      Q88_SAVE_TO_DISK_IMAGE_INFO_0_HE,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   { 
      "q88_rumble", 
      Q88_RUMBLE_LABEL_HE,
      NULL, 
      Q88_RUMBLE_INFO_0_HE,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_screen_size", 
      Q88_SCREEN_SIZE_LABEL_HE,
      NULL, 
#if defined (PSP)
      Q88_SCREEN_SIZE_INFO_0_HE,
#elif defined (_3DS)
      Q88_SCREEN_SIZE_INFO_1_HE,
#else
      Q88_SCREEN_SIZE_INFO_2_HE,
#endif
      NULL,
      NULL,
      {
         { "full",  OPTION_VAL_FULL_HE },
         { "half",  OPTION_VAL_HALF_HE },
         { NULL, NULL }
      },
#if defined (PSP) || defined (_3DS)
      "half"
#else
      "full"
#endif
   },

   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_he = {
   option_cats_he,
   option_defs_he
};

/* RETRO_LANGUAGE_HU */

#define Q88_BASIC_MODE_LABEL_HU NULL
#define Q88_BASIC_MODE_INFO_0_HU NULL
#define OPTION_VAL_N88_V2_HU NULL
#define OPTION_VAL_N88_V1H_HU NULL
#define OPTION_VAL_N88_V1S_HU NULL
#define OPTION_VAL_N_HU NULL
#define Q88_SUB_CPU_MODE_LABEL_HU NULL
#define Q88_SUB_CPU_MODE_INFO_0_HU NULL
#define OPTION_VAL_0_HU NULL
#define OPTION_VAL_1_HU NULL
#define OPTION_VAL_2_HU NULL
#define Q88_CPU_CLOCK_LABEL_HU NULL
#define Q88_CPU_CLOCK_INFO_0_HU NULL
#define OPTION_VAL_4_HU NULL
#define OPTION_VAL_8_HU NULL
#define OPTION_VAL_16_HU NULL
#define OPTION_VAL_32_HU NULL
#define OPTION_VAL_64_HU NULL
#define OPTION_VAL_1_O2_HU NULL
#define OPTION_VAL_2_O2_HU NULL
#define Q88_SOUND_BOARD_LABEL_HU NULL
#define Q88_SOUND_BOARD_INFO_0_HU NULL
#define OPTION_VAL_OPN_HU NULL
#define OPTION_VAL_OPNA_HU NULL
#define Q88_USE_FDC_WAIT_LABEL_HU NULL
#define Q88_USE_FDC_WAIT_INFO_0_HU NULL
#define Q88_PCG_8100_LABEL_HU NULL
#define Q88_PCG_8100_INFO_0_HU NULL
#define Q88_SAVE_TO_DISK_IMAGE_LABEL_HU NULL
#define Q88_SAVE_TO_DISK_IMAGE_INFO_0_HU NULL
#define Q88_RUMBLE_LABEL_HU NULL
#define Q88_RUMBLE_INFO_0_HU NULL
#define Q88_SCREEN_SIZE_LABEL_HU NULL
#define Q88_SCREEN_SIZE_INFO_0_HU NULL
#define Q88_SCREEN_SIZE_INFO_1_HU NULL
#define Q88_SCREEN_SIZE_INFO_2_HU NULL
#define OPTION_VAL_FULL_HU NULL
#define OPTION_VAL_HALF_HU NULL

struct retro_core_option_v2_category option_cats_hu[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_hu[] = {
   { 
      "q88_basic_mode", 
      Q88_BASIC_MODE_LABEL_HU,
      NULL, 
      Q88_BASIC_MODE_INFO_0_HU,
      NULL,
      NULL,
      {
         { "N88 V2",  OPTION_VAL_N88_V2_HU },
         { "N88 V1H", OPTION_VAL_N88_V1H_HU },
         { "N88 V1S", OPTION_VAL_N88_V1S_HU },
         { "N",       OPTION_VAL_N_HU },
         { NULL, NULL }
      },
      "N88 V2"
   },

   { 
      "q88_sub_cpu_mode",
      Q88_SUB_CPU_MODE_LABEL_HU,
      NULL,
      Q88_SUB_CPU_MODE_INFO_0_HU,
      NULL,
      NULL,
      {
         { "0", OPTION_VAL_0_HU},
         { "1", OPTION_VAL_1_HU},
         { "2", OPTION_VAL_2_HU},
         { NULL, NULL },
      },
      "0"
   },

   { 
      "q88_cpu_clock", 
      Q88_CPU_CLOCK_LABEL_HU,
      NULL, 
      Q88_CPU_CLOCK_INFO_0_HU,
      NULL,
      NULL,
      {
         { "4",  OPTION_VAL_4_HU },
         { "8",  OPTION_VAL_8_HU },
         { "16", OPTION_VAL_16_HU },
         { "32", OPTION_VAL_32_HU },
         { "64", OPTION_VAL_64_HU },
         { "1",  OPTION_VAL_1_O2_HU },
         { "2",  OPTION_VAL_2_O2_HU },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      Q88_SOUND_BOARD_LABEL_HU,
      NULL, 
      Q88_SOUND_BOARD_INFO_0_HU,
      NULL,
      NULL,
      {
         { "OPN",  OPTION_VAL_OPN_HU },
         { "OPNA", OPTION_VAL_OPNA_HU},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      Q88_USE_FDC_WAIT_LABEL_HU,
      NULL, 
      Q88_USE_FDC_WAIT_INFO_0_HU,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_pcg-8100", 
      Q88_PCG_8100_LABEL_HU,
      NULL, 
      Q88_PCG_8100_INFO_0_HU,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   {
      "q88_save_to_disk_image", 
      Q88_SAVE_TO_DISK_IMAGE_LABEL_HU,
      NULL, 
      Q88_SAVE_TO_DISK_IMAGE_INFO_0_HU,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   { 
      "q88_rumble", 
      Q88_RUMBLE_LABEL_HU,
      NULL, 
      Q88_RUMBLE_INFO_0_HU,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_screen_size", 
      Q88_SCREEN_SIZE_LABEL_HU,
      NULL, 
#if defined (PSP)
      Q88_SCREEN_SIZE_INFO_0_HU,
#elif defined (_3DS)
      Q88_SCREEN_SIZE_INFO_1_HU,
#else
      Q88_SCREEN_SIZE_INFO_2_HU,
#endif
      NULL,
      NULL,
      {
         { "full",  OPTION_VAL_FULL_HU },
         { "half",  OPTION_VAL_HALF_HU },
         { NULL, NULL }
      },
#if defined (PSP) || defined (_3DS)
      "half"
#else
      "full"
#endif
   },

   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_hu = {
   option_cats_hu,
   option_defs_hu
};

/* RETRO_LANGUAGE_ID */

#define Q88_BASIC_MODE_LABEL_ID NULL
#define Q88_BASIC_MODE_INFO_0_ID NULL
#define OPTION_VAL_N88_V2_ID NULL
#define OPTION_VAL_N88_V1H_ID NULL
#define OPTION_VAL_N88_V1S_ID NULL
#define OPTION_VAL_N_ID NULL
#define Q88_SUB_CPU_MODE_LABEL_ID NULL
#define Q88_SUB_CPU_MODE_INFO_0_ID NULL
#define OPTION_VAL_0_ID NULL
#define OPTION_VAL_1_ID NULL
#define OPTION_VAL_2_ID NULL
#define Q88_CPU_CLOCK_LABEL_ID NULL
#define Q88_CPU_CLOCK_INFO_0_ID NULL
#define OPTION_VAL_4_ID NULL
#define OPTION_VAL_8_ID NULL
#define OPTION_VAL_16_ID NULL
#define OPTION_VAL_32_ID NULL
#define OPTION_VAL_64_ID NULL
#define OPTION_VAL_1_O2_ID NULL
#define OPTION_VAL_2_O2_ID NULL
#define Q88_SOUND_BOARD_LABEL_ID NULL
#define Q88_SOUND_BOARD_INFO_0_ID NULL
#define OPTION_VAL_OPN_ID NULL
#define OPTION_VAL_OPNA_ID NULL
#define Q88_USE_FDC_WAIT_LABEL_ID NULL
#define Q88_USE_FDC_WAIT_INFO_0_ID NULL
#define Q88_PCG_8100_LABEL_ID NULL
#define Q88_PCG_8100_INFO_0_ID NULL
#define Q88_SAVE_TO_DISK_IMAGE_LABEL_ID NULL
#define Q88_SAVE_TO_DISK_IMAGE_INFO_0_ID NULL
#define Q88_RUMBLE_LABEL_ID NULL
#define Q88_RUMBLE_INFO_0_ID NULL
#define Q88_SCREEN_SIZE_LABEL_ID NULL
#define Q88_SCREEN_SIZE_INFO_0_ID NULL
#define Q88_SCREEN_SIZE_INFO_1_ID NULL
#define Q88_SCREEN_SIZE_INFO_2_ID NULL
#define OPTION_VAL_FULL_ID NULL
#define OPTION_VAL_HALF_ID NULL

struct retro_core_option_v2_category option_cats_id[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_id[] = {
   { 
      "q88_basic_mode", 
      Q88_BASIC_MODE_LABEL_ID,
      NULL, 
      Q88_BASIC_MODE_INFO_0_ID,
      NULL,
      NULL,
      {
         { "N88 V2",  OPTION_VAL_N88_V2_ID },
         { "N88 V1H", OPTION_VAL_N88_V1H_ID },
         { "N88 V1S", OPTION_VAL_N88_V1S_ID },
         { "N",       OPTION_VAL_N_ID },
         { NULL, NULL }
      },
      "N88 V2"
   },

   { 
      "q88_sub_cpu_mode",
      Q88_SUB_CPU_MODE_LABEL_ID,
      NULL,
      Q88_SUB_CPU_MODE_INFO_0_ID,
      NULL,
      NULL,
      {
         { "0", OPTION_VAL_0_ID},
         { "1", OPTION_VAL_1_ID},
         { "2", OPTION_VAL_2_ID},
         { NULL, NULL },
      },
      "0"
   },

   { 
      "q88_cpu_clock", 
      Q88_CPU_CLOCK_LABEL_ID,
      NULL, 
      Q88_CPU_CLOCK_INFO_0_ID,
      NULL,
      NULL,
      {
         { "4",  OPTION_VAL_4_ID },
         { "8",  OPTION_VAL_8_ID },
         { "16", OPTION_VAL_16_ID },
         { "32", OPTION_VAL_32_ID },
         { "64", OPTION_VAL_64_ID },
         { "1",  OPTION_VAL_1_O2_ID },
         { "2",  OPTION_VAL_2_O2_ID },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      Q88_SOUND_BOARD_LABEL_ID,
      NULL, 
      Q88_SOUND_BOARD_INFO_0_ID,
      NULL,
      NULL,
      {
         { "OPN",  OPTION_VAL_OPN_ID },
         { "OPNA", OPTION_VAL_OPNA_ID},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      Q88_USE_FDC_WAIT_LABEL_ID,
      NULL, 
      Q88_USE_FDC_WAIT_INFO_0_ID,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_pcg-8100", 
      Q88_PCG_8100_LABEL_ID,
      NULL, 
      Q88_PCG_8100_INFO_0_ID,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   {
      "q88_save_to_disk_image", 
      Q88_SAVE_TO_DISK_IMAGE_LABEL_ID,
      NULL, 
      Q88_SAVE_TO_DISK_IMAGE_INFO_0_ID,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   { 
      "q88_rumble", 
      Q88_RUMBLE_LABEL_ID,
      NULL, 
      Q88_RUMBLE_INFO_0_ID,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_screen_size", 
      Q88_SCREEN_SIZE_LABEL_ID,
      NULL, 
#if defined (PSP)
      Q88_SCREEN_SIZE_INFO_0_ID,
#elif defined (_3DS)
      Q88_SCREEN_SIZE_INFO_1_ID,
#else
      Q88_SCREEN_SIZE_INFO_2_ID,
#endif
      NULL,
      NULL,
      {
         { "full",  OPTION_VAL_FULL_ID },
         { "half",  OPTION_VAL_HALF_ID },
         { NULL, NULL }
      },
#if defined (PSP) || defined (_3DS)
      "half"
#else
      "full"
#endif
   },

   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_id = {
   option_cats_id,
   option_defs_id
};

/* RETRO_LANGUAGE_IT */

#define Q88_BASIC_MODE_LABEL_IT "Modalità BASIC"
#define Q88_BASIC_MODE_INFO_0_IT "Consigliato: N88-BASIC V2/V1H per il software PC-8800, N-BASIC per il software PC-8000.\n\- Se il software PC-8800 funziona troppo velocemente in modalità V2, usa una modalità V1.\n\- I file BIOS sono richiesti per la modalità N-BASIC. Vedi le informazioni principali."
#define OPTION_VAL_N88_V2_IT NULL
#define OPTION_VAL_N88_V1H_IT NULL
#define OPTION_VAL_N88_V1S_IT NULL
#define OPTION_VAL_N_IT NULL
#define Q88_SUB_CPU_MODE_LABEL_IT "Modalità sub-CPU"
#define Q88_SUB_CPU_MODE_INFO_0_IT "Consigliato: Esegui SubCPU solo durante l'accesso al disco."
#define OPTION_VAL_0_IT "Eseguire SubCPU solo durante l'accesso al disco"
#define OPTION_VAL_1_IT "Eseguire entrambe le CPU durante l'accesso al disco"
#define OPTION_VAL_2_IT "Eseguire sempre entrambe le CPU"
#define Q88_CPU_CLOCK_LABEL_IT NULL
#define Q88_CPU_CLOCK_INFO_0_IT "Consigliato: 4MHz o 8MHz. Alcuni software possono funzionare troppo velocemente con una CPU 8MHz."
#define OPTION_VAL_4_IT "4 MHz (NEC μPD780)"
#define OPTION_VAL_8_IT "8 MHz (NEC μPD70008)"
#define OPTION_VAL_16_IT NULL
#define OPTION_VAL_32_IT NULL
#define OPTION_VAL_64_IT NULL
#define OPTION_VAL_1_O2_IT NULL
#define OPTION_VAL_2_O2_IT NULL
#define Q88_SOUND_BOARD_LABEL_IT "Scheda audio"
#define Q88_SOUND_BOARD_INFO_0_IT "Consigliato: OPNA. Alcuni software suoneranno diversi quando si utilizza l'hardware OPN."
#define OPTION_VAL_OPN_IT NULL
#define OPTION_VAL_OPNA_IT NULL
#define Q88_USE_FDC_WAIT_LABEL_IT NULL
#define Q88_USE_FDC_WAIT_INFO_0_IT "Consigliato: ACCESO. Abilita la sincronizzazione IO più accurata per il controller disco floppy."
#define Q88_PCG_8100_LABEL_IT "Usa PCG-8100"
#define Q88_PCG_8100_INFO_0_IT "Consigliato: OFF. Può essere richiesto per alcuni software PC-8000."
#define Q88_SAVE_TO_DISK_IMAGE_LABEL_IT "Salva su immagine disco"
#define Q88_SAVE_TO_DISK_IMAGE_INFO_0_IT "Consigliato: OFF. Cambia il comportamento di salvataggio preferito del nucleo.\n\- SPENTO: I dati scritti su dischetti saranno memorizzati in un file separato nella cartella di salvataggio del frontend.\n\- ACCESO: i dati verranno scritti direttamente sui file del disco caricato. Non funzionerà con il contenuto ziped."
#define Q88_RUMBLE_LABEL_IT "Vibrazione sull'accesso al disco"
#define Q88_RUMBLE_INFO_0_IT "Consigliato: N/A. Imita i suoni di lettura sul regolatore del disco floppy usando il rombo del regolatore."
#define Q88_SCREEN_SIZE_LABEL_IT "Dimensione schermo"
#define Q88_SCREEN_SIZE_INFO_0_IT "Consigliato: a metà. Consente al nucleo di ridimensionare l'immagine. Consigliato per la schermata PSP."
#define Q88_SCREEN_SIZE_INFO_1_IT "Consigliato: a metà. Consente al nucleo di ridimensionare l'immagine. Consigliato per la schermata Nintendo 3DS."
#define Q88_SCREEN_SIZE_INFO_2_IT "Consigliato: Pieno. Consente al nucleo di ridimensionare l'immagine. Consigliato solo per le altezze di visualizzazione inferiori a 400."
#define OPTION_VAL_FULL_IT "Pieno (640x400)"
#define OPTION_VAL_HALF_IT "Metà (320x200)"

struct retro_core_option_v2_category option_cats_it[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_it[] = {
   { 
      "q88_basic_mode", 
      Q88_BASIC_MODE_LABEL_IT,
      NULL, 
      Q88_BASIC_MODE_INFO_0_IT,
      NULL,
      NULL,
      {
         { "N88 V2",  OPTION_VAL_N88_V2_IT },
         { "N88 V1H", OPTION_VAL_N88_V1H_IT },
         { "N88 V1S", OPTION_VAL_N88_V1S_IT },
         { "N",       OPTION_VAL_N_IT },
         { NULL, NULL }
      },
      "N88 V2"
   },

   { 
      "q88_sub_cpu_mode",
      Q88_SUB_CPU_MODE_LABEL_IT,
      NULL,
      Q88_SUB_CPU_MODE_INFO_0_IT,
      NULL,
      NULL,
      {
         { "0", OPTION_VAL_0_IT},
         { "1", OPTION_VAL_1_IT},
         { "2", OPTION_VAL_2_IT},
         { NULL, NULL },
      },
      "0"
   },

   { 
      "q88_cpu_clock", 
      Q88_CPU_CLOCK_LABEL_IT,
      NULL, 
      Q88_CPU_CLOCK_INFO_0_IT,
      NULL,
      NULL,
      {
         { "4",  OPTION_VAL_4_IT },
         { "8",  OPTION_VAL_8_IT },
         { "16", OPTION_VAL_16_IT },
         { "32", OPTION_VAL_32_IT },
         { "64", OPTION_VAL_64_IT },
         { "1",  OPTION_VAL_1_O2_IT },
         { "2",  OPTION_VAL_2_O2_IT },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      Q88_SOUND_BOARD_LABEL_IT,
      NULL, 
      Q88_SOUND_BOARD_INFO_0_IT,
      NULL,
      NULL,
      {
         { "OPN",  OPTION_VAL_OPN_IT },
         { "OPNA", OPTION_VAL_OPNA_IT},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      Q88_USE_FDC_WAIT_LABEL_IT,
      NULL, 
      Q88_USE_FDC_WAIT_INFO_0_IT,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_pcg-8100", 
      Q88_PCG_8100_LABEL_IT,
      NULL, 
      Q88_PCG_8100_INFO_0_IT,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   {
      "q88_save_to_disk_image", 
      Q88_SAVE_TO_DISK_IMAGE_LABEL_IT,
      NULL, 
      Q88_SAVE_TO_DISK_IMAGE_INFO_0_IT,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   { 
      "q88_rumble", 
      Q88_RUMBLE_LABEL_IT,
      NULL, 
      Q88_RUMBLE_INFO_0_IT,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_screen_size", 
      Q88_SCREEN_SIZE_LABEL_IT,
      NULL, 
#if defined (PSP)
      Q88_SCREEN_SIZE_INFO_0_IT,
#elif defined (_3DS)
      Q88_SCREEN_SIZE_INFO_1_IT,
#else
      Q88_SCREEN_SIZE_INFO_2_IT,
#endif
      NULL,
      NULL,
      {
         { "full",  OPTION_VAL_FULL_IT },
         { "half",  OPTION_VAL_HALF_IT },
         { NULL, NULL }
      },
#if defined (PSP) || defined (_3DS)
      "half"
#else
      "full"
#endif
   },

   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_it = {
   option_cats_it,
   option_defs_it
};

/* RETRO_LANGUAGE_JA */

#define Q88_BASIC_MODE_LABEL_JA "BASICモード"
#define Q88_BASIC_MODE_INFO_0_JA "推奨：PC-8800シリーズソフトウェアの場合はN88 V2 / V1H、PC-8000シリーズソフトウェアの場合は N。"
#define OPTION_VAL_N88_V2_JA NULL
#define OPTION_VAL_N88_V1H_JA NULL
#define OPTION_VAL_N88_V1S_JA NULL
#define OPTION_VAL_N_JA NULL
#define Q88_SUB_CPU_MODE_LABEL_JA "Sub-CPU駆動"
#define Q88_SUB_CPU_MODE_INFO_0_JA "推奨：ディスク処理中、Sub-CPUのみ駆動させる"
#define OPTION_VAL_0_JA "ディスク処理中、Sub-CPUのみ駆動させる"
#define OPTION_VAL_1_JA "ディスク処理中、両CPUを駆動させる"
#define OPTION_VAL_2_JA "常時、両CPUを駆動させる"
#define Q88_CPU_CLOCK_LABEL_JA "CPU クロック"
#define Q88_CPU_CLOCK_INFO_0_JA "推奨：4MHzまたは8MHz。 一部のソフトウェアは、8MHz CPUでは高速に実行される場合があります。"
#define OPTION_VAL_4_JA "4 MHz (NEC μPD780)"
#define OPTION_VAL_8_JA "8 MHz (NEC μPD70008)"
#define OPTION_VAL_16_JA "16 MHz (オーバークロック)"
#define OPTION_VAL_32_JA "32 MHz (オーバークロック)"
#define OPTION_VAL_64_JA "64 MHz (オーバークロック)"
#define OPTION_VAL_1_O2_JA "1 MHz (アンダークロック)"
#define OPTION_VAL_2_O2_JA "2 MHz (アンダークロック)"
#define Q88_SOUND_BOARD_LABEL_JA "サウンドボード"
#define Q88_SOUND_BOARD_INFO_0_JA "推奨：OPNA。 OPNハードウェアを使用すると、一部のソフトウェアのサウンドが異なります。"
#define OPTION_VAL_OPN_JA NULL
#define OPTION_VAL_OPNA_JA NULL
#define Q88_USE_FDC_WAIT_LABEL_JA "FDCウエイト"
#define Q88_USE_FDC_WAIT_INFO_0_JA "推奨：ON。 FDCの処理にウエイトをいれます。FDCの処理速度に依存する アプリケーションの場合、動くようになる可能性があります。"
#define Q88_PCG_8100_LABEL_JA "PCG-8100"
#define Q88_PCG_8100_INFO_0_JA "推奨：OFF。 一部のPC-8000シリーズソフトウェアに必要な場合があります。 PCG-8100 のサウンドには対応していません。"
#define Q88_SAVE_TO_DISK_IMAGE_LABEL_JA "ディスクイメージに保存"
#define Q88_SAVE_TO_DISK_IMAGE_INFO_0_JA "推奨：OFF。 コアが挿入されたフロッピーディスクにデータを書き換えることを許可します。 解凍されたコンテンツでのみ動作します。"
#define Q88_RUMBLE_LABEL_JA "ディスクアクセスでランブル"
#define Q88_RUMBLE_INFO_0_JA "推奨：N/A。 コントローラーのランブルを使用して、FDCの読み取り音を模倣します。"
#define Q88_SCREEN_SIZE_LABEL_JA "画面サイズ"
#define Q88_SCREEN_SIZE_INFO_0_JA "推奨：半分。 コアがイメージを縮小できるようにします。 PSP画面に推奨されます。"
#define Q88_SCREEN_SIZE_INFO_1_JA "推奨：半分。 コアがイメージを縮小できるようにします。 Nintendo 3DS画面に推奨されます。"
#define Q88_SCREEN_SIZE_INFO_2_JA "推奨：フル。 コアがイメージを縮小できるようにします。 ディスプレイの高さが400未満の場合にのみ推奨されます。"
#define OPTION_VAL_FULL_JA "フル（640x400）"
#define OPTION_VAL_HALF_JA "半分 (320x200)"

struct retro_core_option_v2_category option_cats_ja[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_ja[] = {
   { 
      "q88_basic_mode", 
      Q88_BASIC_MODE_LABEL_JA,
      NULL, 
      Q88_BASIC_MODE_INFO_0_JA,
      NULL,
      NULL,
      {
         { "N88 V2",  OPTION_VAL_N88_V2_JA },
         { "N88 V1H", OPTION_VAL_N88_V1H_JA },
         { "N88 V1S", OPTION_VAL_N88_V1S_JA },
         { "N",       OPTION_VAL_N_JA },
         { NULL, NULL }
      },
      "N88 V2"
   },

   { 
      "q88_sub_cpu_mode",
      Q88_SUB_CPU_MODE_LABEL_JA,
      NULL,
      Q88_SUB_CPU_MODE_INFO_0_JA,
      NULL,
      NULL,
      {
         { "0", OPTION_VAL_0_JA},
         { "1", OPTION_VAL_1_JA},
         { "2", OPTION_VAL_2_JA},
         { NULL, NULL },
      },
      "0"
   },

   { 
      "q88_cpu_clock", 
      Q88_CPU_CLOCK_LABEL_JA,
      NULL, 
      Q88_CPU_CLOCK_INFO_0_JA,
      NULL,
      NULL,
      {
         { "4",  OPTION_VAL_4_JA },
         { "8",  OPTION_VAL_8_JA },
         { "16", OPTION_VAL_16_JA },
         { "32", OPTION_VAL_32_JA },
         { "64", OPTION_VAL_64_JA },
         { "1",  OPTION_VAL_1_O2_JA },
         { "2",  OPTION_VAL_2_O2_JA },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      Q88_SOUND_BOARD_LABEL_JA,
      NULL, 
      Q88_SOUND_BOARD_INFO_0_JA,
      NULL,
      NULL,
      {
         { "OPN",  OPTION_VAL_OPN_JA },
         { "OPNA", OPTION_VAL_OPNA_JA},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      Q88_USE_FDC_WAIT_LABEL_JA,
      NULL, 
      Q88_USE_FDC_WAIT_INFO_0_JA,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_pcg-8100", 
      Q88_PCG_8100_LABEL_JA,
      NULL, 
      Q88_PCG_8100_INFO_0_JA,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   {
      "q88_save_to_disk_image", 
      Q88_SAVE_TO_DISK_IMAGE_LABEL_JA,
      NULL, 
      Q88_SAVE_TO_DISK_IMAGE_INFO_0_JA,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   { 
      "q88_rumble", 
      Q88_RUMBLE_LABEL_JA,
      NULL, 
      Q88_RUMBLE_INFO_0_JA,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_screen_size", 
      Q88_SCREEN_SIZE_LABEL_JA,
      NULL, 
#if defined (PSP)
      Q88_SCREEN_SIZE_INFO_0_JA,
#elif defined (_3DS)
      Q88_SCREEN_SIZE_INFO_1_JA,
#else
      Q88_SCREEN_SIZE_INFO_2_JA,
#endif
      NULL,
      NULL,
      {
         { "full",  OPTION_VAL_FULL_JA },
         { "half",  OPTION_VAL_HALF_JA },
         { NULL, NULL }
      },
#if defined (PSP) || defined (_3DS)
      "half"
#else
      "full"
#endif
   },

   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_ja = {
   option_cats_ja,
   option_defs_ja
};

/* RETRO_LANGUAGE_KO */

#define Q88_BASIC_MODE_LABEL_KO "BASIC 모드"
#define Q88_BASIC_MODE_INFO_0_KO "권장: PC-8800 소프트웨어에는 N88-BASIC V2/V1H, PC-8000 소프트웨어에는 N-BASIC\n\- PC-8800 소프트웨어가 V2 모드에서 너무 빨리 실행된다면 V1 모드를 사용하십시오.\n\- N-BASIC 모드를 사용하려면 BIOS 파일이 필요합니다. 코어 정보를 참조하십시오."
#define OPTION_VAL_N88_V2_KO NULL
#define OPTION_VAL_N88_V1H_KO NULL
#define OPTION_VAL_N88_V1S_KO NULL
#define OPTION_VAL_N_KO NULL
#define Q88_SUB_CPU_MODE_LABEL_KO "보조 CPU 모드"
#define Q88_SUB_CPU_MODE_INFO_0_KO "권장: 디스크 액세스 중일 때 보조 CPU만 사용"
#define OPTION_VAL_0_KO "디스크 액세스 중일 때 보조 CPU만 사용"
#define OPTION_VAL_1_KO "디스크 액세스 중일 때 두 CPU 모두 사용"
#define OPTION_VAL_2_KO "항상 두 CPU 모두 사용"
#define Q88_CPU_CLOCK_LABEL_KO "CPU 클럭"
#define Q88_CPU_CLOCK_INFO_0_KO "권장: 4MHz 또는 8MHz. 일부 소프트웨어는 8MHz CPU에서 너무 빠르게 실행될 수도 있습니다."
#define OPTION_VAL_4_KO NULL
#define OPTION_VAL_8_KO NULL
#define OPTION_VAL_16_KO "16 MHz (오버클럭)"
#define OPTION_VAL_32_KO "32 MHz (오버클럭)"
#define OPTION_VAL_64_KO "64 MHz (오버클럭)"
#define OPTION_VAL_1_O2_KO "1 MHz (언더클럭)"
#define OPTION_VAL_2_O2_KO "2 MHz (언더클럭)"
#define Q88_SOUND_BOARD_LABEL_KO "사운드 보드"
#define Q88_SOUND_BOARD_INFO_0_KO "권장: OPNA. 일부 소프트웨어는 OPN 하드웨어 사용 시 소리 출력이 달라질 수 있습니다."
#define OPTION_VAL_OPN_KO NULL
#define OPTION_VAL_OPNA_KO NULL
#define Q88_USE_FDC_WAIT_LABEL_KO NULL
#define Q88_USE_FDC_WAIT_INFO_0_KO "권장: ON. 플로피 디스크 컨트롤러의 IO 타이밍을 더욱 정확하게 합니다."
#define Q88_PCG_8100_LABEL_KO "PCG-8100 사용"
#define Q88_PCG_8100_INFO_0_KO "권장: OFF. 일부 PC-8000 소프트웨어의 구동에 필요할 수도 있습니다."
#define Q88_SAVE_TO_DISK_IMAGE_LABEL_KO "디스크 이미지에 저장"
#define Q88_SAVE_TO_DISK_IMAGE_INFO_0_KO "권장: OFF. 코어가 선호할 저장 방식을 변경합니다.\n\- OFF: 플로피 디스크에 저장된 데이터는 프론트엔드의 저장 디렉토리에 개별 파일로 보관됩니다.\n\- ON: 데이터가 불러와진 디스크 파일에 직접 쓰여집니다. 압축된 컨텐츠에서는 작동하지 않습니다."
#define Q88_RUMBLE_LABEL_KO "디스크 액세스 중 진동"
#define Q88_RUMBLE_INFO_0_KO "권장: N/A. 플로피 디스크 컨트롤러가 디스크 읽는 소리를 컨트롤러의 진동으로 흉내냅니다."
#define Q88_SCREEN_SIZE_LABEL_KO "화면 크기"
#define Q88_SCREEN_SIZE_INFO_0_KO "권장: 절반. 코어가 출력되는 이미지를 줄일 수 있게 합니다. PSP 화면에 권장됩니다."
#define Q88_SCREEN_SIZE_INFO_1_KO "권장: 절반. 코어가 출력되는 이미지를 줄일 수 있게 합니다. Nintendo 3DS 화면에 권장됩니다."
#define Q88_SCREEN_SIZE_INFO_2_KO "권장: 전체. 코어가 출력되는 이미지를 줄일 수 있게 합니다. 화면 높이가 400 미만인 화면에만 사용할 것을 권장합니다."
#define OPTION_VAL_FULL_KO "전체 (640x400)"
#define OPTION_VAL_HALF_KO "절반 (320x200)"

struct retro_core_option_v2_category option_cats_ko[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_ko[] = {
   { 
      "q88_basic_mode", 
      Q88_BASIC_MODE_LABEL_KO,
      NULL, 
      Q88_BASIC_MODE_INFO_0_KO,
      NULL,
      NULL,
      {
         { "N88 V2",  OPTION_VAL_N88_V2_KO },
         { "N88 V1H", OPTION_VAL_N88_V1H_KO },
         { "N88 V1S", OPTION_VAL_N88_V1S_KO },
         { "N",       OPTION_VAL_N_KO },
         { NULL, NULL }
      },
      "N88 V2"
   },

   { 
      "q88_sub_cpu_mode",
      Q88_SUB_CPU_MODE_LABEL_KO,
      NULL,
      Q88_SUB_CPU_MODE_INFO_0_KO,
      NULL,
      NULL,
      {
         { "0", OPTION_VAL_0_KO},
         { "1", OPTION_VAL_1_KO},
         { "2", OPTION_VAL_2_KO},
         { NULL, NULL },
      },
      "0"
   },

   { 
      "q88_cpu_clock", 
      Q88_CPU_CLOCK_LABEL_KO,
      NULL, 
      Q88_CPU_CLOCK_INFO_0_KO,
      NULL,
      NULL,
      {
         { "4",  OPTION_VAL_4_KO },
         { "8",  OPTION_VAL_8_KO },
         { "16", OPTION_VAL_16_KO },
         { "32", OPTION_VAL_32_KO },
         { "64", OPTION_VAL_64_KO },
         { "1",  OPTION_VAL_1_O2_KO },
         { "2",  OPTION_VAL_2_O2_KO },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      Q88_SOUND_BOARD_LABEL_KO,
      NULL, 
      Q88_SOUND_BOARD_INFO_0_KO,
      NULL,
      NULL,
      {
         { "OPN",  OPTION_VAL_OPN_KO },
         { "OPNA", OPTION_VAL_OPNA_KO},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      Q88_USE_FDC_WAIT_LABEL_KO,
      NULL, 
      Q88_USE_FDC_WAIT_INFO_0_KO,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_pcg-8100", 
      Q88_PCG_8100_LABEL_KO,
      NULL, 
      Q88_PCG_8100_INFO_0_KO,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   {
      "q88_save_to_disk_image", 
      Q88_SAVE_TO_DISK_IMAGE_LABEL_KO,
      NULL, 
      Q88_SAVE_TO_DISK_IMAGE_INFO_0_KO,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   { 
      "q88_rumble", 
      Q88_RUMBLE_LABEL_KO,
      NULL, 
      Q88_RUMBLE_INFO_0_KO,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_screen_size", 
      Q88_SCREEN_SIZE_LABEL_KO,
      NULL, 
#if defined (PSP)
      Q88_SCREEN_SIZE_INFO_0_KO,
#elif defined (_3DS)
      Q88_SCREEN_SIZE_INFO_1_KO,
#else
      Q88_SCREEN_SIZE_INFO_2_KO,
#endif
      NULL,
      NULL,
      {
         { "full",  OPTION_VAL_FULL_KO },
         { "half",  OPTION_VAL_HALF_KO },
         { NULL, NULL }
      },
#if defined (PSP) || defined (_3DS)
      "half"
#else
      "full"
#endif
   },

   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_ko = {
   option_cats_ko,
   option_defs_ko
};

/* RETRO_LANGUAGE_MT */

#define Q88_BASIC_MODE_LABEL_MT NULL
#define Q88_BASIC_MODE_INFO_0_MT NULL
#define OPTION_VAL_N88_V2_MT NULL
#define OPTION_VAL_N88_V1H_MT NULL
#define OPTION_VAL_N88_V1S_MT NULL
#define OPTION_VAL_N_MT NULL
#define Q88_SUB_CPU_MODE_LABEL_MT NULL
#define Q88_SUB_CPU_MODE_INFO_0_MT NULL
#define OPTION_VAL_0_MT NULL
#define OPTION_VAL_1_MT NULL
#define OPTION_VAL_2_MT NULL
#define Q88_CPU_CLOCK_LABEL_MT NULL
#define Q88_CPU_CLOCK_INFO_0_MT NULL
#define OPTION_VAL_4_MT NULL
#define OPTION_VAL_8_MT NULL
#define OPTION_VAL_16_MT NULL
#define OPTION_VAL_32_MT NULL
#define OPTION_VAL_64_MT NULL
#define OPTION_VAL_1_O2_MT NULL
#define OPTION_VAL_2_O2_MT NULL
#define Q88_SOUND_BOARD_LABEL_MT NULL
#define Q88_SOUND_BOARD_INFO_0_MT NULL
#define OPTION_VAL_OPN_MT NULL
#define OPTION_VAL_OPNA_MT NULL
#define Q88_USE_FDC_WAIT_LABEL_MT NULL
#define Q88_USE_FDC_WAIT_INFO_0_MT NULL
#define Q88_PCG_8100_LABEL_MT NULL
#define Q88_PCG_8100_INFO_0_MT NULL
#define Q88_SAVE_TO_DISK_IMAGE_LABEL_MT NULL
#define Q88_SAVE_TO_DISK_IMAGE_INFO_0_MT NULL
#define Q88_RUMBLE_LABEL_MT NULL
#define Q88_RUMBLE_INFO_0_MT NULL
#define Q88_SCREEN_SIZE_LABEL_MT NULL
#define Q88_SCREEN_SIZE_INFO_0_MT NULL
#define Q88_SCREEN_SIZE_INFO_1_MT NULL
#define Q88_SCREEN_SIZE_INFO_2_MT NULL
#define OPTION_VAL_FULL_MT NULL
#define OPTION_VAL_HALF_MT NULL

struct retro_core_option_v2_category option_cats_mt[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_mt[] = {
   { 
      "q88_basic_mode", 
      Q88_BASIC_MODE_LABEL_MT,
      NULL, 
      Q88_BASIC_MODE_INFO_0_MT,
      NULL,
      NULL,
      {
         { "N88 V2",  OPTION_VAL_N88_V2_MT },
         { "N88 V1H", OPTION_VAL_N88_V1H_MT },
         { "N88 V1S", OPTION_VAL_N88_V1S_MT },
         { "N",       OPTION_VAL_N_MT },
         { NULL, NULL }
      },
      "N88 V2"
   },

   { 
      "q88_sub_cpu_mode",
      Q88_SUB_CPU_MODE_LABEL_MT,
      NULL,
      Q88_SUB_CPU_MODE_INFO_0_MT,
      NULL,
      NULL,
      {
         { "0", OPTION_VAL_0_MT},
         { "1", OPTION_VAL_1_MT},
         { "2", OPTION_VAL_2_MT},
         { NULL, NULL },
      },
      "0"
   },

   { 
      "q88_cpu_clock", 
      Q88_CPU_CLOCK_LABEL_MT,
      NULL, 
      Q88_CPU_CLOCK_INFO_0_MT,
      NULL,
      NULL,
      {
         { "4",  OPTION_VAL_4_MT },
         { "8",  OPTION_VAL_8_MT },
         { "16", OPTION_VAL_16_MT },
         { "32", OPTION_VAL_32_MT },
         { "64", OPTION_VAL_64_MT },
         { "1",  OPTION_VAL_1_O2_MT },
         { "2",  OPTION_VAL_2_O2_MT },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      Q88_SOUND_BOARD_LABEL_MT,
      NULL, 
      Q88_SOUND_BOARD_INFO_0_MT,
      NULL,
      NULL,
      {
         { "OPN",  OPTION_VAL_OPN_MT },
         { "OPNA", OPTION_VAL_OPNA_MT},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      Q88_USE_FDC_WAIT_LABEL_MT,
      NULL, 
      Q88_USE_FDC_WAIT_INFO_0_MT,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_pcg-8100", 
      Q88_PCG_8100_LABEL_MT,
      NULL, 
      Q88_PCG_8100_INFO_0_MT,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   {
      "q88_save_to_disk_image", 
      Q88_SAVE_TO_DISK_IMAGE_LABEL_MT,
      NULL, 
      Q88_SAVE_TO_DISK_IMAGE_INFO_0_MT,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   { 
      "q88_rumble", 
      Q88_RUMBLE_LABEL_MT,
      NULL, 
      Q88_RUMBLE_INFO_0_MT,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_screen_size", 
      Q88_SCREEN_SIZE_LABEL_MT,
      NULL, 
#if defined (PSP)
      Q88_SCREEN_SIZE_INFO_0_MT,
#elif defined (_3DS)
      Q88_SCREEN_SIZE_INFO_1_MT,
#else
      Q88_SCREEN_SIZE_INFO_2_MT,
#endif
      NULL,
      NULL,
      {
         { "full",  OPTION_VAL_FULL_MT },
         { "half",  OPTION_VAL_HALF_MT },
         { NULL, NULL }
      },
#if defined (PSP) || defined (_3DS)
      "half"
#else
      "full"
#endif
   },

   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_mt = {
   option_cats_mt,
   option_defs_mt
};

/* RETRO_LANGUAGE_NL */

#define Q88_BASIC_MODE_LABEL_NL NULL
#define Q88_BASIC_MODE_INFO_0_NL NULL
#define OPTION_VAL_N88_V2_NL NULL
#define OPTION_VAL_N88_V1H_NL NULL
#define OPTION_VAL_N88_V1S_NL NULL
#define OPTION_VAL_N_NL NULL
#define Q88_SUB_CPU_MODE_LABEL_NL NULL
#define Q88_SUB_CPU_MODE_INFO_0_NL NULL
#define OPTION_VAL_0_NL NULL
#define OPTION_VAL_1_NL NULL
#define OPTION_VAL_2_NL NULL
#define Q88_CPU_CLOCK_LABEL_NL NULL
#define Q88_CPU_CLOCK_INFO_0_NL NULL
#define OPTION_VAL_4_NL NULL
#define OPTION_VAL_8_NL NULL
#define OPTION_VAL_16_NL NULL
#define OPTION_VAL_32_NL NULL
#define OPTION_VAL_64_NL NULL
#define OPTION_VAL_1_O2_NL NULL
#define OPTION_VAL_2_O2_NL NULL
#define Q88_SOUND_BOARD_LABEL_NL NULL
#define Q88_SOUND_BOARD_INFO_0_NL NULL
#define OPTION_VAL_OPN_NL NULL
#define OPTION_VAL_OPNA_NL NULL
#define Q88_USE_FDC_WAIT_LABEL_NL NULL
#define Q88_USE_FDC_WAIT_INFO_0_NL NULL
#define Q88_PCG_8100_LABEL_NL NULL
#define Q88_PCG_8100_INFO_0_NL NULL
#define Q88_SAVE_TO_DISK_IMAGE_LABEL_NL NULL
#define Q88_SAVE_TO_DISK_IMAGE_INFO_0_NL NULL
#define Q88_RUMBLE_LABEL_NL NULL
#define Q88_RUMBLE_INFO_0_NL NULL
#define Q88_SCREEN_SIZE_LABEL_NL NULL
#define Q88_SCREEN_SIZE_INFO_0_NL NULL
#define Q88_SCREEN_SIZE_INFO_1_NL NULL
#define Q88_SCREEN_SIZE_INFO_2_NL NULL
#define OPTION_VAL_FULL_NL NULL
#define OPTION_VAL_HALF_NL NULL

struct retro_core_option_v2_category option_cats_nl[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_nl[] = {
   { 
      "q88_basic_mode", 
      Q88_BASIC_MODE_LABEL_NL,
      NULL, 
      Q88_BASIC_MODE_INFO_0_NL,
      NULL,
      NULL,
      {
         { "N88 V2",  OPTION_VAL_N88_V2_NL },
         { "N88 V1H", OPTION_VAL_N88_V1H_NL },
         { "N88 V1S", OPTION_VAL_N88_V1S_NL },
         { "N",       OPTION_VAL_N_NL },
         { NULL, NULL }
      },
      "N88 V2"
   },

   { 
      "q88_sub_cpu_mode",
      Q88_SUB_CPU_MODE_LABEL_NL,
      NULL,
      Q88_SUB_CPU_MODE_INFO_0_NL,
      NULL,
      NULL,
      {
         { "0", OPTION_VAL_0_NL},
         { "1", OPTION_VAL_1_NL},
         { "2", OPTION_VAL_2_NL},
         { NULL, NULL },
      },
      "0"
   },

   { 
      "q88_cpu_clock", 
      Q88_CPU_CLOCK_LABEL_NL,
      NULL, 
      Q88_CPU_CLOCK_INFO_0_NL,
      NULL,
      NULL,
      {
         { "4",  OPTION_VAL_4_NL },
         { "8",  OPTION_VAL_8_NL },
         { "16", OPTION_VAL_16_NL },
         { "32", OPTION_VAL_32_NL },
         { "64", OPTION_VAL_64_NL },
         { "1",  OPTION_VAL_1_O2_NL },
         { "2",  OPTION_VAL_2_O2_NL },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      Q88_SOUND_BOARD_LABEL_NL,
      NULL, 
      Q88_SOUND_BOARD_INFO_0_NL,
      NULL,
      NULL,
      {
         { "OPN",  OPTION_VAL_OPN_NL },
         { "OPNA", OPTION_VAL_OPNA_NL},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      Q88_USE_FDC_WAIT_LABEL_NL,
      NULL, 
      Q88_USE_FDC_WAIT_INFO_0_NL,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_pcg-8100", 
      Q88_PCG_8100_LABEL_NL,
      NULL, 
      Q88_PCG_8100_INFO_0_NL,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   {
      "q88_save_to_disk_image", 
      Q88_SAVE_TO_DISK_IMAGE_LABEL_NL,
      NULL, 
      Q88_SAVE_TO_DISK_IMAGE_INFO_0_NL,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   { 
      "q88_rumble", 
      Q88_RUMBLE_LABEL_NL,
      NULL, 
      Q88_RUMBLE_INFO_0_NL,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_screen_size", 
      Q88_SCREEN_SIZE_LABEL_NL,
      NULL, 
#if defined (PSP)
      Q88_SCREEN_SIZE_INFO_0_NL,
#elif defined (_3DS)
      Q88_SCREEN_SIZE_INFO_1_NL,
#else
      Q88_SCREEN_SIZE_INFO_2_NL,
#endif
      NULL,
      NULL,
      {
         { "full",  OPTION_VAL_FULL_NL },
         { "half",  OPTION_VAL_HALF_NL },
         { NULL, NULL }
      },
#if defined (PSP) || defined (_3DS)
      "half"
#else
      "full"
#endif
   },

   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_nl = {
   option_cats_nl,
   option_defs_nl
};

/* RETRO_LANGUAGE_OC */

#define Q88_BASIC_MODE_LABEL_OC NULL
#define Q88_BASIC_MODE_INFO_0_OC NULL
#define OPTION_VAL_N88_V2_OC NULL
#define OPTION_VAL_N88_V1H_OC NULL
#define OPTION_VAL_N88_V1S_OC NULL
#define OPTION_VAL_N_OC NULL
#define Q88_SUB_CPU_MODE_LABEL_OC NULL
#define Q88_SUB_CPU_MODE_INFO_0_OC NULL
#define OPTION_VAL_0_OC NULL
#define OPTION_VAL_1_OC NULL
#define OPTION_VAL_2_OC NULL
#define Q88_CPU_CLOCK_LABEL_OC NULL
#define Q88_CPU_CLOCK_INFO_0_OC NULL
#define OPTION_VAL_4_OC NULL
#define OPTION_VAL_8_OC NULL
#define OPTION_VAL_16_OC NULL
#define OPTION_VAL_32_OC NULL
#define OPTION_VAL_64_OC NULL
#define OPTION_VAL_1_O2_OC NULL
#define OPTION_VAL_2_O2_OC NULL
#define Q88_SOUND_BOARD_LABEL_OC NULL
#define Q88_SOUND_BOARD_INFO_0_OC NULL
#define OPTION_VAL_OPN_OC NULL
#define OPTION_VAL_OPNA_OC NULL
#define Q88_USE_FDC_WAIT_LABEL_OC NULL
#define Q88_USE_FDC_WAIT_INFO_0_OC NULL
#define Q88_PCG_8100_LABEL_OC NULL
#define Q88_PCG_8100_INFO_0_OC NULL
#define Q88_SAVE_TO_DISK_IMAGE_LABEL_OC NULL
#define Q88_SAVE_TO_DISK_IMAGE_INFO_0_OC NULL
#define Q88_RUMBLE_LABEL_OC NULL
#define Q88_RUMBLE_INFO_0_OC NULL
#define Q88_SCREEN_SIZE_LABEL_OC NULL
#define Q88_SCREEN_SIZE_INFO_0_OC NULL
#define Q88_SCREEN_SIZE_INFO_1_OC NULL
#define Q88_SCREEN_SIZE_INFO_2_OC NULL
#define OPTION_VAL_FULL_OC NULL
#define OPTION_VAL_HALF_OC NULL

struct retro_core_option_v2_category option_cats_oc[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_oc[] = {
   { 
      "q88_basic_mode", 
      Q88_BASIC_MODE_LABEL_OC,
      NULL, 
      Q88_BASIC_MODE_INFO_0_OC,
      NULL,
      NULL,
      {
         { "N88 V2",  OPTION_VAL_N88_V2_OC },
         { "N88 V1H", OPTION_VAL_N88_V1H_OC },
         { "N88 V1S", OPTION_VAL_N88_V1S_OC },
         { "N",       OPTION_VAL_N_OC },
         { NULL, NULL }
      },
      "N88 V2"
   },

   { 
      "q88_sub_cpu_mode",
      Q88_SUB_CPU_MODE_LABEL_OC,
      NULL,
      Q88_SUB_CPU_MODE_INFO_0_OC,
      NULL,
      NULL,
      {
         { "0", OPTION_VAL_0_OC},
         { "1", OPTION_VAL_1_OC},
         { "2", OPTION_VAL_2_OC},
         { NULL, NULL },
      },
      "0"
   },

   { 
      "q88_cpu_clock", 
      Q88_CPU_CLOCK_LABEL_OC,
      NULL, 
      Q88_CPU_CLOCK_INFO_0_OC,
      NULL,
      NULL,
      {
         { "4",  OPTION_VAL_4_OC },
         { "8",  OPTION_VAL_8_OC },
         { "16", OPTION_VAL_16_OC },
         { "32", OPTION_VAL_32_OC },
         { "64", OPTION_VAL_64_OC },
         { "1",  OPTION_VAL_1_O2_OC },
         { "2",  OPTION_VAL_2_O2_OC },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      Q88_SOUND_BOARD_LABEL_OC,
      NULL, 
      Q88_SOUND_BOARD_INFO_0_OC,
      NULL,
      NULL,
      {
         { "OPN",  OPTION_VAL_OPN_OC },
         { "OPNA", OPTION_VAL_OPNA_OC},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      Q88_USE_FDC_WAIT_LABEL_OC,
      NULL, 
      Q88_USE_FDC_WAIT_INFO_0_OC,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_pcg-8100", 
      Q88_PCG_8100_LABEL_OC,
      NULL, 
      Q88_PCG_8100_INFO_0_OC,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   {
      "q88_save_to_disk_image", 
      Q88_SAVE_TO_DISK_IMAGE_LABEL_OC,
      NULL, 
      Q88_SAVE_TO_DISK_IMAGE_INFO_0_OC,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   { 
      "q88_rumble", 
      Q88_RUMBLE_LABEL_OC,
      NULL, 
      Q88_RUMBLE_INFO_0_OC,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_screen_size", 
      Q88_SCREEN_SIZE_LABEL_OC,
      NULL, 
#if defined (PSP)
      Q88_SCREEN_SIZE_INFO_0_OC,
#elif defined (_3DS)
      Q88_SCREEN_SIZE_INFO_1_OC,
#else
      Q88_SCREEN_SIZE_INFO_2_OC,
#endif
      NULL,
      NULL,
      {
         { "full",  OPTION_VAL_FULL_OC },
         { "half",  OPTION_VAL_HALF_OC },
         { NULL, NULL }
      },
#if defined (PSP) || defined (_3DS)
      "half"
#else
      "full"
#endif
   },

   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_oc = {
   option_cats_oc,
   option_defs_oc
};

/* RETRO_LANGUAGE_PL */

#define Q88_BASIC_MODE_LABEL_PL "Tryb PODSTAWOWY"
#define Q88_BASIC_MODE_INFO_0_PL NULL
#define OPTION_VAL_N88_V2_PL NULL
#define OPTION_VAL_N88_V1H_PL NULL
#define OPTION_VAL_N88_V1S_PL NULL
#define OPTION_VAL_N_PL NULL
#define Q88_SUB_CPU_MODE_LABEL_PL NULL
#define Q88_SUB_CPU_MODE_INFO_0_PL NULL
#define OPTION_VAL_0_PL NULL
#define OPTION_VAL_1_PL NULL
#define OPTION_VAL_2_PL NULL
#define Q88_CPU_CLOCK_LABEL_PL NULL
#define Q88_CPU_CLOCK_INFO_0_PL NULL
#define OPTION_VAL_4_PL NULL
#define OPTION_VAL_8_PL NULL
#define OPTION_VAL_16_PL NULL
#define OPTION_VAL_32_PL NULL
#define OPTION_VAL_64_PL NULL
#define OPTION_VAL_1_O2_PL NULL
#define OPTION_VAL_2_O2_PL NULL
#define Q88_SOUND_BOARD_LABEL_PL NULL
#define Q88_SOUND_BOARD_INFO_0_PL NULL
#define OPTION_VAL_OPN_PL NULL
#define OPTION_VAL_OPNA_PL NULL
#define Q88_USE_FDC_WAIT_LABEL_PL NULL
#define Q88_USE_FDC_WAIT_INFO_0_PL NULL
#define Q88_PCG_8100_LABEL_PL NULL
#define Q88_PCG_8100_INFO_0_PL NULL
#define Q88_SAVE_TO_DISK_IMAGE_LABEL_PL NULL
#define Q88_SAVE_TO_DISK_IMAGE_INFO_0_PL NULL
#define Q88_RUMBLE_LABEL_PL NULL
#define Q88_RUMBLE_INFO_0_PL NULL
#define Q88_SCREEN_SIZE_LABEL_PL NULL
#define Q88_SCREEN_SIZE_INFO_0_PL NULL
#define Q88_SCREEN_SIZE_INFO_1_PL NULL
#define Q88_SCREEN_SIZE_INFO_2_PL NULL
#define OPTION_VAL_FULL_PL NULL
#define OPTION_VAL_HALF_PL NULL

struct retro_core_option_v2_category option_cats_pl[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_pl[] = {
   { 
      "q88_basic_mode", 
      Q88_BASIC_MODE_LABEL_PL,
      NULL, 
      Q88_BASIC_MODE_INFO_0_PL,
      NULL,
      NULL,
      {
         { "N88 V2",  OPTION_VAL_N88_V2_PL },
         { "N88 V1H", OPTION_VAL_N88_V1H_PL },
         { "N88 V1S", OPTION_VAL_N88_V1S_PL },
         { "N",       OPTION_VAL_N_PL },
         { NULL, NULL }
      },
      "N88 V2"
   },

   { 
      "q88_sub_cpu_mode",
      Q88_SUB_CPU_MODE_LABEL_PL,
      NULL,
      Q88_SUB_CPU_MODE_INFO_0_PL,
      NULL,
      NULL,
      {
         { "0", OPTION_VAL_0_PL},
         { "1", OPTION_VAL_1_PL},
         { "2", OPTION_VAL_2_PL},
         { NULL, NULL },
      },
      "0"
   },

   { 
      "q88_cpu_clock", 
      Q88_CPU_CLOCK_LABEL_PL,
      NULL, 
      Q88_CPU_CLOCK_INFO_0_PL,
      NULL,
      NULL,
      {
         { "4",  OPTION_VAL_4_PL },
         { "8",  OPTION_VAL_8_PL },
         { "16", OPTION_VAL_16_PL },
         { "32", OPTION_VAL_32_PL },
         { "64", OPTION_VAL_64_PL },
         { "1",  OPTION_VAL_1_O2_PL },
         { "2",  OPTION_VAL_2_O2_PL },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      Q88_SOUND_BOARD_LABEL_PL,
      NULL, 
      Q88_SOUND_BOARD_INFO_0_PL,
      NULL,
      NULL,
      {
         { "OPN",  OPTION_VAL_OPN_PL },
         { "OPNA", OPTION_VAL_OPNA_PL},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      Q88_USE_FDC_WAIT_LABEL_PL,
      NULL, 
      Q88_USE_FDC_WAIT_INFO_0_PL,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_pcg-8100", 
      Q88_PCG_8100_LABEL_PL,
      NULL, 
      Q88_PCG_8100_INFO_0_PL,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   {
      "q88_save_to_disk_image", 
      Q88_SAVE_TO_DISK_IMAGE_LABEL_PL,
      NULL, 
      Q88_SAVE_TO_DISK_IMAGE_INFO_0_PL,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   { 
      "q88_rumble", 
      Q88_RUMBLE_LABEL_PL,
      NULL, 
      Q88_RUMBLE_INFO_0_PL,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_screen_size", 
      Q88_SCREEN_SIZE_LABEL_PL,
      NULL, 
#if defined (PSP)
      Q88_SCREEN_SIZE_INFO_0_PL,
#elif defined (_3DS)
      Q88_SCREEN_SIZE_INFO_1_PL,
#else
      Q88_SCREEN_SIZE_INFO_2_PL,
#endif
      NULL,
      NULL,
      {
         { "full",  OPTION_VAL_FULL_PL },
         { "half",  OPTION_VAL_HALF_PL },
         { NULL, NULL }
      },
#if defined (PSP) || defined (_3DS)
      "half"
#else
      "full"
#endif
   },

   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_pl = {
   option_cats_pl,
   option_defs_pl
};

/* RETRO_LANGUAGE_PT_BR */

#define Q88_BASIC_MODE_LABEL_PT_BR "Modo BASIC"
#define Q88_BASIC_MODE_INFO_0_PT_BR "Recomendado: N88-BASIC V2/V1H para o software do PC-8800, N-BASIC para o software do PC-8000.\n\- Se o software do PC-8800 for executado muito rápido no modo V2, teste com o modo V1.\n\- O modo N-BASIC requer os arquivos da BIOS. Veja as informações do núcleo."
#define OPTION_VAL_N88_V2_PT_BR NULL
#define OPTION_VAL_N88_V1H_PT_BR NULL
#define OPTION_VAL_N88_V1S_PT_BR NULL
#define OPTION_VAL_N_PT_BR NULL
#define Q88_SUB_CPU_MODE_LABEL_PT_BR "Modo da sub-CPU"
#define Q88_SUB_CPU_MODE_INFO_0_PT_BR "Recomendado: Executa só a sub-CPU ao acessar o disco."
#define OPTION_VAL_0_PT_BR "Executa só a sub-CPU ao acessar o disco"
#define OPTION_VAL_1_PT_BR "Executa ambas as CPUs ao acessar o disco"
#define OPTION_VAL_2_PT_BR "Sempre executa ambas as CPUs"
#define Q88_CPU_CLOCK_LABEL_PT_BR "Velocidade da CPU"
#define Q88_CPU_CLOCK_INFO_0_PT_BR "Recomendado: 4MHz ou 8MHz. Alguns aplicativos podem ser executados muito rápido com uma CPU de 8MHz."
#define OPTION_VAL_4_PT_BR NULL
#define OPTION_VAL_8_PT_BR NULL
#define OPTION_VAL_16_PT_BR NULL
#define OPTION_VAL_32_PT_BR NULL
#define OPTION_VAL_64_PT_BR NULL
#define OPTION_VAL_1_O2_PT_BR NULL
#define OPTION_VAL_2_O2_PT_BR NULL
#define Q88_SOUND_BOARD_LABEL_PT_BR "Placa de som"
#define Q88_SOUND_BOARD_INFO_0_PT_BR "Recomendado: OPNA. Alguns softwares podem ter um som alterado ao utilizar o hardware OPN."
#define OPTION_VAL_OPN_PT_BR NULL
#define OPTION_VAL_OPNA_PT_BR NULL
#define Q88_USE_FDC_WAIT_LABEL_PT_BR "Esperar o FDC"
#define Q88_USE_FDC_WAIT_INFO_0_PT_BR "Recomendado: Ligar. Melhora a sincronização da E/S com a unidade de disquetes."
#define Q88_PCG_8100_LABEL_PT_BR "Usar PCG-8100"
#define Q88_PCG_8100_INFO_0_PT_BR "Recomendado: Desligar. Pode ser necessário para alguns softwares do PC-8000."
#define Q88_SAVE_TO_DISK_IMAGE_LABEL_PT_BR "Salvar uma imagem de disco"
#define Q88_SAVE_TO_DISK_IMAGE_INFO_0_PT_BR "Recomendado: Desligar. Altera o método preferido de salvar do núcleo.\n\- Desligar: Os dados salvos em disquetes serão armazenados em um arquivo separado no diretório de salvamento da interface.\n\- Ligar: Os dados serão escritos diretamente no(s) arquivo(s) de disco carregado(s). Não funcionará com conteúdo compactado."
#define Q88_RUMBLE_LABEL_PT_BR "Vibrar o controle ao acessar o disco"
#define Q88_RUMBLE_INFO_0_PT_BR "Recomendado: N/D. Imita os sons de leitura na unidade de disquete usando a vibração do controle."
#define Q88_SCREEN_SIZE_LABEL_PT_BR "Tamanho da tela"
#define Q88_SCREEN_SIZE_INFO_0_PT_BR "Recomendado: Metade. Permite que o núcleo dimensione a imagem. Recomendado para a tela do PSP."
#define Q88_SCREEN_SIZE_INFO_1_PT_BR "Recomendado: Metade. Permite que o núcleo dimensione a imagem. Recomendado para a tela do Nintendo 3DS."
#define Q88_SCREEN_SIZE_INFO_2_PT_BR "Recomendado: Completa. Permite que o núcleo dimensione a imagem. Recomendado apenas para exibição de alturas inferiores a 400."
#define OPTION_VAL_FULL_PT_BR "Completa (640x400)"
#define OPTION_VAL_HALF_PT_BR "Metade (320x200)"

struct retro_core_option_v2_category option_cats_pt_br[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_pt_br[] = {
   { 
      "q88_basic_mode", 
      Q88_BASIC_MODE_LABEL_PT_BR,
      NULL, 
      Q88_BASIC_MODE_INFO_0_PT_BR,
      NULL,
      NULL,
      {
         { "N88 V2",  OPTION_VAL_N88_V2_PT_BR },
         { "N88 V1H", OPTION_VAL_N88_V1H_PT_BR },
         { "N88 V1S", OPTION_VAL_N88_V1S_PT_BR },
         { "N",       OPTION_VAL_N_PT_BR },
         { NULL, NULL }
      },
      "N88 V2"
   },

   { 
      "q88_sub_cpu_mode",
      Q88_SUB_CPU_MODE_LABEL_PT_BR,
      NULL,
      Q88_SUB_CPU_MODE_INFO_0_PT_BR,
      NULL,
      NULL,
      {
         { "0", OPTION_VAL_0_PT_BR},
         { "1", OPTION_VAL_1_PT_BR},
         { "2", OPTION_VAL_2_PT_BR},
         { NULL, NULL },
      },
      "0"
   },

   { 
      "q88_cpu_clock", 
      Q88_CPU_CLOCK_LABEL_PT_BR,
      NULL, 
      Q88_CPU_CLOCK_INFO_0_PT_BR,
      NULL,
      NULL,
      {
         { "4",  OPTION_VAL_4_PT_BR },
         { "8",  OPTION_VAL_8_PT_BR },
         { "16", OPTION_VAL_16_PT_BR },
         { "32", OPTION_VAL_32_PT_BR },
         { "64", OPTION_VAL_64_PT_BR },
         { "1",  OPTION_VAL_1_O2_PT_BR },
         { "2",  OPTION_VAL_2_O2_PT_BR },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      Q88_SOUND_BOARD_LABEL_PT_BR,
      NULL, 
      Q88_SOUND_BOARD_INFO_0_PT_BR,
      NULL,
      NULL,
      {
         { "OPN",  OPTION_VAL_OPN_PT_BR },
         { "OPNA", OPTION_VAL_OPNA_PT_BR},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      Q88_USE_FDC_WAIT_LABEL_PT_BR,
      NULL, 
      Q88_USE_FDC_WAIT_INFO_0_PT_BR,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_pcg-8100", 
      Q88_PCG_8100_LABEL_PT_BR,
      NULL, 
      Q88_PCG_8100_INFO_0_PT_BR,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   {
      "q88_save_to_disk_image", 
      Q88_SAVE_TO_DISK_IMAGE_LABEL_PT_BR,
      NULL, 
      Q88_SAVE_TO_DISK_IMAGE_INFO_0_PT_BR,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   { 
      "q88_rumble", 
      Q88_RUMBLE_LABEL_PT_BR,
      NULL, 
      Q88_RUMBLE_INFO_0_PT_BR,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_screen_size", 
      Q88_SCREEN_SIZE_LABEL_PT_BR,
      NULL, 
#if defined (PSP)
      Q88_SCREEN_SIZE_INFO_0_PT_BR,
#elif defined (_3DS)
      Q88_SCREEN_SIZE_INFO_1_PT_BR,
#else
      Q88_SCREEN_SIZE_INFO_2_PT_BR,
#endif
      NULL,
      NULL,
      {
         { "full",  OPTION_VAL_FULL_PT_BR },
         { "half",  OPTION_VAL_HALF_PT_BR },
         { NULL, NULL }
      },
#if defined (PSP) || defined (_3DS)
      "half"
#else
      "full"
#endif
   },

   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_pt_br = {
   option_cats_pt_br,
   option_defs_pt_br
};

/* RETRO_LANGUAGE_PT_PT */

#define Q88_BASIC_MODE_LABEL_PT_PT NULL
#define Q88_BASIC_MODE_INFO_0_PT_PT NULL
#define OPTION_VAL_N88_V2_PT_PT NULL
#define OPTION_VAL_N88_V1H_PT_PT NULL
#define OPTION_VAL_N88_V1S_PT_PT NULL
#define OPTION_VAL_N_PT_PT NULL
#define Q88_SUB_CPU_MODE_LABEL_PT_PT NULL
#define Q88_SUB_CPU_MODE_INFO_0_PT_PT NULL
#define OPTION_VAL_0_PT_PT NULL
#define OPTION_VAL_1_PT_PT NULL
#define OPTION_VAL_2_PT_PT NULL
#define Q88_CPU_CLOCK_LABEL_PT_PT NULL
#define Q88_CPU_CLOCK_INFO_0_PT_PT NULL
#define OPTION_VAL_4_PT_PT NULL
#define OPTION_VAL_8_PT_PT NULL
#define OPTION_VAL_16_PT_PT NULL
#define OPTION_VAL_32_PT_PT NULL
#define OPTION_VAL_64_PT_PT NULL
#define OPTION_VAL_1_O2_PT_PT NULL
#define OPTION_VAL_2_O2_PT_PT NULL
#define Q88_SOUND_BOARD_LABEL_PT_PT NULL
#define Q88_SOUND_BOARD_INFO_0_PT_PT NULL
#define OPTION_VAL_OPN_PT_PT NULL
#define OPTION_VAL_OPNA_PT_PT NULL
#define Q88_USE_FDC_WAIT_LABEL_PT_PT NULL
#define Q88_USE_FDC_WAIT_INFO_0_PT_PT NULL
#define Q88_PCG_8100_LABEL_PT_PT NULL
#define Q88_PCG_8100_INFO_0_PT_PT NULL
#define Q88_SAVE_TO_DISK_IMAGE_LABEL_PT_PT NULL
#define Q88_SAVE_TO_DISK_IMAGE_INFO_0_PT_PT NULL
#define Q88_RUMBLE_LABEL_PT_PT NULL
#define Q88_RUMBLE_INFO_0_PT_PT NULL
#define Q88_SCREEN_SIZE_LABEL_PT_PT NULL
#define Q88_SCREEN_SIZE_INFO_0_PT_PT NULL
#define Q88_SCREEN_SIZE_INFO_1_PT_PT NULL
#define Q88_SCREEN_SIZE_INFO_2_PT_PT NULL
#define OPTION_VAL_FULL_PT_PT NULL
#define OPTION_VAL_HALF_PT_PT NULL

struct retro_core_option_v2_category option_cats_pt_pt[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_pt_pt[] = {
   { 
      "q88_basic_mode", 
      Q88_BASIC_MODE_LABEL_PT_PT,
      NULL, 
      Q88_BASIC_MODE_INFO_0_PT_PT,
      NULL,
      NULL,
      {
         { "N88 V2",  OPTION_VAL_N88_V2_PT_PT },
         { "N88 V1H", OPTION_VAL_N88_V1H_PT_PT },
         { "N88 V1S", OPTION_VAL_N88_V1S_PT_PT },
         { "N",       OPTION_VAL_N_PT_PT },
         { NULL, NULL }
      },
      "N88 V2"
   },

   { 
      "q88_sub_cpu_mode",
      Q88_SUB_CPU_MODE_LABEL_PT_PT,
      NULL,
      Q88_SUB_CPU_MODE_INFO_0_PT_PT,
      NULL,
      NULL,
      {
         { "0", OPTION_VAL_0_PT_PT},
         { "1", OPTION_VAL_1_PT_PT},
         { "2", OPTION_VAL_2_PT_PT},
         { NULL, NULL },
      },
      "0"
   },

   { 
      "q88_cpu_clock", 
      Q88_CPU_CLOCK_LABEL_PT_PT,
      NULL, 
      Q88_CPU_CLOCK_INFO_0_PT_PT,
      NULL,
      NULL,
      {
         { "4",  OPTION_VAL_4_PT_PT },
         { "8",  OPTION_VAL_8_PT_PT },
         { "16", OPTION_VAL_16_PT_PT },
         { "32", OPTION_VAL_32_PT_PT },
         { "64", OPTION_VAL_64_PT_PT },
         { "1",  OPTION_VAL_1_O2_PT_PT },
         { "2",  OPTION_VAL_2_O2_PT_PT },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      Q88_SOUND_BOARD_LABEL_PT_PT,
      NULL, 
      Q88_SOUND_BOARD_INFO_0_PT_PT,
      NULL,
      NULL,
      {
         { "OPN",  OPTION_VAL_OPN_PT_PT },
         { "OPNA", OPTION_VAL_OPNA_PT_PT},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      Q88_USE_FDC_WAIT_LABEL_PT_PT,
      NULL, 
      Q88_USE_FDC_WAIT_INFO_0_PT_PT,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_pcg-8100", 
      Q88_PCG_8100_LABEL_PT_PT,
      NULL, 
      Q88_PCG_8100_INFO_0_PT_PT,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   {
      "q88_save_to_disk_image", 
      Q88_SAVE_TO_DISK_IMAGE_LABEL_PT_PT,
      NULL, 
      Q88_SAVE_TO_DISK_IMAGE_INFO_0_PT_PT,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   { 
      "q88_rumble", 
      Q88_RUMBLE_LABEL_PT_PT,
      NULL, 
      Q88_RUMBLE_INFO_0_PT_PT,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_screen_size", 
      Q88_SCREEN_SIZE_LABEL_PT_PT,
      NULL, 
#if defined (PSP)
      Q88_SCREEN_SIZE_INFO_0_PT_PT,
#elif defined (_3DS)
      Q88_SCREEN_SIZE_INFO_1_PT_PT,
#else
      Q88_SCREEN_SIZE_INFO_2_PT_PT,
#endif
      NULL,
      NULL,
      {
         { "full",  OPTION_VAL_FULL_PT_PT },
         { "half",  OPTION_VAL_HALF_PT_PT },
         { NULL, NULL }
      },
#if defined (PSP) || defined (_3DS)
      "half"
#else
      "full"
#endif
   },

   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_pt_pt = {
   option_cats_pt_pt,
   option_defs_pt_pt
};

/* RETRO_LANGUAGE_RO */

#define Q88_BASIC_MODE_LABEL_RO NULL
#define Q88_BASIC_MODE_INFO_0_RO NULL
#define OPTION_VAL_N88_V2_RO NULL
#define OPTION_VAL_N88_V1H_RO NULL
#define OPTION_VAL_N88_V1S_RO NULL
#define OPTION_VAL_N_RO NULL
#define Q88_SUB_CPU_MODE_LABEL_RO NULL
#define Q88_SUB_CPU_MODE_INFO_0_RO NULL
#define OPTION_VAL_0_RO NULL
#define OPTION_VAL_1_RO NULL
#define OPTION_VAL_2_RO NULL
#define Q88_CPU_CLOCK_LABEL_RO NULL
#define Q88_CPU_CLOCK_INFO_0_RO NULL
#define OPTION_VAL_4_RO NULL
#define OPTION_VAL_8_RO NULL
#define OPTION_VAL_16_RO NULL
#define OPTION_VAL_32_RO NULL
#define OPTION_VAL_64_RO NULL
#define OPTION_VAL_1_O2_RO NULL
#define OPTION_VAL_2_O2_RO NULL
#define Q88_SOUND_BOARD_LABEL_RO NULL
#define Q88_SOUND_BOARD_INFO_0_RO NULL
#define OPTION_VAL_OPN_RO NULL
#define OPTION_VAL_OPNA_RO NULL
#define Q88_USE_FDC_WAIT_LABEL_RO NULL
#define Q88_USE_FDC_WAIT_INFO_0_RO NULL
#define Q88_PCG_8100_LABEL_RO NULL
#define Q88_PCG_8100_INFO_0_RO NULL
#define Q88_SAVE_TO_DISK_IMAGE_LABEL_RO NULL
#define Q88_SAVE_TO_DISK_IMAGE_INFO_0_RO NULL
#define Q88_RUMBLE_LABEL_RO NULL
#define Q88_RUMBLE_INFO_0_RO NULL
#define Q88_SCREEN_SIZE_LABEL_RO NULL
#define Q88_SCREEN_SIZE_INFO_0_RO NULL
#define Q88_SCREEN_SIZE_INFO_1_RO NULL
#define Q88_SCREEN_SIZE_INFO_2_RO NULL
#define OPTION_VAL_FULL_RO NULL
#define OPTION_VAL_HALF_RO NULL

struct retro_core_option_v2_category option_cats_ro[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_ro[] = {
   { 
      "q88_basic_mode", 
      Q88_BASIC_MODE_LABEL_RO,
      NULL, 
      Q88_BASIC_MODE_INFO_0_RO,
      NULL,
      NULL,
      {
         { "N88 V2",  OPTION_VAL_N88_V2_RO },
         { "N88 V1H", OPTION_VAL_N88_V1H_RO },
         { "N88 V1S", OPTION_VAL_N88_V1S_RO },
         { "N",       OPTION_VAL_N_RO },
         { NULL, NULL }
      },
      "N88 V2"
   },

   { 
      "q88_sub_cpu_mode",
      Q88_SUB_CPU_MODE_LABEL_RO,
      NULL,
      Q88_SUB_CPU_MODE_INFO_0_RO,
      NULL,
      NULL,
      {
         { "0", OPTION_VAL_0_RO},
         { "1", OPTION_VAL_1_RO},
         { "2", OPTION_VAL_2_RO},
         { NULL, NULL },
      },
      "0"
   },

   { 
      "q88_cpu_clock", 
      Q88_CPU_CLOCK_LABEL_RO,
      NULL, 
      Q88_CPU_CLOCK_INFO_0_RO,
      NULL,
      NULL,
      {
         { "4",  OPTION_VAL_4_RO },
         { "8",  OPTION_VAL_8_RO },
         { "16", OPTION_VAL_16_RO },
         { "32", OPTION_VAL_32_RO },
         { "64", OPTION_VAL_64_RO },
         { "1",  OPTION_VAL_1_O2_RO },
         { "2",  OPTION_VAL_2_O2_RO },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      Q88_SOUND_BOARD_LABEL_RO,
      NULL, 
      Q88_SOUND_BOARD_INFO_0_RO,
      NULL,
      NULL,
      {
         { "OPN",  OPTION_VAL_OPN_RO },
         { "OPNA", OPTION_VAL_OPNA_RO},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      Q88_USE_FDC_WAIT_LABEL_RO,
      NULL, 
      Q88_USE_FDC_WAIT_INFO_0_RO,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_pcg-8100", 
      Q88_PCG_8100_LABEL_RO,
      NULL, 
      Q88_PCG_8100_INFO_0_RO,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   {
      "q88_save_to_disk_image", 
      Q88_SAVE_TO_DISK_IMAGE_LABEL_RO,
      NULL, 
      Q88_SAVE_TO_DISK_IMAGE_INFO_0_RO,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   { 
      "q88_rumble", 
      Q88_RUMBLE_LABEL_RO,
      NULL, 
      Q88_RUMBLE_INFO_0_RO,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_screen_size", 
      Q88_SCREEN_SIZE_LABEL_RO,
      NULL, 
#if defined (PSP)
      Q88_SCREEN_SIZE_INFO_0_RO,
#elif defined (_3DS)
      Q88_SCREEN_SIZE_INFO_1_RO,
#else
      Q88_SCREEN_SIZE_INFO_2_RO,
#endif
      NULL,
      NULL,
      {
         { "full",  OPTION_VAL_FULL_RO },
         { "half",  OPTION_VAL_HALF_RO },
         { NULL, NULL }
      },
#if defined (PSP) || defined (_3DS)
      "half"
#else
      "full"
#endif
   },

   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_ro = {
   option_cats_ro,
   option_defs_ro
};

/* RETRO_LANGUAGE_RU */

#define Q88_BASIC_MODE_LABEL_RU "Режим BASIC"
#define Q88_BASIC_MODE_INFO_0_RU "Рекомендованный режим: N88-BASIC V2/V1H для программ PC-8800, N-BASIC для программ PC-8000.\n\ - Если программа PC-8800 идёт слишком быстро в режиме V2, используйте режим V1.\n\ - Файлы BIOS необходимы для режима N-BASIC. См. информацию о ядре."
#define OPTION_VAL_N88_V2_RU NULL
#define OPTION_VAL_N88_V1H_RU NULL
#define OPTION_VAL_N88_V1S_RU NULL
#define OPTION_VAL_N_RU NULL
#define Q88_SUB_CPU_MODE_LABEL_RU "Режим доп. CPU"
#define Q88_SUB_CPU_MODE_INFO_0_RU "Рекомендованный режим: запускать доп. CPU только при чтении с диска."
#define OPTION_VAL_0_RU "Запускать доп. CPU только при чтении с диска"
#define OPTION_VAL_1_RU "Запускать оба CPU при чтении с диска"
#define OPTION_VAL_2_RU "Всегда запускать оба CPU"
#define Q88_CPU_CLOCK_LABEL_RU "Частота CPU"
#define Q88_CPU_CLOCK_INFO_0_RU "Рекомендованный режим: 4 МГц или 8 МГц. Некоторые программы могут идти слишком быстро на 8 МГц."
#define OPTION_VAL_4_RU "4 МГц (NEC µPD780)"
#define OPTION_VAL_8_RU "8 МГц (NEC µPD70008)"
#define OPTION_VAL_16_RU "16 МГц (разгон)"
#define OPTION_VAL_32_RU "32 МГц (разгон)"
#define OPTION_VAL_64_RU "64 МГц (разгон)"
#define OPTION_VAL_1_O2_RU "1 МГц (замедление)"
#define OPTION_VAL_2_O2_RU "2 МГц (замедление)"
#define Q88_SOUND_BOARD_LABEL_RU "Звуковая плата"
#define Q88_SOUND_BOARD_INFO_0_RU "Рекомендованный режим: OPNA. Некоторые программы будут звучать иначе на оборудовании OPN."
#define OPTION_VAL_OPN_RU NULL
#define OPTION_VAL_OPNA_RU NULL
#define Q88_USE_FDC_WAIT_LABEL_RU NULL
#define Q88_USE_FDC_WAIT_INFO_0_RU NULL
#define Q88_PCG_8100_LABEL_RU NULL
#define Q88_PCG_8100_INFO_0_RU NULL
#define Q88_SAVE_TO_DISK_IMAGE_LABEL_RU NULL
#define Q88_SAVE_TO_DISK_IMAGE_INFO_0_RU NULL
#define Q88_RUMBLE_LABEL_RU "Вибрация при чтении диска"
#define Q88_RUMBLE_INFO_0_RU "Рекомендованный режим: Н/Д. Имитирует с помощью вибрации геймпада звук считывания контроллера гибких дисков."
#define Q88_SCREEN_SIZE_LABEL_RU "Размер экрана"
#define Q88_SCREEN_SIZE_INFO_0_RU "Рекомендованный режим: Половина. Позволяет ядру уменьшать размер изображения. Рекомендуется для экрана PSP."
#define Q88_SCREEN_SIZE_INFO_1_RU "Рекомендованный режим: Половина. Позволяет ядру уменьшать размер изображения. Рекомендуется для экрана Nintendo 3DS."
#define Q88_SCREEN_SIZE_INFO_2_RU "Рекомендованный режим: Полный. Позволяет ядру уменьшать размер изображения. Рекомендуется для экранов с высотой меньше 400."
#define OPTION_VAL_FULL_RU "Полный (640x480)"
#define OPTION_VAL_HALF_RU "Половина (320x200)"

struct retro_core_option_v2_category option_cats_ru[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_ru[] = {
   { 
      "q88_basic_mode", 
      Q88_BASIC_MODE_LABEL_RU,
      NULL, 
      Q88_BASIC_MODE_INFO_0_RU,
      NULL,
      NULL,
      {
         { "N88 V2",  OPTION_VAL_N88_V2_RU },
         { "N88 V1H", OPTION_VAL_N88_V1H_RU },
         { "N88 V1S", OPTION_VAL_N88_V1S_RU },
         { "N",       OPTION_VAL_N_RU },
         { NULL, NULL }
      },
      "N88 V2"
   },

   { 
      "q88_sub_cpu_mode",
      Q88_SUB_CPU_MODE_LABEL_RU,
      NULL,
      Q88_SUB_CPU_MODE_INFO_0_RU,
      NULL,
      NULL,
      {
         { "0", OPTION_VAL_0_RU},
         { "1", OPTION_VAL_1_RU},
         { "2", OPTION_VAL_2_RU},
         { NULL, NULL },
      },
      "0"
   },

   { 
      "q88_cpu_clock", 
      Q88_CPU_CLOCK_LABEL_RU,
      NULL, 
      Q88_CPU_CLOCK_INFO_0_RU,
      NULL,
      NULL,
      {
         { "4",  OPTION_VAL_4_RU },
         { "8",  OPTION_VAL_8_RU },
         { "16", OPTION_VAL_16_RU },
         { "32", OPTION_VAL_32_RU },
         { "64", OPTION_VAL_64_RU },
         { "1",  OPTION_VAL_1_O2_RU },
         { "2",  OPTION_VAL_2_O2_RU },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      Q88_SOUND_BOARD_LABEL_RU,
      NULL, 
      Q88_SOUND_BOARD_INFO_0_RU,
      NULL,
      NULL,
      {
         { "OPN",  OPTION_VAL_OPN_RU },
         { "OPNA", OPTION_VAL_OPNA_RU},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      Q88_USE_FDC_WAIT_LABEL_RU,
      NULL, 
      Q88_USE_FDC_WAIT_INFO_0_RU,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_pcg-8100", 
      Q88_PCG_8100_LABEL_RU,
      NULL, 
      Q88_PCG_8100_INFO_0_RU,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   {
      "q88_save_to_disk_image", 
      Q88_SAVE_TO_DISK_IMAGE_LABEL_RU,
      NULL, 
      Q88_SAVE_TO_DISK_IMAGE_INFO_0_RU,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   { 
      "q88_rumble", 
      Q88_RUMBLE_LABEL_RU,
      NULL, 
      Q88_RUMBLE_INFO_0_RU,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_screen_size", 
      Q88_SCREEN_SIZE_LABEL_RU,
      NULL, 
#if defined (PSP)
      Q88_SCREEN_SIZE_INFO_0_RU,
#elif defined (_3DS)
      Q88_SCREEN_SIZE_INFO_1_RU,
#else
      Q88_SCREEN_SIZE_INFO_2_RU,
#endif
      NULL,
      NULL,
      {
         { "full",  OPTION_VAL_FULL_RU },
         { "half",  OPTION_VAL_HALF_RU },
         { NULL, NULL }
      },
#if defined (PSP) || defined (_3DS)
      "half"
#else
      "full"
#endif
   },

   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_ru = {
   option_cats_ru,
   option_defs_ru
};

/* RETRO_LANGUAGE_SI */

#define Q88_BASIC_MODE_LABEL_SI NULL
#define Q88_BASIC_MODE_INFO_0_SI NULL
#define OPTION_VAL_N88_V2_SI NULL
#define OPTION_VAL_N88_V1H_SI NULL
#define OPTION_VAL_N88_V1S_SI NULL
#define OPTION_VAL_N_SI NULL
#define Q88_SUB_CPU_MODE_LABEL_SI NULL
#define Q88_SUB_CPU_MODE_INFO_0_SI NULL
#define OPTION_VAL_0_SI NULL
#define OPTION_VAL_1_SI NULL
#define OPTION_VAL_2_SI NULL
#define Q88_CPU_CLOCK_LABEL_SI NULL
#define Q88_CPU_CLOCK_INFO_0_SI NULL
#define OPTION_VAL_4_SI NULL
#define OPTION_VAL_8_SI NULL
#define OPTION_VAL_16_SI NULL
#define OPTION_VAL_32_SI NULL
#define OPTION_VAL_64_SI NULL
#define OPTION_VAL_1_O2_SI NULL
#define OPTION_VAL_2_O2_SI NULL
#define Q88_SOUND_BOARD_LABEL_SI NULL
#define Q88_SOUND_BOARD_INFO_0_SI NULL
#define OPTION_VAL_OPN_SI NULL
#define OPTION_VAL_OPNA_SI NULL
#define Q88_USE_FDC_WAIT_LABEL_SI NULL
#define Q88_USE_FDC_WAIT_INFO_0_SI NULL
#define Q88_PCG_8100_LABEL_SI NULL
#define Q88_PCG_8100_INFO_0_SI NULL
#define Q88_SAVE_TO_DISK_IMAGE_LABEL_SI NULL
#define Q88_SAVE_TO_DISK_IMAGE_INFO_0_SI NULL
#define Q88_RUMBLE_LABEL_SI NULL
#define Q88_RUMBLE_INFO_0_SI NULL
#define Q88_SCREEN_SIZE_LABEL_SI NULL
#define Q88_SCREEN_SIZE_INFO_0_SI NULL
#define Q88_SCREEN_SIZE_INFO_1_SI NULL
#define Q88_SCREEN_SIZE_INFO_2_SI NULL
#define OPTION_VAL_FULL_SI NULL
#define OPTION_VAL_HALF_SI NULL

struct retro_core_option_v2_category option_cats_si[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_si[] = {
   { 
      "q88_basic_mode", 
      Q88_BASIC_MODE_LABEL_SI,
      NULL, 
      Q88_BASIC_MODE_INFO_0_SI,
      NULL,
      NULL,
      {
         { "N88 V2",  OPTION_VAL_N88_V2_SI },
         { "N88 V1H", OPTION_VAL_N88_V1H_SI },
         { "N88 V1S", OPTION_VAL_N88_V1S_SI },
         { "N",       OPTION_VAL_N_SI },
         { NULL, NULL }
      },
      "N88 V2"
   },

   { 
      "q88_sub_cpu_mode",
      Q88_SUB_CPU_MODE_LABEL_SI,
      NULL,
      Q88_SUB_CPU_MODE_INFO_0_SI,
      NULL,
      NULL,
      {
         { "0", OPTION_VAL_0_SI},
         { "1", OPTION_VAL_1_SI},
         { "2", OPTION_VAL_2_SI},
         { NULL, NULL },
      },
      "0"
   },

   { 
      "q88_cpu_clock", 
      Q88_CPU_CLOCK_LABEL_SI,
      NULL, 
      Q88_CPU_CLOCK_INFO_0_SI,
      NULL,
      NULL,
      {
         { "4",  OPTION_VAL_4_SI },
         { "8",  OPTION_VAL_8_SI },
         { "16", OPTION_VAL_16_SI },
         { "32", OPTION_VAL_32_SI },
         { "64", OPTION_VAL_64_SI },
         { "1",  OPTION_VAL_1_O2_SI },
         { "2",  OPTION_VAL_2_O2_SI },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      Q88_SOUND_BOARD_LABEL_SI,
      NULL, 
      Q88_SOUND_BOARD_INFO_0_SI,
      NULL,
      NULL,
      {
         { "OPN",  OPTION_VAL_OPN_SI },
         { "OPNA", OPTION_VAL_OPNA_SI},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      Q88_USE_FDC_WAIT_LABEL_SI,
      NULL, 
      Q88_USE_FDC_WAIT_INFO_0_SI,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_pcg-8100", 
      Q88_PCG_8100_LABEL_SI,
      NULL, 
      Q88_PCG_8100_INFO_0_SI,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   {
      "q88_save_to_disk_image", 
      Q88_SAVE_TO_DISK_IMAGE_LABEL_SI,
      NULL, 
      Q88_SAVE_TO_DISK_IMAGE_INFO_0_SI,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   { 
      "q88_rumble", 
      Q88_RUMBLE_LABEL_SI,
      NULL, 
      Q88_RUMBLE_INFO_0_SI,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_screen_size", 
      Q88_SCREEN_SIZE_LABEL_SI,
      NULL, 
#if defined (PSP)
      Q88_SCREEN_SIZE_INFO_0_SI,
#elif defined (_3DS)
      Q88_SCREEN_SIZE_INFO_1_SI,
#else
      Q88_SCREEN_SIZE_INFO_2_SI,
#endif
      NULL,
      NULL,
      {
         { "full",  OPTION_VAL_FULL_SI },
         { "half",  OPTION_VAL_HALF_SI },
         { NULL, NULL }
      },
#if defined (PSP) || defined (_3DS)
      "half"
#else
      "full"
#endif
   },

   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_si = {
   option_cats_si,
   option_defs_si
};

/* RETRO_LANGUAGE_SK */

#define Q88_BASIC_MODE_LABEL_SK NULL
#define Q88_BASIC_MODE_INFO_0_SK NULL
#define OPTION_VAL_N88_V2_SK NULL
#define OPTION_VAL_N88_V1H_SK NULL
#define OPTION_VAL_N88_V1S_SK NULL
#define OPTION_VAL_N_SK NULL
#define Q88_SUB_CPU_MODE_LABEL_SK NULL
#define Q88_SUB_CPU_MODE_INFO_0_SK NULL
#define OPTION_VAL_0_SK NULL
#define OPTION_VAL_1_SK NULL
#define OPTION_VAL_2_SK NULL
#define Q88_CPU_CLOCK_LABEL_SK NULL
#define Q88_CPU_CLOCK_INFO_0_SK NULL
#define OPTION_VAL_4_SK NULL
#define OPTION_VAL_8_SK NULL
#define OPTION_VAL_16_SK NULL
#define OPTION_VAL_32_SK NULL
#define OPTION_VAL_64_SK NULL
#define OPTION_VAL_1_O2_SK NULL
#define OPTION_VAL_2_O2_SK NULL
#define Q88_SOUND_BOARD_LABEL_SK NULL
#define Q88_SOUND_BOARD_INFO_0_SK NULL
#define OPTION_VAL_OPN_SK NULL
#define OPTION_VAL_OPNA_SK NULL
#define Q88_USE_FDC_WAIT_LABEL_SK NULL
#define Q88_USE_FDC_WAIT_INFO_0_SK NULL
#define Q88_PCG_8100_LABEL_SK NULL
#define Q88_PCG_8100_INFO_0_SK NULL
#define Q88_SAVE_TO_DISK_IMAGE_LABEL_SK NULL
#define Q88_SAVE_TO_DISK_IMAGE_INFO_0_SK NULL
#define Q88_RUMBLE_LABEL_SK NULL
#define Q88_RUMBLE_INFO_0_SK NULL
#define Q88_SCREEN_SIZE_LABEL_SK NULL
#define Q88_SCREEN_SIZE_INFO_0_SK NULL
#define Q88_SCREEN_SIZE_INFO_1_SK NULL
#define Q88_SCREEN_SIZE_INFO_2_SK NULL
#define OPTION_VAL_FULL_SK NULL
#define OPTION_VAL_HALF_SK NULL

struct retro_core_option_v2_category option_cats_sk[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_sk[] = {
   { 
      "q88_basic_mode", 
      Q88_BASIC_MODE_LABEL_SK,
      NULL, 
      Q88_BASIC_MODE_INFO_0_SK,
      NULL,
      NULL,
      {
         { "N88 V2",  OPTION_VAL_N88_V2_SK },
         { "N88 V1H", OPTION_VAL_N88_V1H_SK },
         { "N88 V1S", OPTION_VAL_N88_V1S_SK },
         { "N",       OPTION_VAL_N_SK },
         { NULL, NULL }
      },
      "N88 V2"
   },

   { 
      "q88_sub_cpu_mode",
      Q88_SUB_CPU_MODE_LABEL_SK,
      NULL,
      Q88_SUB_CPU_MODE_INFO_0_SK,
      NULL,
      NULL,
      {
         { "0", OPTION_VAL_0_SK},
         { "1", OPTION_VAL_1_SK},
         { "2", OPTION_VAL_2_SK},
         { NULL, NULL },
      },
      "0"
   },

   { 
      "q88_cpu_clock", 
      Q88_CPU_CLOCK_LABEL_SK,
      NULL, 
      Q88_CPU_CLOCK_INFO_0_SK,
      NULL,
      NULL,
      {
         { "4",  OPTION_VAL_4_SK },
         { "8",  OPTION_VAL_8_SK },
         { "16", OPTION_VAL_16_SK },
         { "32", OPTION_VAL_32_SK },
         { "64", OPTION_VAL_64_SK },
         { "1",  OPTION_VAL_1_O2_SK },
         { "2",  OPTION_VAL_2_O2_SK },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      Q88_SOUND_BOARD_LABEL_SK,
      NULL, 
      Q88_SOUND_BOARD_INFO_0_SK,
      NULL,
      NULL,
      {
         { "OPN",  OPTION_VAL_OPN_SK },
         { "OPNA", OPTION_VAL_OPNA_SK},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      Q88_USE_FDC_WAIT_LABEL_SK,
      NULL, 
      Q88_USE_FDC_WAIT_INFO_0_SK,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_pcg-8100", 
      Q88_PCG_8100_LABEL_SK,
      NULL, 
      Q88_PCG_8100_INFO_0_SK,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   {
      "q88_save_to_disk_image", 
      Q88_SAVE_TO_DISK_IMAGE_LABEL_SK,
      NULL, 
      Q88_SAVE_TO_DISK_IMAGE_INFO_0_SK,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   { 
      "q88_rumble", 
      Q88_RUMBLE_LABEL_SK,
      NULL, 
      Q88_RUMBLE_INFO_0_SK,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_screen_size", 
      Q88_SCREEN_SIZE_LABEL_SK,
      NULL, 
#if defined (PSP)
      Q88_SCREEN_SIZE_INFO_0_SK,
#elif defined (_3DS)
      Q88_SCREEN_SIZE_INFO_1_SK,
#else
      Q88_SCREEN_SIZE_INFO_2_SK,
#endif
      NULL,
      NULL,
      {
         { "full",  OPTION_VAL_FULL_SK },
         { "half",  OPTION_VAL_HALF_SK },
         { NULL, NULL }
      },
#if defined (PSP) || defined (_3DS)
      "half"
#else
      "full"
#endif
   },

   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_sk = {
   option_cats_sk,
   option_defs_sk
};

/* RETRO_LANGUAGE_SR */

#define Q88_BASIC_MODE_LABEL_SR NULL
#define Q88_BASIC_MODE_INFO_0_SR NULL
#define OPTION_VAL_N88_V2_SR NULL
#define OPTION_VAL_N88_V1H_SR NULL
#define OPTION_VAL_N88_V1S_SR NULL
#define OPTION_VAL_N_SR NULL
#define Q88_SUB_CPU_MODE_LABEL_SR NULL
#define Q88_SUB_CPU_MODE_INFO_0_SR NULL
#define OPTION_VAL_0_SR NULL
#define OPTION_VAL_1_SR NULL
#define OPTION_VAL_2_SR NULL
#define Q88_CPU_CLOCK_LABEL_SR NULL
#define Q88_CPU_CLOCK_INFO_0_SR NULL
#define OPTION_VAL_4_SR NULL
#define OPTION_VAL_8_SR NULL
#define OPTION_VAL_16_SR NULL
#define OPTION_VAL_32_SR NULL
#define OPTION_VAL_64_SR NULL
#define OPTION_VAL_1_O2_SR NULL
#define OPTION_VAL_2_O2_SR NULL
#define Q88_SOUND_BOARD_LABEL_SR NULL
#define Q88_SOUND_BOARD_INFO_0_SR NULL
#define OPTION_VAL_OPN_SR NULL
#define OPTION_VAL_OPNA_SR NULL
#define Q88_USE_FDC_WAIT_LABEL_SR NULL
#define Q88_USE_FDC_WAIT_INFO_0_SR NULL
#define Q88_PCG_8100_LABEL_SR NULL
#define Q88_PCG_8100_INFO_0_SR NULL
#define Q88_SAVE_TO_DISK_IMAGE_LABEL_SR NULL
#define Q88_SAVE_TO_DISK_IMAGE_INFO_0_SR NULL
#define Q88_RUMBLE_LABEL_SR NULL
#define Q88_RUMBLE_INFO_0_SR NULL
#define Q88_SCREEN_SIZE_LABEL_SR NULL
#define Q88_SCREEN_SIZE_INFO_0_SR NULL
#define Q88_SCREEN_SIZE_INFO_1_SR NULL
#define Q88_SCREEN_SIZE_INFO_2_SR NULL
#define OPTION_VAL_FULL_SR NULL
#define OPTION_VAL_HALF_SR NULL

struct retro_core_option_v2_category option_cats_sr[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_sr[] = {
   { 
      "q88_basic_mode", 
      Q88_BASIC_MODE_LABEL_SR,
      NULL, 
      Q88_BASIC_MODE_INFO_0_SR,
      NULL,
      NULL,
      {
         { "N88 V2",  OPTION_VAL_N88_V2_SR },
         { "N88 V1H", OPTION_VAL_N88_V1H_SR },
         { "N88 V1S", OPTION_VAL_N88_V1S_SR },
         { "N",       OPTION_VAL_N_SR },
         { NULL, NULL }
      },
      "N88 V2"
   },

   { 
      "q88_sub_cpu_mode",
      Q88_SUB_CPU_MODE_LABEL_SR,
      NULL,
      Q88_SUB_CPU_MODE_INFO_0_SR,
      NULL,
      NULL,
      {
         { "0", OPTION_VAL_0_SR},
         { "1", OPTION_VAL_1_SR},
         { "2", OPTION_VAL_2_SR},
         { NULL, NULL },
      },
      "0"
   },

   { 
      "q88_cpu_clock", 
      Q88_CPU_CLOCK_LABEL_SR,
      NULL, 
      Q88_CPU_CLOCK_INFO_0_SR,
      NULL,
      NULL,
      {
         { "4",  OPTION_VAL_4_SR },
         { "8",  OPTION_VAL_8_SR },
         { "16", OPTION_VAL_16_SR },
         { "32", OPTION_VAL_32_SR },
         { "64", OPTION_VAL_64_SR },
         { "1",  OPTION_VAL_1_O2_SR },
         { "2",  OPTION_VAL_2_O2_SR },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      Q88_SOUND_BOARD_LABEL_SR,
      NULL, 
      Q88_SOUND_BOARD_INFO_0_SR,
      NULL,
      NULL,
      {
         { "OPN",  OPTION_VAL_OPN_SR },
         { "OPNA", OPTION_VAL_OPNA_SR},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      Q88_USE_FDC_WAIT_LABEL_SR,
      NULL, 
      Q88_USE_FDC_WAIT_INFO_0_SR,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_pcg-8100", 
      Q88_PCG_8100_LABEL_SR,
      NULL, 
      Q88_PCG_8100_INFO_0_SR,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   {
      "q88_save_to_disk_image", 
      Q88_SAVE_TO_DISK_IMAGE_LABEL_SR,
      NULL, 
      Q88_SAVE_TO_DISK_IMAGE_INFO_0_SR,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   { 
      "q88_rumble", 
      Q88_RUMBLE_LABEL_SR,
      NULL, 
      Q88_RUMBLE_INFO_0_SR,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_screen_size", 
      Q88_SCREEN_SIZE_LABEL_SR,
      NULL, 
#if defined (PSP)
      Q88_SCREEN_SIZE_INFO_0_SR,
#elif defined (_3DS)
      Q88_SCREEN_SIZE_INFO_1_SR,
#else
      Q88_SCREEN_SIZE_INFO_2_SR,
#endif
      NULL,
      NULL,
      {
         { "full",  OPTION_VAL_FULL_SR },
         { "half",  OPTION_VAL_HALF_SR },
         { NULL, NULL }
      },
#if defined (PSP) || defined (_3DS)
      "half"
#else
      "full"
#endif
   },

   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_sr = {
   option_cats_sr,
   option_defs_sr
};

/* RETRO_LANGUAGE_SV */

#define Q88_BASIC_MODE_LABEL_SV NULL
#define Q88_BASIC_MODE_INFO_0_SV NULL
#define OPTION_VAL_N88_V2_SV NULL
#define OPTION_VAL_N88_V1H_SV NULL
#define OPTION_VAL_N88_V1S_SV NULL
#define OPTION_VAL_N_SV NULL
#define Q88_SUB_CPU_MODE_LABEL_SV NULL
#define Q88_SUB_CPU_MODE_INFO_0_SV NULL
#define OPTION_VAL_0_SV NULL
#define OPTION_VAL_1_SV NULL
#define OPTION_VAL_2_SV NULL
#define Q88_CPU_CLOCK_LABEL_SV NULL
#define Q88_CPU_CLOCK_INFO_0_SV NULL
#define OPTION_VAL_4_SV NULL
#define OPTION_VAL_8_SV NULL
#define OPTION_VAL_16_SV NULL
#define OPTION_VAL_32_SV NULL
#define OPTION_VAL_64_SV NULL
#define OPTION_VAL_1_O2_SV NULL
#define OPTION_VAL_2_O2_SV NULL
#define Q88_SOUND_BOARD_LABEL_SV NULL
#define Q88_SOUND_BOARD_INFO_0_SV NULL
#define OPTION_VAL_OPN_SV NULL
#define OPTION_VAL_OPNA_SV NULL
#define Q88_USE_FDC_WAIT_LABEL_SV NULL
#define Q88_USE_FDC_WAIT_INFO_0_SV NULL
#define Q88_PCG_8100_LABEL_SV NULL
#define Q88_PCG_8100_INFO_0_SV NULL
#define Q88_SAVE_TO_DISK_IMAGE_LABEL_SV NULL
#define Q88_SAVE_TO_DISK_IMAGE_INFO_0_SV NULL
#define Q88_RUMBLE_LABEL_SV NULL
#define Q88_RUMBLE_INFO_0_SV NULL
#define Q88_SCREEN_SIZE_LABEL_SV NULL
#define Q88_SCREEN_SIZE_INFO_0_SV NULL
#define Q88_SCREEN_SIZE_INFO_1_SV NULL
#define Q88_SCREEN_SIZE_INFO_2_SV NULL
#define OPTION_VAL_FULL_SV NULL
#define OPTION_VAL_HALF_SV NULL

struct retro_core_option_v2_category option_cats_sv[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_sv[] = {
   { 
      "q88_basic_mode", 
      Q88_BASIC_MODE_LABEL_SV,
      NULL, 
      Q88_BASIC_MODE_INFO_0_SV,
      NULL,
      NULL,
      {
         { "N88 V2",  OPTION_VAL_N88_V2_SV },
         { "N88 V1H", OPTION_VAL_N88_V1H_SV },
         { "N88 V1S", OPTION_VAL_N88_V1S_SV },
         { "N",       OPTION_VAL_N_SV },
         { NULL, NULL }
      },
      "N88 V2"
   },

   { 
      "q88_sub_cpu_mode",
      Q88_SUB_CPU_MODE_LABEL_SV,
      NULL,
      Q88_SUB_CPU_MODE_INFO_0_SV,
      NULL,
      NULL,
      {
         { "0", OPTION_VAL_0_SV},
         { "1", OPTION_VAL_1_SV},
         { "2", OPTION_VAL_2_SV},
         { NULL, NULL },
      },
      "0"
   },

   { 
      "q88_cpu_clock", 
      Q88_CPU_CLOCK_LABEL_SV,
      NULL, 
      Q88_CPU_CLOCK_INFO_0_SV,
      NULL,
      NULL,
      {
         { "4",  OPTION_VAL_4_SV },
         { "8",  OPTION_VAL_8_SV },
         { "16", OPTION_VAL_16_SV },
         { "32", OPTION_VAL_32_SV },
         { "64", OPTION_VAL_64_SV },
         { "1",  OPTION_VAL_1_O2_SV },
         { "2",  OPTION_VAL_2_O2_SV },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      Q88_SOUND_BOARD_LABEL_SV,
      NULL, 
      Q88_SOUND_BOARD_INFO_0_SV,
      NULL,
      NULL,
      {
         { "OPN",  OPTION_VAL_OPN_SV },
         { "OPNA", OPTION_VAL_OPNA_SV},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      Q88_USE_FDC_WAIT_LABEL_SV,
      NULL, 
      Q88_USE_FDC_WAIT_INFO_0_SV,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_pcg-8100", 
      Q88_PCG_8100_LABEL_SV,
      NULL, 
      Q88_PCG_8100_INFO_0_SV,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   {
      "q88_save_to_disk_image", 
      Q88_SAVE_TO_DISK_IMAGE_LABEL_SV,
      NULL, 
      Q88_SAVE_TO_DISK_IMAGE_INFO_0_SV,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   { 
      "q88_rumble", 
      Q88_RUMBLE_LABEL_SV,
      NULL, 
      Q88_RUMBLE_INFO_0_SV,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_screen_size", 
      Q88_SCREEN_SIZE_LABEL_SV,
      NULL, 
#if defined (PSP)
      Q88_SCREEN_SIZE_INFO_0_SV,
#elif defined (_3DS)
      Q88_SCREEN_SIZE_INFO_1_SV,
#else
      Q88_SCREEN_SIZE_INFO_2_SV,
#endif
      NULL,
      NULL,
      {
         { "full",  OPTION_VAL_FULL_SV },
         { "half",  OPTION_VAL_HALF_SV },
         { NULL, NULL }
      },
#if defined (PSP) || defined (_3DS)
      "half"
#else
      "full"
#endif
   },

   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_sv = {
   option_cats_sv,
   option_defs_sv
};

/* RETRO_LANGUAGE_TR */

#define Q88_BASIC_MODE_LABEL_TR "BASIC kipi"
#define Q88_BASIC_MODE_INFO_0_TR "Önerilen: PC-8800 yazılımı için N88-BASIC V2/V1H, PC-8000 yazılımı için N-BASIC.\n\- PC-8800 yazılımı V2 kipinde çok hızlı çalışıyorsa, bir V1 kipi kullanın.\n\- N-BASIC kipi için BIOS dosyaları gereklidir. Çekirdek bilgilerine bakın."
#define OPTION_VAL_N88_V2_TR NULL
#define OPTION_VAL_N88_V1H_TR NULL
#define OPTION_VAL_N88_V1S_TR NULL
#define OPTION_VAL_N_TR NULL
#define Q88_SUB_CPU_MODE_LABEL_TR "Alt CPU kipi"
#define Q88_SUB_CPU_MODE_INFO_0_TR "Önerilen: Disket erişimi sırasında yalnızca Alt CPU'yu çalıştırın."
#define OPTION_VAL_0_TR "Disket erişimi sırasında yalnızca Alt CPU'yu çalıştırın"
#define OPTION_VAL_1_TR "Disket erişimi sırasında her iki CPU'yu da çalıştırın"
#define OPTION_VAL_2_TR "Her zaman iki CPU'yu da çalıştırın"
#define Q88_CPU_CLOCK_LABEL_TR "CPU hızı"
#define Q88_CPU_CLOCK_INFO_0_TR "Önerilen: 4MHz veya 8MHz. Bazı yazılımlar 8MHz CPU ile çok hızlı çalışabilir."
#define OPTION_VAL_4_TR NULL
#define OPTION_VAL_8_TR NULL
#define OPTION_VAL_16_TR "16 MHz (hız aşırtmalı)"
#define OPTION_VAL_32_TR "32 MHz (hız aşırtmalı)"
#define OPTION_VAL_64_TR "64 MHz (hız aşırtmalı)"
#define OPTION_VAL_1_O2_TR "1 MHz (hız düşürmeli)"
#define OPTION_VAL_2_O2_TR "2 MHz (hız düşürmeli)"
#define Q88_SOUND_BOARD_LABEL_TR "Ses kartı"
#define Q88_SOUND_BOARD_INFO_0_TR "Önerilen: OPNA. OPN donanımını kullanırken bazı yazılımlar farklı gelebilir."
#define OPTION_VAL_OPN_TR NULL
#define OPTION_VAL_OPNA_TR NULL
#define Q88_USE_FDC_WAIT_LABEL_TR "FDC-Beklemesi"
#define Q88_USE_FDC_WAIT_INFO_0_TR "Önerilen: AÇIK. Disket denetleyicisi için daha doğru IO zamanlaması sağlar."
#define Q88_PCG_8100_LABEL_TR "PCG-8100 Kullan"
#define Q88_PCG_8100_INFO_0_TR "Önerilen: KAPALI. Bazı PC-8000 yazılımları için gerekli olabilir."
#define Q88_SAVE_TO_DISK_IMAGE_LABEL_TR "Kalıbı diskete kaydet"
#define Q88_SAVE_TO_DISK_IMAGE_INFO_0_TR "Önerilen: KAPALI. Çekirdeğin tercih edilen kaydetme davranışını değiştirir.\n\- KAPALI: Disketlere yazılan veriler, ön ucun kaydetme dizininde ayrı bir dosyada saklanacaktır.\n\- AÇIK: Veriler doğrudan yüklenen disket dosyasına/dosyalarına yazılacaktır. Sıkıştırılmış içerikle çalışmaz."
#define Q88_RUMBLE_LABEL_TR "Disket erişim sesi"
#define Q88_RUMBLE_INFO_0_TR "Önerilen: Yok. Denetleyicinin gürültüsünü kullanarak disket denetleyicisindeki okuma seslerini taklit eder."
#define Q88_SCREEN_SIZE_LABEL_TR "Ekran boyutu"
#define Q88_SCREEN_SIZE_INFO_0_TR "Önerilen: Yarım. Çekirdeğin görüntüyü küçültmesine izin verir. PSP ekranı için önerilir."
#define Q88_SCREEN_SIZE_INFO_1_TR "Önerilen: Yarım. Çekirdeğin görüntüyü küçültmesine izin verir. Nintendo 3DS ekranı için önerilir."
#define Q88_SCREEN_SIZE_INFO_2_TR "Önerilen: Tam. Çekirdeğin görüntüyü küçültmesine izin verir. Yalnızca 400'ün altındaki ekran yükseklikleri için önerilir."
#define OPTION_VAL_FULL_TR "Tam (640x400)"
#define OPTION_VAL_HALF_TR "Yarım (320x200)"

struct retro_core_option_v2_category option_cats_tr[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_tr[] = {
   { 
      "q88_basic_mode", 
      Q88_BASIC_MODE_LABEL_TR,
      NULL, 
      Q88_BASIC_MODE_INFO_0_TR,
      NULL,
      NULL,
      {
         { "N88 V2",  OPTION_VAL_N88_V2_TR },
         { "N88 V1H", OPTION_VAL_N88_V1H_TR },
         { "N88 V1S", OPTION_VAL_N88_V1S_TR },
         { "N",       OPTION_VAL_N_TR },
         { NULL, NULL }
      },
      "N88 V2"
   },

   { 
      "q88_sub_cpu_mode",
      Q88_SUB_CPU_MODE_LABEL_TR,
      NULL,
      Q88_SUB_CPU_MODE_INFO_0_TR,
      NULL,
      NULL,
      {
         { "0", OPTION_VAL_0_TR},
         { "1", OPTION_VAL_1_TR},
         { "2", OPTION_VAL_2_TR},
         { NULL, NULL },
      },
      "0"
   },

   { 
      "q88_cpu_clock", 
      Q88_CPU_CLOCK_LABEL_TR,
      NULL, 
      Q88_CPU_CLOCK_INFO_0_TR,
      NULL,
      NULL,
      {
         { "4",  OPTION_VAL_4_TR },
         { "8",  OPTION_VAL_8_TR },
         { "16", OPTION_VAL_16_TR },
         { "32", OPTION_VAL_32_TR },
         { "64", OPTION_VAL_64_TR },
         { "1",  OPTION_VAL_1_O2_TR },
         { "2",  OPTION_VAL_2_O2_TR },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      Q88_SOUND_BOARD_LABEL_TR,
      NULL, 
      Q88_SOUND_BOARD_INFO_0_TR,
      NULL,
      NULL,
      {
         { "OPN",  OPTION_VAL_OPN_TR },
         { "OPNA", OPTION_VAL_OPNA_TR},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      Q88_USE_FDC_WAIT_LABEL_TR,
      NULL, 
      Q88_USE_FDC_WAIT_INFO_0_TR,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_pcg-8100", 
      Q88_PCG_8100_LABEL_TR,
      NULL, 
      Q88_PCG_8100_INFO_0_TR,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   {
      "q88_save_to_disk_image", 
      Q88_SAVE_TO_DISK_IMAGE_LABEL_TR,
      NULL, 
      Q88_SAVE_TO_DISK_IMAGE_INFO_0_TR,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   { 
      "q88_rumble", 
      Q88_RUMBLE_LABEL_TR,
      NULL, 
      Q88_RUMBLE_INFO_0_TR,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_screen_size", 
      Q88_SCREEN_SIZE_LABEL_TR,
      NULL, 
#if defined (PSP)
      Q88_SCREEN_SIZE_INFO_0_TR,
#elif defined (_3DS)
      Q88_SCREEN_SIZE_INFO_1_TR,
#else
      Q88_SCREEN_SIZE_INFO_2_TR,
#endif
      NULL,
      NULL,
      {
         { "full",  OPTION_VAL_FULL_TR },
         { "half",  OPTION_VAL_HALF_TR },
         { NULL, NULL }
      },
#if defined (PSP) || defined (_3DS)
      "half"
#else
      "full"
#endif
   },

   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_tr = {
   option_cats_tr,
   option_defs_tr
};

/* RETRO_LANGUAGE_UK */

#define Q88_BASIC_MODE_LABEL_UK NULL
#define Q88_BASIC_MODE_INFO_0_UK NULL
#define OPTION_VAL_N88_V2_UK NULL
#define OPTION_VAL_N88_V1H_UK NULL
#define OPTION_VAL_N88_V1S_UK NULL
#define OPTION_VAL_N_UK NULL
#define Q88_SUB_CPU_MODE_LABEL_UK NULL
#define Q88_SUB_CPU_MODE_INFO_0_UK NULL
#define OPTION_VAL_0_UK NULL
#define OPTION_VAL_1_UK NULL
#define OPTION_VAL_2_UK NULL
#define Q88_CPU_CLOCK_LABEL_UK NULL
#define Q88_CPU_CLOCK_INFO_0_UK NULL
#define OPTION_VAL_4_UK NULL
#define OPTION_VAL_8_UK NULL
#define OPTION_VAL_16_UK NULL
#define OPTION_VAL_32_UK NULL
#define OPTION_VAL_64_UK NULL
#define OPTION_VAL_1_O2_UK NULL
#define OPTION_VAL_2_O2_UK NULL
#define Q88_SOUND_BOARD_LABEL_UK NULL
#define Q88_SOUND_BOARD_INFO_0_UK NULL
#define OPTION_VAL_OPN_UK NULL
#define OPTION_VAL_OPNA_UK NULL
#define Q88_USE_FDC_WAIT_LABEL_UK NULL
#define Q88_USE_FDC_WAIT_INFO_0_UK NULL
#define Q88_PCG_8100_LABEL_UK NULL
#define Q88_PCG_8100_INFO_0_UK NULL
#define Q88_SAVE_TO_DISK_IMAGE_LABEL_UK NULL
#define Q88_SAVE_TO_DISK_IMAGE_INFO_0_UK NULL
#define Q88_RUMBLE_LABEL_UK NULL
#define Q88_RUMBLE_INFO_0_UK NULL
#define Q88_SCREEN_SIZE_LABEL_UK NULL
#define Q88_SCREEN_SIZE_INFO_0_UK NULL
#define Q88_SCREEN_SIZE_INFO_1_UK NULL
#define Q88_SCREEN_SIZE_INFO_2_UK NULL
#define OPTION_VAL_FULL_UK NULL
#define OPTION_VAL_HALF_UK NULL

struct retro_core_option_v2_category option_cats_uk[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_uk[] = {
   { 
      "q88_basic_mode", 
      Q88_BASIC_MODE_LABEL_UK,
      NULL, 
      Q88_BASIC_MODE_INFO_0_UK,
      NULL,
      NULL,
      {
         { "N88 V2",  OPTION_VAL_N88_V2_UK },
         { "N88 V1H", OPTION_VAL_N88_V1H_UK },
         { "N88 V1S", OPTION_VAL_N88_V1S_UK },
         { "N",       OPTION_VAL_N_UK },
         { NULL, NULL }
      },
      "N88 V2"
   },

   { 
      "q88_sub_cpu_mode",
      Q88_SUB_CPU_MODE_LABEL_UK,
      NULL,
      Q88_SUB_CPU_MODE_INFO_0_UK,
      NULL,
      NULL,
      {
         { "0", OPTION_VAL_0_UK},
         { "1", OPTION_VAL_1_UK},
         { "2", OPTION_VAL_2_UK},
         { NULL, NULL },
      },
      "0"
   },

   { 
      "q88_cpu_clock", 
      Q88_CPU_CLOCK_LABEL_UK,
      NULL, 
      Q88_CPU_CLOCK_INFO_0_UK,
      NULL,
      NULL,
      {
         { "4",  OPTION_VAL_4_UK },
         { "8",  OPTION_VAL_8_UK },
         { "16", OPTION_VAL_16_UK },
         { "32", OPTION_VAL_32_UK },
         { "64", OPTION_VAL_64_UK },
         { "1",  OPTION_VAL_1_O2_UK },
         { "2",  OPTION_VAL_2_O2_UK },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      Q88_SOUND_BOARD_LABEL_UK,
      NULL, 
      Q88_SOUND_BOARD_INFO_0_UK,
      NULL,
      NULL,
      {
         { "OPN",  OPTION_VAL_OPN_UK },
         { "OPNA", OPTION_VAL_OPNA_UK},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      Q88_USE_FDC_WAIT_LABEL_UK,
      NULL, 
      Q88_USE_FDC_WAIT_INFO_0_UK,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_pcg-8100", 
      Q88_PCG_8100_LABEL_UK,
      NULL, 
      Q88_PCG_8100_INFO_0_UK,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   {
      "q88_save_to_disk_image", 
      Q88_SAVE_TO_DISK_IMAGE_LABEL_UK,
      NULL, 
      Q88_SAVE_TO_DISK_IMAGE_INFO_0_UK,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   { 
      "q88_rumble", 
      Q88_RUMBLE_LABEL_UK,
      NULL, 
      Q88_RUMBLE_INFO_0_UK,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_screen_size", 
      Q88_SCREEN_SIZE_LABEL_UK,
      NULL, 
#if defined (PSP)
      Q88_SCREEN_SIZE_INFO_0_UK,
#elif defined (_3DS)
      Q88_SCREEN_SIZE_INFO_1_UK,
#else
      Q88_SCREEN_SIZE_INFO_2_UK,
#endif
      NULL,
      NULL,
      {
         { "full",  OPTION_VAL_FULL_UK },
         { "half",  OPTION_VAL_HALF_UK },
         { NULL, NULL }
      },
#if defined (PSP) || defined (_3DS)
      "half"
#else
      "full"
#endif
   },

   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_uk = {
   option_cats_uk,
   option_defs_uk
};

/* RETRO_LANGUAGE_VN */

#define Q88_BASIC_MODE_LABEL_VN NULL
#define Q88_BASIC_MODE_INFO_0_VN NULL
#define OPTION_VAL_N88_V2_VN NULL
#define OPTION_VAL_N88_V1H_VN NULL
#define OPTION_VAL_N88_V1S_VN NULL
#define OPTION_VAL_N_VN NULL
#define Q88_SUB_CPU_MODE_LABEL_VN NULL
#define Q88_SUB_CPU_MODE_INFO_0_VN NULL
#define OPTION_VAL_0_VN NULL
#define OPTION_VAL_1_VN NULL
#define OPTION_VAL_2_VN NULL
#define Q88_CPU_CLOCK_LABEL_VN NULL
#define Q88_CPU_CLOCK_INFO_0_VN NULL
#define OPTION_VAL_4_VN NULL
#define OPTION_VAL_8_VN NULL
#define OPTION_VAL_16_VN NULL
#define OPTION_VAL_32_VN NULL
#define OPTION_VAL_64_VN NULL
#define OPTION_VAL_1_O2_VN NULL
#define OPTION_VAL_2_O2_VN NULL
#define Q88_SOUND_BOARD_LABEL_VN NULL
#define Q88_SOUND_BOARD_INFO_0_VN NULL
#define OPTION_VAL_OPN_VN NULL
#define OPTION_VAL_OPNA_VN NULL
#define Q88_USE_FDC_WAIT_LABEL_VN NULL
#define Q88_USE_FDC_WAIT_INFO_0_VN NULL
#define Q88_PCG_8100_LABEL_VN NULL
#define Q88_PCG_8100_INFO_0_VN NULL
#define Q88_SAVE_TO_DISK_IMAGE_LABEL_VN NULL
#define Q88_SAVE_TO_DISK_IMAGE_INFO_0_VN NULL
#define Q88_RUMBLE_LABEL_VN NULL
#define Q88_RUMBLE_INFO_0_VN NULL
#define Q88_SCREEN_SIZE_LABEL_VN NULL
#define Q88_SCREEN_SIZE_INFO_0_VN NULL
#define Q88_SCREEN_SIZE_INFO_1_VN NULL
#define Q88_SCREEN_SIZE_INFO_2_VN NULL
#define OPTION_VAL_FULL_VN NULL
#define OPTION_VAL_HALF_VN NULL

struct retro_core_option_v2_category option_cats_vn[] = {
   { NULL, NULL, NULL },
};
struct retro_core_option_v2_definition option_defs_vn[] = {
   { 
      "q88_basic_mode", 
      Q88_BASIC_MODE_LABEL_VN,
      NULL, 
      Q88_BASIC_MODE_INFO_0_VN,
      NULL,
      NULL,
      {
         { "N88 V2",  OPTION_VAL_N88_V2_VN },
         { "N88 V1H", OPTION_VAL_N88_V1H_VN },
         { "N88 V1S", OPTION_VAL_N88_V1S_VN },
         { "N",       OPTION_VAL_N_VN },
         { NULL, NULL }
      },
      "N88 V2"
   },

   { 
      "q88_sub_cpu_mode",
      Q88_SUB_CPU_MODE_LABEL_VN,
      NULL,
      Q88_SUB_CPU_MODE_INFO_0_VN,
      NULL,
      NULL,
      {
         { "0", OPTION_VAL_0_VN},
         { "1", OPTION_VAL_1_VN},
         { "2", OPTION_VAL_2_VN},
         { NULL, NULL },
      },
      "0"
   },

   { 
      "q88_cpu_clock", 
      Q88_CPU_CLOCK_LABEL_VN,
      NULL, 
      Q88_CPU_CLOCK_INFO_0_VN,
      NULL,
      NULL,
      {
         { "4",  OPTION_VAL_4_VN },
         { "8",  OPTION_VAL_8_VN },
         { "16", OPTION_VAL_16_VN },
         { "32", OPTION_VAL_32_VN },
         { "64", OPTION_VAL_64_VN },
         { "1",  OPTION_VAL_1_O2_VN },
         { "2",  OPTION_VAL_2_O2_VN },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      Q88_SOUND_BOARD_LABEL_VN,
      NULL, 
      Q88_SOUND_BOARD_INFO_0_VN,
      NULL,
      NULL,
      {
         { "OPN",  OPTION_VAL_OPN_VN },
         { "OPNA", OPTION_VAL_OPNA_VN},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      Q88_USE_FDC_WAIT_LABEL_VN,
      NULL, 
      Q88_USE_FDC_WAIT_INFO_0_VN,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_pcg-8100", 
      Q88_PCG_8100_LABEL_VN,
      NULL, 
      Q88_PCG_8100_INFO_0_VN,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   {
      "q88_save_to_disk_image", 
      Q88_SAVE_TO_DISK_IMAGE_LABEL_VN,
      NULL, 
      Q88_SAVE_TO_DISK_IMAGE_INFO_0_VN,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "disabled"
   },

   { 
      "q88_rumble", 
      Q88_RUMBLE_LABEL_VN,
      NULL, 
      Q88_RUMBLE_INFO_0_VN,
      NULL,
      NULL,
      {
         { "enabled",  "enabled" },
         { "disabled", "disabled" },
         { NULL, NULL }
      },
      "enabled"
   },

   { 
      "q88_screen_size", 
      Q88_SCREEN_SIZE_LABEL_VN,
      NULL, 
#if defined (PSP)
      Q88_SCREEN_SIZE_INFO_0_VN,
#elif defined (_3DS)
      Q88_SCREEN_SIZE_INFO_1_VN,
#else
      Q88_SCREEN_SIZE_INFO_2_VN,
#endif
      NULL,
      NULL,
      {
         { "full",  OPTION_VAL_FULL_VN },
         { "half",  OPTION_VAL_HALF_VN },
         { NULL, NULL }
      },
#if defined (PSP) || defined (_3DS)
      "half"
#else
      "full"
#endif
   },

   { NULL, NULL, NULL, NULL, NULL, NULL, {{0}}, NULL },
};
struct retro_core_options_v2 options_vn = {
   option_cats_vn,
   option_defs_vn
};


#ifdef __cplusplus
}
#endif

#endif