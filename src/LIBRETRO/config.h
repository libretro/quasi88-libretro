#ifndef	CONFIG_H_INCLUDED
#define	CONFIG_H_INCLUDED


/*----------------------------------------------------------------------*/
/* システム固有の定義							*/
/*----------------------------------------------------------------------*/

/* システム固有のインクルードファイル */
/* #include <XXXXX.h> */


/* このシステム専用の QUASI88 のための識別用 (必要なら) */

#ifndef	QUASI88_LIBRETRO
#define	QUASI88_LIBRETRO
#endif



#include <retro_endianness.h>



/* メニューのタイトル／バージョン表示にて追加で表示する言葉 (任意の文字列) */

#define	Q_COMMENT	"LIBRETRO port"



/* 画面の bpp の定義。最低でもどれか一つは定義しなくてはならない */

#undef	SUPPORT_8BPP
#define	SUPPORT_16BPP
#undef	SUPPORT_32BPP



/* libretro makefile handles this */
/* #define	INLINE		static */



#if	0

/* サウンド出力に対応する場合 (MAMEベース) */
#define	USE_SOUND

/* さらに、 fmgen にも対応する場合 */
#define	USE_FMGEN

/* コンパイラによっては、PI(π) と M_PI(π)の定義が必要かもしれない */
#ifndef PI
#define PI 3.14159265358979323846
#endif
#ifndef	M_PI
#define	M_PI	PI
#endif

#endif

#endif	/* CONFIG_H_INCLUDED */
