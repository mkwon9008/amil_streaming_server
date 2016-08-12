/*	amil_linux.h
*	This file is definition macro and struct and Preprocessing in linux environment.
*	<RULE>
*	1. Function is created as concise as possible.
*	2. If you must write a custom function before amil + underbar.
*	3. Function names are separated by a custom type + content + relevant work.
*	   If needed, it may be written the use of the method object between custom type and content.
*	4. The macro statement is written in capital letters.
*/	

#ifndef AMIL_LINUX_HEATHER_INCLUDED
#define AMIL_LINUX_HEATHER_INCLUDED

amil_chain_t *amil_linux_sendfile_chain(amil_connection_t *c, amil_chain_t *in, off_t limit);

#endif