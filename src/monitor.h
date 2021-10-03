#ifndef MONITOR_H_INCLUDED
#define MONITOR_H_INCLUDED



extern	int	debug_mode;			/* デバッグ機能(モニター)  */
extern	char	alt_char;			/* 代替文字 */

void	set_signal( void );

void print_hankaku(FILE *fp, Uchar *str, char npc);

#endif	/* MONITOR_H_INCLUDED */
