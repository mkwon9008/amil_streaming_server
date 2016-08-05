
/*	amil_config.h
*	This file is definition macro and Preprocessing. 
*	And include amil_auto_headers.h, amil_linux_config.h, amil_posix_config.h
*	<RULE>
*	1. Function is created as concise as possible.
*	2. If you must write a custom function before amil + underbar.
*	3. Function names are separated by a custom type + content + relevant work.
*	   If needed, it may be written the use of the method object between custom type and content.
*	4. The macro statement is written in capital letters.
*/	

#ifndef AMIL_CONFIG_HEADER_INCLUDED
#define AMIL_CONFIG_HEADER_INCLUDED

#include <amil_auto_headers.h>


//MACRO check type of operating system.
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


//Defined Max value via Operation bit type.
#if(AMIL_PTR_SIZE == 4)
#define AMIL_INT_T_LEN AMIL_INT32_LEN
#define AMIL_MAX_INT_T_VALUE 2147483647

#else
#define AMIL_INT_T_LEN AMIL_INT64_LEN
#define AMIL_MAX_INT_T_VALUE 9223372036854775807
#endif



typedef intptr_t 	amil_intptr_t;
typedef intptr_t 	amil_int_t;
typedef intptr_t 	amil_flag_t;

typedef uintptr_t 	amil_uint_t;

#define amil_align(d, a) (((d) + (a-1)) & ~(a-1)) 
#define amil_align_ptr(p, a)	(u_char *) (((uintptr_t ) (p) + ((uintptr_t) a - 1)) & ~((uintptr_t) a - 1))

#define amil_inline
#define amil_inline inline


