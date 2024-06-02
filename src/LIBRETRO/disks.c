#include <file/file_path.h>
#include <streams/file_stream.h>
#include <string/stdstring.h>
#include <vfs/vfs_implementation.h>
#include <compat/msvc.h>
#include <wchar.h>

#include "quasi88.h"
#include "drive.h"
#include "event.h"

#include "disks.h"

disk_t retro_disks[MAX_DISK_COUNT];
static drive_swap_t swap;

void disk_display_message(retro_environment_t cb)
{
   if (swap.state == DRIVE_NONE)
      return;
   else
   {
      bool    is_first_drive = swap.state == DRIVE_1;
      char    drive_id       = is_first_drive ? '1' : '2';
      int8_t *index          = is_first_drive ? &swap.index_a : &swap.index_b;
      wchar_t msg[OSD_MAX_FILENAME];
      struct  retro_message rmsg;

      if (*index == NO_DISK)
         snprintf((char*)msg, 2048, "Drive %c: %s", drive_id, "No disk");
      else
         snprintf((char*)msg, 2048, "Drive %c: %s", drive_id, retro_disks[*index].basename);

      rmsg.frames = MESSAGE_DISPLAY_FRAMES;
      rmsg.msg = (const char*)msg;
      cb(RETRO_ENVIRONMENT_SET_MESSAGE, &rmsg);
   }
}

bool is_user_disk(const char *filename)
{
   return !(strncmp(path_get_extension(filename), "u88", 3) || 
      strncmp(path_get_extension(filename), "U88", 3));
}

void retro_disks_init()
{
   swap.count   = 0;
   swap.index_a = -1;
   swap.index_b = -1;
   swap.state   = DRIVE_NONE;
}

bool retro_disks_append(const char *new_filename)
{
   if (swap.count >= MAX_DISK_COUNT)
      return false;
   else
   {
      disk_t *new_disk = &retro_disks[swap.count];

      strncpy(new_disk->filename, new_filename, OSD_MAX_FILENAME);
      new_disk->drive_index = DRIVE_NONE;
      new_disk->is_user_disk = is_user_disk(new_filename);
      strncpy(new_disk->basename, path_basename(new_filename), OSD_MAX_FILENAME);
      swap.count++;

      if (swap.count == 1)
         swap.index_a = 0;
      else if (swap.count == 2)
         swap.index_b = 1;

      return true;
   }
}

void retro_disks_start(retro_environment_t cb, bool is_first_drive)
{
   if (is_first_drive)
      swap.state = DRIVE_1;
   else
      swap.state = DRIVE_2;
   disk_display_message(cb);
}

void retro_disks_cycle(retro_environment_t cb, bool right)
{
   if (swap.state == DRIVE_NONE)
      return;
   else
   {
      int8_t  *index = swap.state == DRIVE_1 ? 
          &swap.index_a : &swap.index_b;
      uint8_t  i;

      if (right)
      {
         if (*index < swap.count - 1)
            *index += 1;
      }
      else
      {
         *index -= 1;
         if (*index < 0)
            *index = NO_DISK;
      }
      disk_display_message(cb);
   }
}

void retro_disks_ready()
{
   uint8_t i;

   for (i = 2; i < swap.count; i++)
      quasi88_disk_insert(DRIVE_1, retro_disks[i].filename, i - 1, 0);
   if (swap.count > 0)
      quasi88_disk_insert(DRIVE_1, retro_disks[0].filename, 0, 0);
   if (swap.count > 1)
      quasi88_disk_insert(DRIVE_2, retro_disks[1].filename, 0, 0);
}

void retro_disks_set(retro_environment_t cb)
{
   int8_t  index;
   char    drive_id = swap.state == DRIVE_1 ? '1' : '2';
   char    msg[OSD_MAX_FILENAME];
   struct  retro_message rmsg;

   if (swap.state == DRIVE_1)
      index = swap.index_a;
   else if (swap.state == DRIVE_2)
      index = swap.index_b;
   else
      return;

   if (index != NO_DISK)
   {
      if (!quasi88_disk_insert(swap.state, retro_disks[index].filename, 0, 0))
         snprintf(msg, sizeof(msg), "Drive %c: Error! (%s)", drive_id, retro_disks[index].filename);
      else
      {
         snprintf(msg, sizeof(msg), "Drive %c: %s set.", drive_id, retro_disks[index].basename);
         retro_disks[index].drive_index = swap.state;
      }
   }
   else
   {
      quasi88_disk_eject(swap.state);
      snprintf(msg, sizeof(msg), "Drive %c: No disk set.", drive_id);
   }
   swap.state = DRIVE_NONE;

   rmsg.frames = MESSAGE_DISPLAY_FRAMES;
   rmsg.msg = msg;
   cb(RETRO_ENVIRONMENT_SET_MESSAGE, &rmsg);
}
