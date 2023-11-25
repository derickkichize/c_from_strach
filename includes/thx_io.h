#ifndef _THXIO_H_
#define _THXIO_H_

#include <thx_types.h>
#include <thx_string.h>
#include <thx_syscall.h>

#define stdin  0x0
#define stdout 0x1
#define stderr 0x2

extern void   __x64_itoa    (void*, char*, int);
extern int    __x64_atoi    (char*);
extern double __x64_atof    (char*);
extern int    __x64_atoh    (char*);
extern void*  __x64_memcats (void*, void*);
extern void*  __x64_memcatc (void*, char);

void thx_putc(char* c);
void thx_puts(char* s);

#define PRINTF_FMTBUF_MAX     4096
#define PRINTF_ARGBUF_MAX     128
#define PRINTF_ARGUMENT_STATE 1
#define PRINTF_NORMAL_STATE   0

void thx_printf (const char* fmt, ...);
int  thx_sprintf(char*          , const char* fmt, ...);
int  thx_fprintf(unsigned int   , const char* fmt, ...);

#define SSCANF_START_STATE 0
#define SSCANF_ARGUMENT_STATE 1
void thx_sscanf (char*, const char* fmt, ...);

struct thxio_
{
	void* (*printf)    (const char *, ...);
	void* (*sprintf)   (char*       , const char *, ...);
	void* (*fprintf)   (unsigned int, const char *, ...);
	void* (*sscanf)    (char*       , const char *, ...);
}; 

static struct thxio_ thxio = { 
	.printf  = (void*) thx_printf,
	.sprintf = (void*) thx_sprintf,
	.fprintf = (void*) thx_fprintf,
	.sscanf  = (void*) thx_sscanf
};

#endif//_THXIO_H_
