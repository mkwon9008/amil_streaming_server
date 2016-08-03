

#ifndef AMIL_CONFIG_HEADER_INCLUDED
#define AMIL_CONFIG_HEADER_INCLUDED 

#include <amil_auto_headers.h>


//operating system.
#if (AMIL_LINUX)
#include <amil_linux_config.h>

#else 
#include <amil_posix_config.h>

#endif


#ifndef AMIL_HAVE_SO_SNDLOWAT
#define AMIL_HAVE_SO_SNDLOWAT 1
#endif

#define amil_cdecl
#define amil_libc_cdecl

#endif

#if(AMIL_PTR_SIZE == 4)
#define AMIL_INT_T_LEN AMIL_INT32_LEN
#define AMIL_MAX_INT_T_VALUE 2147483647

#else
#define AMIL_INT_T_LEN AMIL_INT64_LEN
#define AMIL_MAX_INT_T_VALUE 9223372036854775807
#endif



typedef intptr_t 	amil_intptr_t;
typedef	uintptr_t 	amil_uint_t;
typedef intptr_t 	amil_flag_t;

typedef uintptr_t 	amil_uint_t;

#define amil_align(d, a) (((d) + (a-1)) & ~(a-1)) 
#define amil_align_ptr(p, a)	(u_char *) (((uintptr_t ) (p) + ((uintptr_t) a - 1)) & ~((uintptr_t) a - 1))
