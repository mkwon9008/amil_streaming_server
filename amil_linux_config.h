/* Created by Kwon */
/* It referenced by nginx/src/nginx_linux_config.h */

#ifndef AMIL_LINUX_CONFIG_HEADER_INCLUDED
#define AMIL_LINUX_CONFIG_HEADER_INCLUDED

#ifndef GNU_SOURCE
#define GNU_SOURCE

#endif

#define _FILE_OFFSET_BITS  64

#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdarg.h>
#include <stddef.h>             
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <glob.h>
#include <sys/vfs.h>            

#include <sys/uio.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <sched.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>        
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/un.h>

#include <time.h>               
#include <malloc.h>             
#include <limits.h>             
#include <sys/ioctl.h>
#include <crypt.h>
#include <sys/utsname.h>        

#include <dlfcn.h>

#include <amil_auto_config.h>

#if(AMIL_HAVE_POSIX_SEM)
#include <semaphore.h>
#endif


#if (AMIL_HAVE_SYS_PRCTL_H)
#include <sys/sendfile.h>
#else
extern ssize_t sendfile(int s, int fd, int32_t *offset, size_t size);
#define AMIL_SENDFILE_LIMIT 0x80000000
#endif



#if (AMIL_HAVE_POLL)
#include <poll.h>
#endif

#if(AMIL_HAVE_EPOLL)
#include <sys/epoll.h>
#endif


#if(AMIL_HAVE_SYS_EVENTFD_H)
#include <sys/eventfd.h>
#endif
#include <sys/syscall.h>
#if(AMIL_HAVE_FILE_AIO)
#include <linux/aio_abi.h>
typedef struct iocb amil_aiocb_t;
#endif


#define AMIL_LISTEN_BACKLOG		511

#ifdef AMIL_HAVE_SO_SNDLOWAT
#define AMIL_HAVE_SO_SNDLOWAT	0
#endif


#ifdef AMIL_HAVE_INHERITED_NONBLOCK 
#define AMIL_HAVE_INHERITED_NONBLOCK 0
#endif

#define AMIL_HAVE_OS_SPECIFIC_INIT	1
#define amil_debug_init()

extern char **environ;

#endif
