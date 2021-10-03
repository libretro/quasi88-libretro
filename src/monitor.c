/************************************************************************/
/*									*/
/* モニターモード							*/
/*									*/
/************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>

#include "quasi88.h"
#include "initval.h"
#include "monitor.h"

#include "pc88cpu.h"
#include "pc88main.h"
#include "pc88sub.h"
#include "crtcdmac.h"
#include "memory.h"
#include "graph.h"
#include "intr.h"
#include "keyboard.h"
#include "pio.h"
#include "soundbd.h"
#include "screen.h"
#include "fdc.h"

#include "emu.h"
#include "drive.h"
#include "image.h"
#include "file-op.h"
#include "status.h"
#include "menu.h"
#include "pause.h"
#include "snddrv.h"
#include "wait.h"
#include "suspend.h"
#include "snapshot.h"
#include "event.h"

#include "basic.h"


#ifdef USE_GNU_READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif

#ifdef USE_LOCALE
#include <locale.h>
#include <langinfo.h>
#endif /* USE_LOCALE */



/************************************************************************/
/* SIGINT発生時 (Ctrl-C) 、モニターモードへ遷移するように設定		*/
/*	起動時に -debug オプション指定時のみ。未指定時は終了する。	*/
/************************************************************************/

int	debug_mode	= FALSE;		/* デバッグ機能(モニター)  */

char	alt_char	= 'X';			/* 代替文字 */



/* モニターモード以外の時に SIGINT(Ctrl-C)を受け取ったらモニターモードに移行 */

static	void	sigint_handler(int dummy)
{
    quasi88_monitor();
    signal(SIGINT, sigint_handler);
}

/* SIGTERM を受けとったら、終了する */

static	void	sigterm_handler(int dummy)
{
    quasi88_quit();
    z80main_cpu.icount = 0;
    z80sub_cpu.icount = 0;
}

/*-------- 割り込み設定 -------- */

void	set_signal(void)
{
    if (debug_mode) {
	signal(SIGINT,  sigint_handler);
	signal(SIGTERM, sigterm_handler);
    } else {
	signal(SIGINT,  sigterm_handler);
	signal(SIGTERM, sigterm_handler);
    }
}
