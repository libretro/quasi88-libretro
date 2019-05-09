/************************************************************************/
/*                                                                      */
/*            QUASI88                                                   */
/*                                                                      */
/************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "quasi88.h"
#include "device.h"

#include "getconf.h"   /* config_init */
#include "suspend.h"   /* stateload_system */
#include "menu.h"   /* menu_about_osd_msg */


/***********************************************************************
 * Main entry/exit point (main is stubbed because we enter from libretro.c)
 ************************************************************************/
static void finish(void);

/* Called when quasi88_exit() is called */
static void finish(void)
{
   config_exit();
}

/***********************************************************************
 * Savestates (more stubs)
 ************************************************************************/

int stateload_system(void)
{
   return TRUE;
}
int statesave_system(void)
{
   return TRUE;
}

/***********************************************************************
 * System-specific message displayed on menu info tab
 ************************************************************************/

int menu_about_osd_msg(int req_japanese, int *result_code, const char *message[])
{
    return FALSE;
}
