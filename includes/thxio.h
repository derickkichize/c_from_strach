#ifndef _THXIO_H_
#define _THXIO_H_

#include <thx_types.h>
#include <thx_string.h>

//#define stdin  0x0
//#define stdout 0x1
//#define stderr 0x2

extern void  __x64_itoa    (void*, char*, int);
extern void* __x64_putsbuf (void*, void*);
extern void* __x64_putcbuf (void*, char);
extern void  __x64_putstr  (const char*);

#define PRINTF_BUF_MAX 4096
#define PRINTF_ARGBUF_MAX 128

#define PRINTF_ARGUMENT_STATE 1
#define PRINTF_NORMAL_STATE 0
void thx_printf(const char *fmt, ...);

#endif//_THXIO_H_
