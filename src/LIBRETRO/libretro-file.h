typedef struct OSD_FILE_STRUCT		OSD_FILE;

OSD_FILE *osd_file_mem(char *mem, size_t size, int is_writeable);
int osd_file_did_overflow(OSD_FILE * fp);
