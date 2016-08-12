

/*	amil_conf_file.h
*	This file is definition macro and Preprocessing of config file functions.
*	<RULE>
*	1. Function is created as concise as possible.
*	2. If you must write a custom function before amil + underbar.
*	3. Function names are separated by a custom type + content + relevant work.
	   If needed, it may be written the use of the method object between custom type and content.
*	4. The macro statement is written in capital letters.
*/	

#ifndef AMIL_CONFIG_FILE_HEADER_INCLUDED
#define AMIL_CONFIG_FILE_HEADER_INCLUDED 


#define AMIL_CONF_ERROR (void *) -1

#define AMIL_MAX_CONF_ERRSTR 1024

typedef uintptr_t       ngx_uint_t;

typedef struct 
{
	amil_str_t name;
	amil_uint_t value;
} amil_conf_enum_t;
