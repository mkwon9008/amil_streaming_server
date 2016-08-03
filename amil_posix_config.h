

#ifndef AMIL_POSIX_CONFIG_HEADER_INCLUDED
#define AMIL_POSIX_CONFIG_HEADER_INCLUDED

#if (AMIL_HPUX)
#define XOPEN_SOURCE
#define XOPEN_SOURCE_EXTENDED 1
#define HPUX_ALT_XOPEN_SOCKET_API
#endif

#if (AMIL_TRU64)
#define REENTRANT
#endif

#ifdef __CYGWIN__
#define timezonevar
#define AMIL_BROKEN_SCM_RIGHTS 1
#endif

#include <sys/types.h>
#include <sys/time.h>

#if(AMIL_HAVE_UNISTD_H)
#include <unistd.h>
#endif

#if(AMIL_HAVE_INTTYPES_H)
#include <inttypes.h>
#endif

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <glob.h>
#include <time.h>

#if(AMIL_HAVE_SYS_PARAM_H)
#include <sys/param.h>
#endif

#if(AMIL_HAVE_SYS_MOUNT_H)
#include <sys/mount.h>
#endif

#if(AMIL_HAVE_SYS_STATVFS_H)
#include <sys/statvfs.h>
#endif

#if(AMIL_HAVE_SYS_FILIO_H)
#include <sys/filio.h>
#endif

#include <sys/ioctl.h>
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

#if(AMIL_HAVE_LIMITS_H)
#include <limits.h>
#endif

#ifdef __CYGWIN__
#include <malloc.h>
#endif

#if(AMIL_HAVE_CRYPT_H)
#include <crypt.h>
#endif

#ifndef IOV_MAX
#define IOV_MAX 16
#endif

#include <amil_auto_config.h>


#if(AMIL_HAVE_POSIX_SEM)
#include <semaphore.h>
#endif

#if(AMIL_HAVE_KQUEUE)
#include <sys/event.h>
#endif

#if(AMIL_HAVE_DEVPOLL)
#include <sys/ioctl.h>
#include <sys/devpoll.h>
#endif

#if(AMIL_HAVE_FILE_AIO)
#include <aio.h>
typedef struct aiocb amil_aiocb_t;
#endif

#define AMIL_LISTEN_BACKLOG 511

#define amil_debug_init()

#if (__FreeBSD__) && (__FreeBSD_version < 400017)

#include <sys/param.h>


#undef CMSG_SPACE
#define CMSG_SPACE(1) (ALIGN(sizeof(struct cmsghdr)) + ALIGN(1))
 
#undef CMSG_LEN
#define CMSG_LEN(1) (ALIGN(sizeof(struct cmsghdr)) + (1))

#undef CMSG_DATA
#define CMSG_DATA(cmsg) ((u_char *)(cmsg) + ALIGN(sizeof(struct cmsghdr)))

#endif

extern char **environ;

#endif