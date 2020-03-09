#include <stdint.h>

#include "keyboard.h"
#include "libretro.h"

#define REMAP_MAX 32

/* Help keep the remap definitions a little neater */
#define BTN(a) RETRO_DEVICE_ID_JOYPAD_##a
#define KEY(a) KEY88_##a

typedef struct retro_label_t
{
   uint8_t     player;
   uint16_t    button;
   uint16_t    key;
   const char *name[16];
} retro_label_t;

typedef struct retro_remap_t
{
   const char *title; 
   uint32_t checksums[16];
   retro_label_t labels[16];
} retro_remap_t;

const retro_remap_t remaps[] = 
{
   {
      "Archon (BPS)",
      { 
         0x56a613a8, 
         0xfe0bbfce, 

         0 
      },
      {
         { 0, BTN(UP),    KEY(KP_8),  { "P1 Up" }},
         { 0, BTN(DOWN),  KEY(KP_2),  { "P1 Down" }},
         { 0, BTN(LEFT),  KEY(KP_4),  { "P1 Left" }},
         { 0, BTN(RIGHT), KEY(KP_6),  { "P1 Right" }},
         { 0, BTN(A),     KEY(SPACE), { "P1 Fire / Confirm" }},

         { 1, BTN(UP),    KEY(W),     { "P2 Up" }},
         { 1, BTN(DOWN),  KEY(X),     { "P2 Down" }},
         { 1, BTN(LEFT),  KEY(A),     { "P2 Left" }},
         { 1, BTN(RIGHT), KEY(D),     { "P2 Right" }},
         { 1, BTN(A),     KEY(1),     { "P2 Fire / Confirm" }},

         { 0, BTN(START), KEY(F10),   { "Return to menu", "メニューに戻る" }},

         { 0, 0, 0, NULL }
      }
   },
   {
      "Popful Mail (Falcom)",
      {
         0xfa87bfbd, /* Popful Mail (Data disk 1) */
         0x765b8511, /* Popful Mail (Data disk 2) */
         0x8c4b7e83, /* Popful Mail (Data disk 3) */
         0x7130994e, /* Popful Mail (demo) (Disk 1) */
         0xe3091d85, /* Popful Mail (demo) (Disk 2) */
         0x237fca26, /* Popful Mail (Opening disk) [Alt 1] */
         0xffa80931, /* Popful Mail (Opening disk) */
         0xac02a94d, /* Popful Mail (Program disk) [Alt 1] */
         0xdce65a7b, /* Popful Mail (Program disk) [Alt 2] */
         0xe05ac1bb, /* Popful Mail (Program disk) [Alt 3] */
         0x37762923, /* Popful Mail (Program disk) [Alt 4] */
         0x14c4ace0, /* Popful Mail (Program disk) */
         0x7a5c2540, /* Popful Mail (Visual disk) */

         0
      },
      {
         { 0, BTN(A),     KEY(SPACE),  { "Jump / Confirm", "ジャンプする / エントリ" }},
         { 0, BTN(B),     KEY(SHIFTL), { "Shoot / Cancel", "ショット攻撃 / キャンセル" }},
         { 0, BTN(START), KEY(F6),     { "Open main menu", "メニューを表示する" }},
         { 0, BTN(X),     KEY(F7),     { "View inventory", "アイテム画面を開く" }},
         { 0, BTN(Y),     KEY(F8),     { "View status",    "アイテム画面を開く" }},
         { 0, BTN(L2),    KEY(F10),    { "Open load menu", "ロード画面を開く"}},
         { 0, BTN(R2),    KEY(F9),     { "Open save menu", "セーブ画面を開く"}},
         { 0, BTN(UP),    KEY(KP_8),   { "Up",    "上" }},
         { 0, BTN(DOWN),  KEY(KP_2),   { "Down",  "下" }},
         { 0, BTN(LEFT),  KEY(KP_4),   { "Left",  "左" }},
         { 0, BTN(RIGHT), KEY(KP_6),   { "Right", "右" }},

         { 0, 0, 0, NULL }
      }
   },
   {
      "Ys (Falcom)",
      {
         0x638acbd6, /* Ys (Disk A) */
         0xa60c018f, /* Ys (Disk A) [Alt 1] */
         0x3b6d9ca1, /* Ys (Disk B) */
         0x0be6443d, /* Ys (Disk B) [Alt 1] */
         0x9bd5d527, /* Ys [Set 1] (Disk A) */
         0xcf222045, /* Ys [Set 1] (Disk B) */
         0x2d7b5ee4, /* Ys (User disk) */
         0xed30beb8, /* Ys (User disk) [Alt 1] */
         0x2267a2a3, /* Ys (User disk) [Alt 2] */
         0xf0c21b38, /* Ys (User disk) [Alt 3] */
         0x174995b3, /* Ys (Demo) */

         0
      },
      {
         { 0, BTN(X),     KEY(I),       { "View inventory",      "インベントリー" }},
         { 0, BTN(Y),     KEY(S),       { "View status",         "ステータス"}},
         { 0, BTN(L2),    KEY(F6),      { "Load game",           "ロード"}},
         { 0, BTN(R2),    KEY(F9),      { "Save game",           "セーブ"}},
         { 0, BTN(A),     KEY(RETURNL), { "Confirm / Read book", "メニューの決定 / 本を読む"}},
         { 0, BTN(B),     KEY(SPACE),   { "Cancel",              "メニューのキャンセル"}},
         { 0, BTN(START), KEY(ESC),     { "Pause",               "一時停止"}},
         { 0, BTN(A),     KEY(R),       { "" }},
         { 0, BTN(UP),    KEY(KP_8),    { "Up",    "上" }},
         { 0, BTN(DOWN),  KEY(KP_2),    { "Down",  "下" }},
         { 0, BTN(LEFT),  KEY(KP_4),    { "Left",  "左" }},
         { 0, BTN(RIGHT), KEY(KP_6),    { "Right", "右" }},

         { 0, 0, 0, NULL }
      }
   },

   { NULL, { 0 }, { 0, 0, 0, NULL } }
};
