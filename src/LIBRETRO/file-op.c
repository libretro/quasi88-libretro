/*****************************************************************************/
/* ファイル操作に関する処理                */
/*                       */
/*  仕様の詳細は、ヘッダファイル file-op.h 参照          */
/*                       */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#ifdef _WIN32
#include <direct.h>
#else
#include <unistd.h>
#endif
#include <errno.h>

#ifdef _MSC_VER
#include <compat/msvc.h>
#endif

#include <file/file_path.h>
#include <streams/file_stream.h>
#include <string/stdstring.h>
#include <vfs/vfs_implementation.h>

#include "quasi88.h"
#include "initval.h"
#include "file-op.h"
#include "menu.h"


/*****************************************************************************/

/* 以下のディレクトリ名は、予め OSD_MAX_FILENAME バイトの
   固定長バッファを確保して、それにわりあてる。
  (malloc/free で動的に管理する方がスマートかもしれないけど…) */

static char *dir_cwd; /* デフォルトのディレクトリ (カレント)    */
static char *dir_rom; /* ROMイメージファイルの検索ディレクトリ */
static char *dir_disk;  /* DISKイメージファイルの検索ディレクトリ  */
static char *dir_tape;  /* TAPEイメージファイルの基準ディレクトリ  */
static char *dir_snap;  /* 画面スナップショットファイルの保存先   */
static char *dir_state; /* サスペンドファイルの保存先      */
static char *dir_g_cfg; /* 共通設定ファイルのディレクトリ    */
static char *dir_l_cfg; /* 個別設定ファイルのディレクトリ    */



/****************************************************************************
 * 各種ディレクトリの取得  (osd_dir_cwd は NULLを返してはだめ !)
 *****************************************************************************/
const char *osd_dir_cwd  (void) { return dir_cwd;   }
const char *osd_dir_rom  (void) { return dir_rom;   }
const char *osd_dir_disk (void) { return dir_disk;  }
const char *osd_dir_tape (void) { return dir_tape;  }
const char *osd_dir_snap (void) { return dir_snap;  }
const char *osd_dir_state(void) { return dir_state; }
const char *osd_dir_gcfg (void) { return dir_g_cfg[0] ? dir_g_cfg : NULL; }
const char *osd_dir_lcfg (void) { return dir_l_cfg[0] ? dir_l_cfg : NULL; }

static int set_new_dir(const char *newdir, char *dir)
{
    if (strlen(newdir) < OSD_MAX_FILENAME) {
  strcpy(dir, newdir);
  return TRUE;
    }
    return FALSE;
}

int osd_set_dir_cwd  (const char *d) { return set_new_dir(d, dir_cwd);   }
int osd_set_dir_rom  (const char *d) { return set_new_dir(d, dir_rom);   }
int osd_set_dir_disk (const char *d) { return set_new_dir(d, dir_disk);  }
int osd_set_dir_tape (const char *d) { return set_new_dir(d, dir_tape);  }
int osd_set_dir_snap (const char *d) { return set_new_dir(d, dir_snap);  }
int osd_set_dir_state(const char *d) { return set_new_dir(d, dir_state); }
int osd_set_dir_gcfg (const char *d) { return set_new_dir(d, dir_g_cfg); }
int osd_set_dir_lcfg (const char *d) { return set_new_dir(d, dir_l_cfg); }







/****************************************************************************
 * ファイル名に使用されている漢字コードを取得
 *    0 … ASCII のみ
 *    1 … 日本語EUC
 *    2 … シフトJIS
 *    3 … UTF-8
 *****************************************************************************/
int osd_kanji_code(void)
{
    if      (file_coding == 2) return 3;
    else if (file_coding == 1) return 2;
    else                       return 1;
}



/****************************************************************************
 * ファイル操作
 *
 * OSD_FILE *osd_fopen(int type, const char *path, const char *mode)
 * int  osd_fclose(OSD_FILE *stream)
 * int  osd_fflush(OSD_FILE *stream)
 * int  osd_fseek(OSD_FILE *stream, long offset, int whence)
 * long osd_ftell(OSD_FILE *stream)
 * void osd_rewind(OSD_FILE *stream)
 * size_t osd_fread(void *ptr, size_t size, size_t nobj, OSD_FILE *stream)
 * size_t osd_fwrite(const void *ptr,size_t size,size_t nobj,OSD_FILE *stream)
 * int  osd_fputc(int c, OSD_FILE *stream)
 * int  osd_fgetc(OSD_FILE *stream)
 * char *osd_fgets(char *str, int size, OSD_FILE *stream)
 * int  osd_fputs(const char *str, OSD_FILE *stream)
 *****************************************************************************/

/* The original code does not allow the same disk/tape file to be opened
   in multiple instances. We need to store path instead of serial number
   for platform compatibility. */

struct OSD_FILE_STRUCT
{
   RFILE   *fp;                     /* NULL when not in use                     */
   RFILE   *sfp;                    /* File to store differences saved to disks */
   uint8_t  mode;                   /* VFS file open flags (libretro.h)         */
   char     path[OSD_MAX_FILENAME]; /* Path to opened file                      */
   uint8_t  type;                   /* File type (file-op.h)                    */
};

#define  MAX_STREAM  16
static   OSD_FILE osd_stream[MAX_STREAM];

/* The original code uses strings to decide file access mode. 
   Here, we will use the flags defined in libretro.h */
uint8_t get_file_access_mode(const char *mode)
{
   uint8_t i = 0;
   uint8_t retro_mode = 0;

   do
   {
      switch (mode[i])
      {
      case 'r':
         retro_mode |= RETRO_VFS_FILE_ACCESS_READ;
         break;
      case 'w':
         retro_mode |= RETRO_VFS_FILE_ACCESS_WRITE;
         break;
      case '+':
         retro_mode |= RETRO_VFS_FILE_ACCESS_WRITE;
      case 'a':
         retro_mode |= RETRO_VFS_FILE_ACCESS_UPDATE_EXISTING;
      }
      i++;
   } while (mode[i] != '\0');

   return retro_mode;
}

OSD_FILE *osd_fopen(int type, const char *path, const char *mode)
{
   uint8_t   i;
   uint8_t   retro_mode;
   OSD_FILE *current_stream;
   uint8_t   stat;

   retro_mode = get_file_access_mode(mode);
   if (!retro_mode)
      return NULL;

   /* Try to find a free spot in the filestream buffer */
   current_stream = NULL;
   for (i = 0; i < MAX_STREAM; i++)
   {
      if (osd_stream[i].fp == NULL)
      {
         current_stream = &osd_stream[i];
         break;
      }
   }
   if (current_stream == NULL)
      return NULL;

   /* Make sure file exists if it needs to be read */
   stat = osd_file_stat(path);
   if (stat != FILE_STAT_FILE && retro_mode == RETRO_VFS_FILE_ACCESS_READ)
         return NULL;

   switch (type)
   {
   case FTYPE_DISK:      /* "r+b", "rb" */
   case FTYPE_TAPE_LOAD: /* "rb"        */
   case FTYPE_TAPE_SAVE: /* "ab"        */
   case FTYPE_PRN:       /* "ab"        */
   case FTYPE_COM_LOAD:  /* "rb"        */
   case FTYPE_COM_SAVE:  /* "ab"        */

      if (stat == FILE_STAT_FILE)
      {
         for (i = 0; i < MAX_STREAM; i++)
         {
            if (osd_stream[i].fp && string_is_equal(osd_stream[i].path, path))
            {
               return &osd_stream[i];
            }
         }
      }

   /* FALLTHROUGH */
   default:
      current_stream->fp = filestream_open(path, retro_mode, 0);
      if (current_stream->fp)
      {
         if (stat == FILE_STAT_NOEXIST)
         {
            filestream_flush(current_stream->fp);
            /* This shouldn't happen */
            if (osd_file_stat(path) != FILE_STAT_FILE)
               return NULL;
         }
         current_stream->mode = retro_mode;
         snprintf(current_stream->path, OSD_MAX_FILENAME, "%s", path);
         current_stream->type = type;

         /* Set up diff file if the loaded file is a disk */
         if (type == FTYPE_DISK)
         {
            char save_name[OSD_MAX_FILENAME];

            snprintf(save_name, OSD_MAX_FILENAME, "%s%c%s.srm", save_path, SLASH, path_remove_extension(path_basename(path)));
            /* Create diff file if it does not already exist */
            if (osd_file_stat(save_name) != FILE_STAT_FILE)
               filestream_write_file(save_name, 0, 0);
            current_stream->sfp = filestream_open(save_name, retro_mode, 0);
         }
         else
            current_stream->sfp = NULL;

         if (retro_mode & RETRO_VFS_FILE_ACCESS_UPDATE_EXISTING)
            osd_fseek(current_stream, 0, RETRO_VFS_SEEK_POSITION_END);

         return current_stream;
      }
      else
         return NULL;
   }
}

int osd_fclose(OSD_FILE *stream)
{
   /* Leave streams open for disks so we can swap easily */
   if (stream->type == FTYPE_DISK)
      return TRUE;
   else
   {
      RFILE *fp  = stream->fp;

      stream->fp  = NULL;

      return filestream_close(fp);
   }
}

int osd_fflush(OSD_FILE *stream)
{
   if (stream == NULL)
      return filestream_flush(NULL);
   else
      return filestream_flush(stream->fp);
}

int osd_fseek(OSD_FILE *stream, long offset, int whence)
{
   return filestream_seek(stream->fp, offset, whence);
}

long osd_ftell(OSD_FILE *stream)
{
   return filestream_tell(stream->fp);
}

void osd_rewind(OSD_FILE *stream)
{
   (void)osd_fseek(stream, 0L, SEEK_SET);
   osd_fflush(stream);
}

size_t osd_fread_diff(void *ptr, size_t size, OSD_FILE *stream)
{
   if (!stream->fp)
      return 0;
   else
   {
      int8_t *diff;
      size_t  diff_size;

      /* Offset to the position that the read attempt was made at */
      filestream_seek(stream->sfp, filestream_tell(stream->fp), SEEK_SET);
      size      = filestream_read(stream->fp,  ptr,  size);
      diff      = (int8_t*)calloc(size, sizeof(int8_t));
      diff_size = filestream_read(stream->sfp, diff, size);

      /* Add difference of each byte to read buffer*/
      for (; diff_size != 0; diff_size--)
         ((uint8_t*)ptr)[diff_size] = ((uint8_t*)ptr)[diff_size] + diff[diff_size];

      free(diff);
      return size;
   }
}

size_t osd_fwrite_diff(const void *ptr, uint32_t size, OSD_FILE *stream)
{
   void     *diff;
   uint32_t  diff_offset;
   size_t    diff_size;

   /* Backup the current position, then read data from disk into buffer */
   diff        = (void*)calloc(size, sizeof(int8_t));
   diff_offset = filestream_tell(stream->fp);
   diff_size   = filestream_read(stream->fp, diff, size);

   /* Write difference of each byte to file */
   for (; diff_size != 0; diff_size--)
      ((int8_t*)diff)[diff_size] = ((uint8_t*)ptr)[diff_size] - ((uint8_t*)diff)[diff_size];
   filestream_seek(stream->sfp, diff_offset, SEEK_SET);
   filestream_write(stream->sfp, diff, size);

   free(diff);
   return size;
}

#define SAVE_DIFF !save_to_disk_image && stream->type == FTYPE_DISK && stream->sfp

size_t osd_fread(void *ptr, size_t size, size_t nobj, OSD_FILE *stream)
{
   if (SAVE_DIFF)
      return osd_fread_diff(ptr, size * nobj, stream);
   else
      return filestream_read(stream->fp, ptr, size * nobj);
}

size_t osd_fwrite(const void *ptr, size_t size, size_t nobj, OSD_FILE *stream)
{
   if (SAVE_DIFF)
      return osd_fwrite_diff(ptr, size * nobj, stream);
   else
      return filestream_write(stream->fp, ptr, size * nobj);
}

int osd_fputc(int c, OSD_FILE *stream)
{
   return filestream_putc(stream->fp, c);
}

int osd_fgetc(OSD_FILE *stream)
{
   return filestream_getc(stream->fp);
}

char *osd_fgets(char *str, int size, OSD_FILE *stream)
{
   return filestream_gets(stream->fp, str, size);
}

/* libretro-common does not have an fputs implementation */
int osd_fputs(const char *str, OSD_FILE *stream)
{
   uint32_t i = 0;

   while (str[i] != '\0')
   {
      if (!filestream_putc(stream->fp, str[i]))
      {
         i = FALSE;
         break;
      }
      i++;
   }

   return i;
}

/****************************************************************************
 * ディレクトリ閲覧
 *****************************************************************************/

struct  T_DIR_INFO_STRUCT
{
    int   cur_entry;    /* 上位が取得したエントリ数 */
    int   nr_entry;   /* エントリの全数    */
    T_DIR_ENTRY *entry;     /* エントリ情報 (entry[0]〜) */
};



/*
 * ディレクトリ内のファイル名のソーティングに使う関数
 */
static int namecmp(const void *p1, const void *p2)
{
    T_DIR_ENTRY *s1 = (T_DIR_ENTRY *)p1;
    T_DIR_ENTRY *s2 = (T_DIR_ENTRY *)p2;

    return strcmp(s1->name, s2->name);
}




/*---------------------------------------------------------------------------
 * T_DIR_INFO *osd_opendir(const char *filename)
 *  opendir()、rewinddir()、readdir()、closedir() を駆使し、
 *  ディレクトリの全てのエントリのファイル名をワークにセットする。
 *  ワークは malloc で確保するが、失敗時はそこでエントリの取得を打ち切る。
 *  処理後は、このワークをファイル名でソートしておく。
 *---------------------------------------------------------------------------*/
/* Folder operations are stubbed because they are only used in the original UI.
   These would be worth rewriting if we decide to call it. */

T_DIR_INFO *osd_opendir(const char *filename)
{
   return NULL;
}

T_DIR_ENTRY *osd_readdir(T_DIR_INFO *dirp)
{
   return NULL;
}

void osd_closedir(T_DIR_INFO *dirp)
{
}

/****************************************************************************
 * パス名の操作
 *****************************************************************************/

/*---------------------------------------------------------------------------
 * int  osd_path_normalize(const char *path, char resolved_path[], int size)
 *
 *  処理内容:
 *    ./ は削除、 ../ は親ディレクトリに置き換え、 /…/ は / に置換。
 *    面倒なので、リンクやカレントディレクトリは展開しない。
 *    末尾に / が残った場合、それは削除する。
 *  例:
 *    "../dir1/./dir2///dir3/../../file" → "../dir1/file"
 *---------------------------------------------------------------------------*/
int osd_path_normalize(const char *path, char resolved_path[], int size)
{
    char *buf, *s, *d, *p;
    int is_abs, is_dir, success = FALSE;
    size_t len = strlen(path);

    if (len == 0) {
  if (size) { resolved_path[0] = '\0';  success = TRUE; }
    } else {

  is_abs = (path[0]     == '/') ? TRUE : FALSE;
  is_dir = (path[len-1] == '/') ? TRUE : FALSE;

  buf = (char *)malloc((len+3) * 2);  /* path と同サイズ位の */
  if (buf) {        /* バッファを2個分 確保  */
      strcpy(buf, path);
      d = &buf[ len + 3 ];
      d[0] = '\0';

      s = strtok(buf, "/");   /* / で 区切っていく */

      if (s == NULL) {      /* 区切れないなら、 */
            /* それは / そのものだ  */
    if (size > 1) {
        strcpy(resolved_path, "/");
        success = TRUE;
    }

      } else {        /* 区切れたなら、分析  */

    for ( ; s ;  s = strtok(NULL, "/")) {

        if        (strcmp(s, ".")  == 0) {  /* . は無視  */
      ;

        } else if (strcmp(s, "..") == 0) {  /* .. は直前を削除 */

      p = strrchr(d, '/');        /* 直前の/を探す */

      if (p && strcmp(p, "/..") != 0) {   /* 見つかれば    */
          *p = '\0';          /*    そこで分断 */
      } else {                            /* 見つからない  */
          if (p == NULL && is_abs) {      /*   絶対パスなら*/
        ;         /*     無視する  */
          } else {          /*   相対パスなら*/
        strcat(d, "/..");     /*     .. にする */
          }
      }

        } else {        /* 上記以外は連結 */
      strcat(d, "/");         /* 常に / を前置 */
      strcat(d, s);
        }
    }

    if (d[0] == '\0') {   /* 結果が空文字列になったら */
        if (is_abs) strcpy(d, "/"); /*   元が絶対パスなら /     */
        /* else         ;    *   元が相対パスから 空    */

    } else {
        if (is_abs == FALSE) {  /* 元が相対パスなら */
      d ++;     /* 先頭の / を削除  */
        }
#if 0 /* この処理は無し。元が a/b/c/ でも a/b/c とする */
        if (is_dir) {   /* 元の末尾が / なら */
      strcat(d, "/");   /* 末尾に / を付加   */
        }
#endif
    }

    if (strlen(d) < (size_t)size) {
        strcpy(resolved_path, d);
        success = TRUE;
    }
      }

      free(buf);
  }
    }

    /*printf("NORM:\"%s\" => \"%s\"\n",path,resolved_path);*/
    return success;
}



/*---------------------------------------------------------------------------
 * int  osd_path_split(const char *path, char dir[], char file[], int size)
 *
 *  処理内容:
 *    path の最後の / より前を dir、後ろを file にセットする
 *      dir の末尾に / はつかない。
 *    path の末尾が / なら、予め削除してから処理する
 *      よって、 file の末尾にも / はつかない。
 *    path は予め、正規化されているものとする。
 *---------------------------------------------------------------------------*/
int osd_path_split(const char *path, char dir[], char file[], int size)
{
    int pos = strlen(path);

    /* dir, file は十分なサイズを確保しているはずなので、軽くチェック */
    if (pos == 0 || size <= pos) {
  dir[0]  = '\0';
  file[0] = '\0';
  strncat(file, path, size-1);
  if (pos) fprintf(stderr, "internal overflow %d\n", __LINE__);
  return FALSE;
    }


    if (strcmp(path, "/") == 0) { /* "/" の場合、別処理  */
  strcpy(dir, "/");     /* ディレクトリは "/"  */
  strcpy(file, "");     /* ファイルは "" */
  return TRUE;
    }

    if (path[ pos - 1 ] == '/') { /* path 末尾の / は無視 */
  pos --;
    }

    do {        /* / を末尾から探す  */
  if (path[ pos - 1 ] == '/') { break; }
  pos --;
    } while (pos);

    if (pos) {        /* / が見つかったら  */
  strncpy(dir, path, pos);    /* 先頭〜 / までをコピー*/
  if (pos > 1)
      dir[ pos - 1 ] = '\0';    /* 末尾の / は削除する  */
  else          /* ただし    */ 
      dir[ pos ] = '\0';      /* "/"の場合は / は残す */

  strcpy(file, &path[pos]);

    } else {        /* / が見つからなかった  */
  strcpy(dir,  "");     /* ディレクトリは "" */
  strcpy(file, path);     /* ファイルは path全て */
    }

    pos = strlen(file);     /* ファイル末尾の / は削除 */
    if (pos && file[ pos - 1 ] == '/') { 
  file[ pos - 1 ] = '\0';
    }

    /*printf("SPLT:\"%s\" = \"%s\" + \"%s\")\n",path,dir,file);*/
    return TRUE;
}



/*---------------------------------------------------------------------------
 * int  osd_path_join(const char *dir, const char *file, char path[], int size)
 *
 *  処理内容:
 *    file が / で始まっていたら、そのまま path にセット
 *    そうでなければ、"dir" + "/" + "file" を path にセット
 *    出来上がった path は正規化しておく
 *---------------------------------------------------------------------------*/
int osd_path_join(const char *dir, const char *file, char path[], int size)
{
    int len;
    char *p;

    if (dir == NULL    ||
  dir[0] == '\0' ||     /* ディレクトリ名なし or  */
  file[0] == '/') {     /* ファイル名が、絶対パス */

  if ((size_t)size <= strlen(file)) { return FALSE; }
  strcpy(path, file);

    } else {          /* ファイル名は、相対パス */

  path[0] = '\0';
  strncat(path, dir, size - 1);

  len = strlen(path);       /* ディレクトリ末尾  */
  if (len && path[ len - 1 ] != '/') {    /* が '/' でないなら */
      strncat(path, "/", size - len - 1);   /* 付加する          */
  }

  len = strlen(path);
  strncat(path, file, size - len - 1);

    }


    p = (char *)malloc(size);     /* 正規化しておこう */
    if (p) {
  strcpy(p, path);
  if (osd_path_normalize(p, path, size) == FALSE) {
      strcpy(path, p);
  }
  free(p);
    }

    /*printf("JOIN:\"%s\" + \"%s\" = \"%s\"\n",dir,file,path);*/
    return TRUE;
}



/****************************************************************************
 * ファイル属性の取得
 ****************************************************************************/

int osd_file_stat(const char *pathname)
{
   if (!path_is_valid(pathname))
       return FILE_STAT_NOEXIST;
   else if (path_is_directory(pathname))
       return FILE_STAT_DIR;
   else
       return FILE_STAT_FILE;
}

/****************************************************************************
 * int  osd_file_config_init(void)
 *
 *  この関数は、起動後に1度だけ呼び出される。
 *  正常終了時は真を、 malloc に失敗したなど異常終了時は偽を返す。
 *
 ****************************************************************************/
static int parse_tilda(const char *home, const char *path,
           char *result_path, int result_size);
static int make_dir(const char *dname);

/* This is stubbed as well, we don't load from a config file. */
int osd_file_config_init(void)
{
   return TRUE;
}


/*
 * path が ~ で始まっていたら、 home に置き換えて result_path に格納する。
 *  何らかの理由で格納できなかったら、偽を返す。
 */

static int parse_tilda(const char *home, const char *path,
           char *result_path, int result_size)
{
    int  i;
    char *buf;

    if (home           &&
  home[0] == '/' && /* home が / で始まっていて、   */
  path[0] == '~') { /* path が ~ で始まっている場合 */

  buf = (char *)malloc(strlen(home) + strlen(path) + 2);
  if (buf == NULL)
      return FALSE;

  if (path[1] == '/'  ||    /* path が ~/ や ~/xxx や ~ の場合 */
      path[1] == '\0') {

      sprintf(buf, "%s%s%s", home, "/", &path[1]);

  } else {      /* path が ~xxx や ~xxx/ の場合 */

      strcpy(buf, home);      /* home から最後のディレク */
      i = strlen(buf) - 1;    /* トリ部を削り切り取ろう  */

      while (0<=i && buf[i] == '/') {i--;}  /* 末尾の / を全てスキップ */
      while (0<=i && buf[i] != '/') {i--;}  /* / 以外を全てスキップ    */
      while (0<=i && buf[i] == '/') {i--;}  /* さらに / を全てスキップ */
              /*   (全部スキップして     */
      buf[i+1] = '\0';        /*    しまったら / になる) */

      strcat(buf, "/");
      strcat(buf, &path[1]);
  }

  osd_path_normalize(buf, result_path, result_size);

  free(buf);
  return TRUE;

    } else {      /* home が / で始まらない、 path が ~ で…… */

  if (strlen(path) < (size_t)result_size) {

      strcpy(result_path, path);
      return TRUE;

  } else {
      return FALSE;
  }
    }
}



/*
 *  ディレクトリ dname があるかチェック。無ければ作る。
 *    成功したら、真を返す
 */
static int make_dir(const char *dname)
{
   return path_mkdir(dname);
}

/****************************************************************************
 * int  osd_file_config_exit(void)
 *
 *  この関数は、終了後に1度だけ呼び出される。
 *
 ****************************************************************************/
void  osd_file_config_exit(void)
{
    if (dir_cwd)   free(dir_cwd);
    if (dir_rom)   free(dir_rom);
    if (dir_disk)  free(dir_disk);
    if (dir_tape)  free(dir_tape);
    if (dir_snap)  free(dir_snap);
    if (dir_state) free(dir_state);
    if (dir_g_cfg) free(dir_g_cfg);
    if (dir_l_cfg) free(dir_l_cfg);
}
