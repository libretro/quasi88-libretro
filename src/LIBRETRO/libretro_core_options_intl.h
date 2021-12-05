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

/* RETRO_LANGUAGE_JAPANESE */


struct retro_core_option_v2_category option_cats_ja[] = {
   { NULL, NULL, NULL },
};

struct retro_core_option_v2_definition option_defs_ja[] = {
   { 
      "q88_basic_mode", 
      "BASICモード",
      NULL, 
      "推奨：PC-8800シリーズソフトウェアの場合はN88 V2 / V1H、PC-8000シリーズソフトウェアの場合は N。", 
      NULL,
      NULL,
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
      "q88_sub_cpu_mode",
      "Sub-CPU駆動",
      NULL,
      "推奨：ディスク処理中、Sub-CPUのみ駆動させる",
      NULL,
      NULL,
      {
         { "0", "ディスク処理中、Sub-CPUのみ駆動させる"},
         { "1", "ディスク処理中、両CPUを駆動させる"},
         { "2", "常時、両CPUを駆動させる"},
         { NULL, NULL },
      },
      "0"
   },

   { 
      "q88_cpu_clock", 
      "CPU クロック",
      NULL, 
      "推奨：4MHzまたは8MHz。 一部のソフトウェアは、8MHz CPUでは高速に実行される場合があります。",
      NULL,
      NULL,
      {
         { "4",  "4 MHz (NEC µPD780)" },
         { "8",  "8 MHz (NEC µPD70008)" },
         { "16", "16 MHz (オーバークロック)" },
         { "32", "32 MHz (オーバークロック)" },
         { "64", "64 MHz (オーバークロック)" },
         { "1",  "1 MHz (アンダークロック)" },
         { "2",  "2 MHz (アンダークロック)" },
         { NULL, NULL }
      },
      "4"
   },

   { 
      "q88_sound_board", 
      "サウンドボード",
      NULL, 
      "推奨：OPNA。 OPNハードウェアを使用すると、一部のソフトウェアのサウンドが異なります。",
      NULL,
      NULL,
      {
         { "OPN",  "OPN (Yamaha YM2203)" },
         { "OPNA", "OPNA (Yamaha YM2608)"},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      "FDCウエイト",
      NULL, 
      "推奨：ON。 FDCの処理にウエイトをいれます。FDCの処理速度に依存する アプリケーションの場合、動くようになる可能性があります。",
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
      "PCG-8100",
      NULL, 
      "推奨：OFF。 一部のPC-8000シリーズソフトウェアに必要な場合があります。 PCG-8100 のサウンドには対応していません。",
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
      "ディスクイメージに保存",
      NULL, 
      "推奨：OFF。 コアが挿入されたフロッピーディスクにデータを書き換えることを許可します。 解凍されたコンテンツでのみ動作します。",
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
      "ディスクアクセスでランブル",
      NULL, 
      "推奨：N/A。 コントローラーのランブルを使用して、FDCの読み取り音を模倣します。",
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
      "画面サイズ",
      NULL, 
#if defined (PSP)
      "推奨：半分。 コアがイメージを縮小できるようにします。 PSP画面に推奨されます。",
#elif defined (_3DS)
      "推奨：半分。 コアがイメージを縮小できるようにします。 Nintendo 3DS画面に推奨されます。",
#else
      "推奨：フル。 コアがイメージを縮小できるようにします。 ディスプレイの高さが400未満の場合にのみ推奨されます。",
#endif
      NULL,
      NULL,
      {
         { "full",  "フル（640x400）" },
         { "half",  "半分 (320x200)" },
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

/* RETRO_LANGUAGE_SPANISH */

/* RETRO_LANGUAGE_GERMAN */

/* RETRO_LANGUAGE_ITALIAN */

/* RETRO_LANGUAGE_DUTCH */

/* RETRO_LANGUAGE_PORTUGUESE_BRAZIL */

/* RETRO_LANGUAGE_PORTUGUESE_PORTUGAL */

/* RETRO_LANGUAGE_RUSSIAN */

/* RETRO_LANGUAGE_KOREAN */

/* RETRO_LANGUAGE_CHINESE_TRADITIONAL */

/* RETRO_LANGUAGE_CHINESE_SIMPLIFIED */

/* RETRO_LANGUAGE_ESPERANTO */

/* RETRO_LANGUAGE_POLISH */

/* RETRO_LANGUAGE_VIETNAMESE */

/* RETRO_LANGUAGE_ARABIC */

/* RETRO_LANGUAGE_GREEK */

/* RETRO_LANGUAGE_TURKISH */

/* RETRO_LANGUAGE_SLOVAK */

/* RETRO_LANGUAGE_PERSIAN */

/* RETRO_LANGUAGE_HEBREW */

/* RETRO_LANGUAGE_ASTURIAN */

/* RETRO_LANGUAGE_FINNISH */

#ifdef __cplusplus
}
#endif

#endif
