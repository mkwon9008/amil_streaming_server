

#ifndef AMIL_FILE_HEADER_INCLUDE
#define AMIL_FILE_HEADER_INCLUDE

#include <amil_config.h>
#include <amil_core.h>


/*typedef 
struct amil_file_s
{
	amil_fd_t fd;
	amil_str_t name;
	amil_file_info_t info;

	off_t offset;
	off_t sys_offset;

	amil_log_t *log
	unsigned info_valid:1;
};

struct amil_path_s
{
	amil_str_t name;
	u_int len;
	u_int level[3];
	amil_gc_handler_pt gc_handler;
};

typedef struct 
{
	amil_file_t file;
	off_t offset;
	amil_path_t *path;
	amil_pool_t *pool;
	char *warn;
	unsigned persistent:1;
}amil_temp_file_t;

*/

struct amil_file_s
{
	amil_fd_t fd;
	amil_str_t name; 
	amil_file_info_t info;

	off_t offset;
	off_t sys_offset;

	amil_log_t *log

	#if (AMIL_HAVE_FILE_AIO)
	amil_event_aio_t *aio;
	#endif
	unsigned valid_info:1;
	unsigned directio:1;
};

typedef struct
{
	amil_str_t name;
	size_t level[3];
	size_t len;

	amil_path_manager_pt manager;
	amil_path_loader_pt loader;
	void 				*data;

	u_char *conf_file;
	amil_uint_t line;
}amil_path_t;

#define amil_close_file close
#define amil_close_file_n "close()"

#define amil_delete_file(name) unlink((const char * ) name)
#define amil_delete_file_n "unlink()"


#define amil_open_tempfile_n "open()"
amil_fd_t amil_open_tempfile(u_char *name, amil_uint_t persistent, amil_uint_t access);

#if(AMIL_HAVE_PREAD)
#define amil_read_file_n "pread()"
#else
#define amil_read_file_n "read()"
#endif

ssize_t amil_write_file(amil_file_t *file, u_char *buf, size_t size, off_t offset);
ssize_t amil_write_chain_to_file(amil_file_t *file, amil_chain_t *ce, off_t offset, amil_pool_t *pool);

#define amil_read_fd read
#define amil_read_fd_n	"read()"



