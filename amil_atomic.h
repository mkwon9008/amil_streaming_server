/*	amil_atomic.h
*	This file is defination macro and Preprocessing of atomic functions.
*	<RULE>
*	1. Function is created as concise as possible.
*	2. If you must write a custom function before amil + underbar.
*	3. Function names are separated by a custom type + content + relevant work.
	   If needed, it may be written the use of the method object between custom type and content.
*	4. The macro statement is written in capital letters.
*/	

#ifndef AMIL_ATOMIC_HEADER_INCLUDE
#define AMIL_ATOMIC_HEADER_INCLUDE

#include <amil_conf.h>
#include <amil_core.h>

//if amil has libAtomic library.
#if (AMIL_HAVE_LIBATOMIC)

#define AO_REQUIRE_CAS
#include <atomic_ops.h>

#define AMIL_HAVE_ATOMIC_OPS 1


//Preprocessing varriable & defination statement.
typedef long 						amil_atomic_int_t;
typedef AO_t 						amil_atomic_uint_t;
typedef volatile amil_atomic_uint_t amil_atomic_t;

//Preprocessing macro defination.
#if (AMIL_PTR_SIZE == 8)
#define AMIL_ATOMIC_T_LEN	(sizeof("-9223372036854775808") - 1)
#else
#define AMIL_ATOMIC_T_LEN	(sizeof("-2147483648") - 1)
#endif 

/*	amil_atomic_fetch_add function is tells us about 
*	the patch histories of the atomic number of the function.
*	amil_atomic_t = defined by amil_atomic.h
*	amil_atomic_uint_t = defined by amil_atomic.h 
*/
static amil_inline amil_atomic_int_t amil_atomic_fetch_add(amil_atomic_t *value, amil_atomic_int_t add)
{
	amil_atomic_t old;
	old = *value;
	*value += add;

	return old;
}

#define amil_memory_barrier()
#define amil_cpu_parse()

