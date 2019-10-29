#include <libretro.h>

const struct retro_variable variables_old[] = 
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

struct retro_core_option_definition variables_english[] = 
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
      "Recommended: N/A. Imitates the read sounds on the floppy disk controller using the controller's rumble.",
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

struct retro_core_option_definition variables_japanese[] = 
{
   { 
      "q88_basic_mode", 
      "BASICモード", 
      "推奨：PC-8800シリーズソフトウェアの場合はN88 V2 / V1H、PC-8000シリーズソフトウェアの場合は N。", 
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
      "推奨：4MHzまたは8MHz。 一部のソフトウェアは、8MHz CPUでは高速に実行される場合があります。",
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
      "推奨：OPNA。 OPNハードウェアを使用すると、一部のソフトウェアのサウンドが異なります。",
      {
         { "OPN",  "OPN (Yamaha YM2203)" },
         { "OPNA", "OPNA (Yamaha YM2608)"},
         { NULL, NULL}
      },
      "OPNA"
   },
         
   { 
      "q88_use_fdc_wait", 
      "FDC-Wait", 
      "推奨：ON。 FDCの処理にウエイトをいれます。FDCの処理速度に依存する アプリケーションの場合、動くようになる可能性があります。",
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
      "推奨：OFF。 一部のPC-8000シリーズソフトウェアに必要な場合があります。 PCG-8100 のサウンドには対応していません。",
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
      "推奨：OFF。 コアが挿入されたフロッピーディスクにデータを書き換えることを許可します。 解凍されたコンテンツでのみ動作します。",
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
      "推奨：N/A。 コントローラーのランブルを使用して、FDCの読み取り音を模倣します。",
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
#if defined (PSP)
      "推奨：半分。 コアがイメージを縮小できるようにします。 PSP画面に推奨されます。",
#elif defined (_3DS)
      "推奨：半分。 コアがイメージを縮小できるようにします。 Nintendo 3DS画面に推奨されます。",
#else
      "推奨：フル。 コアがイメージを縮小できるようにします。 ディスプレイの高さが400未満の場合にのみ推奨されます。",
#endif
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

   { NULL, NULL, NULL, {{0}}, NULL }
};

void *variables[RETRO_LANGUAGE_LAST] =
{
   &variables_english,
   &variables_japanese,
   NULL,
   NULL,
   NULL,
   NULL,
   NULL,
   NULL,
   NULL,
   NULL,
   NULL,
   NULL,
   NULL,
   NULL,
   NULL,
   NULL,
   NULL,
   NULL
};
