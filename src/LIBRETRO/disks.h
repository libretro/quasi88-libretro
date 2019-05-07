#include "quasi88.h"

#define CONFIRM_TIME 300
#define NO_DISK -1

typedef struct
{
   char      disk_name[QUASI88_MAX_FILENAME];
   uint8_t  *disk_data;
   uint32_t  disk_size;
} retro_disk_t;

void cycle_disk(uint8_t drive);

retro_disk_t *disks;
uint8_t       disk_total;
int8_t        disk_index_drive_a;
int8_t        disk_index_drive_b;