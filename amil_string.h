
/*	amil_string.h
*	This file is defined macros and structs.
*	<RULE>
*	1. Function is created as concise as possible.
*	2. If you must write a custom function before amil + underbar.
*	3. Function names are separated by a custom type + content + relevant work.
	   If needed, it may be written the use of the method object between custom type and content.
*	4. The macro statement is written in capital letters.
*/	

#ifndef AMIL_STRING_HEADER_INCLUDE
#define AMIL_STRING_HEADER_INCLUDE

#include <amil_config.h>
#include <amil_core.h>

/* typedefined amil_str_t. */
typedef struct 
{
	size_t len;
	u_char *data;
}amil_str_t;

/* typedefined amil_keyval_t. */
typedef struct 
{
	amil_str_t key;
	amil_str_t value;
}amil_keyval_t;

/* typedefined amil_variable_value_t. */
typedef struct 
{
	unsigned len:28;
	unsigned valid:1;
	unsigned no_chacheable:1;
	unsigned escape:1;

	u_char *data;
}amil_variable_value_t;

/* function defination start. */
#define amil_string(str)	{ sizeof(str) -1, (u_char *) str }
#define amil_null_string	{0,NULL}
#define amil_str_set(str, text) \ (str)->len = sizeof(text) -1; (str)->data = (u_char *) text
#define amil_str_null(str)	(str)-> len = 0; (str)->data = NULL


#define amil_tolower(c) (u_char) ((c >= 'A' && c <= 'Z') ? (c | 0x20) : c)
#define amil_toupper(c) (u_char) ((c >= 'a' && c <= 'z') ? (c & ~0x20) : c)

void amil_strlow(u_char *dst, u_char *src, size_t n);

#define amil_strncmp(s1, s2, n) strncmp((const char *) s1, (const char *) s2, n)
#define amil_strcmp(s1, s2) strcmp((const char *) s1, (const char*) s2)

#define amil_member(buf, c, n) (void) memset(buf, c, n)

#define amil_memzero(buf, n) (void) memset(buf, 0, n)
#define amil_memset(buf, c, n) (void) memset(buf, c, n)


/* AMIL_MEMCPY_LIMIT */
#if (AMIL_MEMCPY_LIMIT)

void *amil_memcpy(void *dst, const void *src, size_t n);
#define amil_cpymem(dst, src, n) (((u_char *) amil_memcpy(dst, src, n))+(n))

#else

#define amil_memcpy(dst, src, n) (void) memcpy(dst, src, n)
#define amil_cpymem(dst, src, n) (((u_char *) memcpy(dst, src, n))+(n))

#endif




#if (__INTEL_COMPILER >= 800)



#else
#define amil_copy amil_cpymem
#endif


u_char *amil_cpystrn (u_char *dst, u_char *src, size_t n);
