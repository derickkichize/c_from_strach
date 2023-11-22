#ifndef _THX_TYPES_H_
#define _THX_TYPES_H_

#define _Addr long

typedef unsigned _Addr size_t;
typedef unsigned _Addr uintptr_t;

typedef	__builtin_va_list va_list;
#define va_start __builtin_va_start
#define va_end __builtin_va_end
#define va_copy __builtin_va_copy
#define va_arg __builtin_va_arg
 
typedef unsigned char bool;
#define true 1
#define false 0

#define NULL 0

#endif//_THX_TYPES_H_
