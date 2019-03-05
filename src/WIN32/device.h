#ifndef DEVICE_H_INCLUDED
#define DEVICE_H_INCLUDED


#include <windows.h>
#include <stdio.h>


/*
 *	src/WIN32/ 莉･荳九〒縺ｮ繧ｰ繝ｭ繝ｼ繝舌Ν螟画焚
 */
extern	HINSTANCE	g_hInstance;
extern	HWND		g_hWnd;
extern	HMENU		g_hMenu;

extern	int		g_keyrepeat;
extern	int		g_pcm_bufsize;

extern	FILE		*debugfp;



/*
 *	src/WIN32/ 莉･荳九〒縺ｮ繧ｰ繝ｭ繝ｼ繝舌Ν螟画焚 (繧ｪ繝励す繝ｧ繝ｳ險ｭ螳壼庄閭ｽ縺ｪ螟画焚)
 */



LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
extern	int	graph_update_WM_PAINT(void);
extern	void	menubar_setup(int active);
extern	int	menubar_event(int id);
extern	void	wave_event_open(HWAVEOUT hwo);
extern	void	wave_event_done(HWAVEOUT hwo, LPWAVEHDR lpwhdr);
extern	void	wave_event_close(HWAVEOUT hwo);


#endif	/* DEVICE_H_INCLUDED */
