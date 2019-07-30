#ifndef	FILENAME_H_INCLUDED
#define	FILENAME_H_INCLUDED

#include <boolean.h>

#ifndef	QUASI88_FLIBRETRO
#define	QUASI88_FLIBRETRO
#endif

#ifndef	CONFIG_SUFFIX
#define	CONFIG_SUFFIX		".rc"
#endif

#ifndef	CONFIG_FILENAME
#define	CONFIG_FILENAME		"quasi88"
#endif

#ifndef	KEYCONF_FILENAME
#define	KEYCONF_FILENAME	"keyconf"
#endif

#ifndef	STATE_SUFFIX
#define	STATE_SUFFIX		".sta"
#endif

#ifndef	STATE_FILENAME
#define	STATE_FILENAME		"quasi88"
#endif

#ifndef	SNAPSHOT_FILENAME
#define	SNAPSHOT_FILENAME	"save"
#endif

#ifndef	WAVEOUT_FILENAME
#define	WAVEOUT_FILENAME	"wave"
#endif

#ifdef _WIN32
#define SLASH '\\'
#else
#define SLASH '/'
#endif

extern char *save_path;
extern bool  save_to_disk_image;

#endif	/* FILENAME_H_INCLUDED */
