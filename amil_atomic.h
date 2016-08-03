
#ifndef AMIL_ATOMIC_HEADER_INCLUDE
#define AMIL_ATOMIC_HEADER_INCLUDE

#include <amil_conf.h>
#include <amil_core.h>


#if (AMIL_HAVE_LIBATOMIC)

#define AO_REQUIRE_CAS
#include <atomic_ops.h>

#define AMIL_HAVE_ATOMIC_OPS 1

typedef long 						amil_atomic_int_t;
typedef AO_t 						amil_atomic_uint_t;
typedef volatile amil_atomic_uint_t amil_atomic_t;

#if (AMIL_PTR_SIZE == 8)
#define AMIL_ATOMIC_T_LEN	(sizeof("-9223372036854775808") - 1)
#else
#define AMIL_ATOMIC_T_LEN	(sizeof("-2147483648") - 1)
#endif 

static amil_inline amil_atomic_int_t amil_atomic_fetch_add(amil_atomic_t *value, amil_atomic_int_t add)
{
	amil_atomic_t old;
	old = *value;
	*value += add;

	return old;
}

#define amil_memory_barrier()
#define amil_cpu_parse()

