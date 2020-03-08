#include <stdint.h>
#include <libretro.h>

#define MAX_DISK_COUNT         16
#define MESSAGE_DISPLAY_FRAMES 180
#define DRIVE_NONE             -1
#define NO_DISK                -1

typedef struct disk_t
{
   char basename[OSD_MAX_FILENAME];
   char filename[OSD_MAX_FILENAME];

   /* Which drive is this disk inserted into? */
   int8_t drive_index;

   /* Is this an arbitrary data disk for saving? */
   bool   is_user_disk;
} disk_t;

typedef struct drive_swap_t
{
   /* Is the user swapping drive A, B, or nothing? */
   uint8_t state;

   /* Which disk is currently loaded? */
   int8_t  index_a;
   int8_t  index_b;

   /* How many disks exist in the buffer? */
   uint8_t count;
} drive_swap_t;

void retro_disks_init  ();
bool retro_disks_append(const char *new_filename);
void retro_disks_cycle (retro_environment_t cb, bool right);
void retro_disks_ready ();
void retro_disks_set   (retro_environment_t cb);
void retro_disks_start (retro_environment_t cb, bool is_first_drive);

extern disk_t retro_disks[MAX_DISK_COUNT];
