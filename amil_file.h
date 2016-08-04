

/*	amil_file.h
*	This file is definition macro and struct and Preprocessing about amil_file.c
*	<RULE>
*	1. Function is created as concise as possible.
*	2. If you must write a custom function before amil + underbar.
*	3. Function names are separated by a custom type + content + relevant work.
*	   If needed, it may be written the use of the method object between custom type and content.
*	4. The macro statement is written in capital letters.
*/	

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


typedef int 	amil_fd_t;
typedef struct stat amil_file_info_t;
typedef ino_t amil_file_uniq_t;

/*	amil_file_s
*	amil_fd_t = defined by amil_file.h
*	amil_str_t = defined by amil_string.h
*	amil_file_into_t = defined by <sys/types.h>
*	amil_log_t = defined by amil_core.h
*	amil_event_aio_t = defined by amil_core.h
*/
struct amil_file_s
{
	amil_fd_t fd;
	amil_str_t name; 
	amil_file_info_t info;

	off_t /* type long*/ offset;
	off_t /* type long*/ sys_offset;

	amil_log_t *log

	#if (AMIL_HAVE_FILE_AIO)
	amil_event_aio_t *aio;
	#endif
	unsigned valid_info:1;
	unsigned directio:1;
};

/*	amil_path_t
*	amil_str_t = defined by amil_string.h
*	size_t = defined by <sys/types.h>
*	amil_path_manager_pt = 
*	amil_path_loader_pt = 
*	amil_uint_t = defined by amil_config.h
*/
typedef struct
{
	amil_str_t name;
	size_t level[3];
	size_t len;

	amil_path_manager_pt manager;
	amil_path_loader_pt loader;
	void 				*data; //Generic pattern.

	u_char *conf_file;
	amil_uint_t line;
}amil_path_t;


//Macro defination start.
#define amil_close_file close
#define amil_close_file_n "close()"

#define amil_delete_file(name) unlink((const char * ) name)
#define amil_delete_file_n "unlink()"

amil_fd_t amil_open_tempfile(u_char *name, amil_uint_t persistent, amil_uint_t access);
#define amil_open_tempfile_n "open()"

#if(AMIL_HAVE_PREAD)
#define amil_read_file_n "pread()"
#else
#define amil_read_file_n "read()"
#endif

#define amil_read_fd read
#define amil_read_fd_n	"read()"



//Preprocessing functionality.

ssize_t amil_write_file(amil_file_t *file, u_char *buf, size_t size, off_t offset);
ssize_t amil_write_chain_to_file(amil_file_t *file, amil_chain_t *ce, off_t offset, amil_pool_t *pool);

amil_int_t amil_get_full_name(amil_pool_t *pool, amil_str_t *prefix, amil_str_t *name)
ssize_t amil_write_chain_to_temp_file(amil_temp_file_t *tf, amil_chain_t *chain)
amil_int_t amil_create_temp_file(amil_file_t *file, amil_path_t *path, amil_pool_t *pool, amil_uint_t persistent, amil_uint_t clean, amil_uint_t access)
