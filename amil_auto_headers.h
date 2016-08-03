/*	amil_auto_header.h
*	This file is create check list of header file of standard library.
*	<RULE>
*	1. Function is created as concise as possible.
*	2. If you must write a custom function before amil + underbar.
*	3. Function names are separated by a custom type + content + relevant work.
	   If needed, it may be written the use of the method object between custom type and content.
*	4. The macro statement is written in capital letters.
*/	

//check start.
#ifndef AMIL_AUTO_HEADERS_HEADER_INCLUDED
#define AMIL_AUTO_HEADERS_HEADER_INCLUDED


#ifndef AMIL_HAVE_UNISTD_H
#define AMIL_HAVE_UNISTD_H 1
#endif

#ifndef AMIL_HAVE_INTTYPES_H
#define AMIL_HAVE_INTTYPES_H 1
#endif

#ifndef AMIL_HAVE_LIMITS_H
#define AMIL_HAVE_LIMITS_H 1
#endif

#ifndef AMIL_HAVE_SYS_PARAM_H
#define AMIL_HAVE_SYS_PARAM_H 1
#endif

#ifndef AMIL_HAVE_SYS_MOUNT_H
#define AMIL_HAVE_SYS_MOUNT_H 1
#endif

#ifndef AMIL_HAVE_SYS_STATVFS_H
#define AMIL_HAVE_SYS_STATVFS_H 1
#endif

#ifndef AMIL_HAVE_SYS_FILIO_H
#define AMIL_HAVE_SYS_FILIO_H 1
#endif

#ifndef AMIL_HAVE_CRYPT_H
#define AMIL_HAVE_CRYPT_H 1
#endif

#ifndef AMIL_LINUX
#define AMIL_LINUX 1
#endif

#ifndef AMIL_HAVESYS_PRCTL_H
#define AMIL_HAVESYS_PRCTL_H 1
#endif

#ifndef AMIL_HAVE_SYS_VFS_H
#define AMIL_HAVE_SYS_VFS_H 1
#endif


#endif