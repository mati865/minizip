#ifndef _MINISHARED_H
#define _MINISHARED_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __APPLE__
    /* In darwin and perhaps other BSD variants off_t is a 64 bit value, hence no need for specific 64 bit functions */
#  define FOPEN_FUNC(filename, mode) fopen(filename, mode)
#  define FTELLO_FUNC(stream) ftello(stream)
#  define FSEEKO_FUNC(stream, offset, origin) fseeko(stream, offset, origin)
#else
#  define FOPEN_FUNC(filename, mode) fopen64(filename, mode)
#  define FTELLO_FUNC(stream) ftello64(stream)
#  define FSEEKO_FUNC(stream, offset, origin) fseeko64(stream, offset, origin)
#endif

#ifdef _WIN32
#  define MKDIR(d) _mkdir(d)
#  define CHDIR(d) _chdir(d)
#else
#  define MKDIR(d) mkdir(d, 0775)
#  define CHDIR(d) chdir(d)
#endif

/***************************************************************************/

/* Get a file's date and time in dos format */
uint32_t get_file_date(const char *path, uint32_t *dos_date);

/* Sets a file's date and time in dos format */
void change_file_date(const char *path, uint32_t dos_date);

/* Convert dos date/time format to struct tm */
int dosdate_to_tm(uint64_t dos_date, struct tm *ptm);

/* Convert struct tm to dos date/time format */
uint32_t tm_to_dosdate(const struct tm *ptm);

/* Create a directory and all subdirectories */
int makedir(const char *newdir);

/* Check to see if a file exists */
int check_file_exists(const char *path);

/* Check to see if a file is over 4GB and needs ZIP64 extension */
int is_large_file(const char *path);

/* Calculate the CRC32 of a file, because to encrypt a file, we need known the CRC32 of the file before */
int get_file_crc(const char *path, void *buf, uint32_t size_buf, uint32_t *result_crc);

/***************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* _MINISHARED_H */