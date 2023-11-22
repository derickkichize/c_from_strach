#include <thx_types.h>
#include <thx_io.h>

void
thx_puts(char* s)
{
	while(*s)
	{ thx_putc(s); s++; };
}

void 
thx_putc(char* c)
{ __x64_syswrite(stdout, c, 1); }

static int 
thx_printf_core(unsigned int fd, char* buf, const char *fmt, va_list ap)
{
	va_list argp;

	va_copy(argp, ap);

	long long int n;
	double f;

	char arg_buf[PRINTF_ARGBUF_MAX];

	int    state = 0;
	int    radix = 10;
	int    f_pres = 0;

	memset(buf, 0, sizeof buf * sizeof(char*));
	while(*fmt != '\0')
	{
		if (*fmt == '%' || state == PRINTF_ARGUMENT_STATE)
		{
			++fmt;
			switch(*fmt)
			{
				case 's':
					char* str = va_arg(ap, char*);
					__x64_putsbuf((void*) buf, str);
					fmt++;
					break;
				case 'c':
					char c = va_arg(ap, int);
					__x64_putcbuf(buf, c);
					fmt++;
					break;
				case 'i':
				case 'd':
					n = (int) va_arg(ap, int);
					radix = 10;
					__x64_itoa((void*) n, arg_buf, radix);
					__x64_putsbuf(buf, arg_buf);
					fmt++;
					break;
				case 'p':
					n = (uintptr_t) va_arg(ap, uintptr_t);
					radix = 16;
					__x64_itoa((void*) n, arg_buf, radix);
					__x64_putsbuf(buf, arg_buf);
					fmt++;
					break;
				case 'f':
					f = va_arg(ap, double);
					ftoa(f, arg_buf, (f_pres) ? f_pres : 6); 
					__x64_putsbuf((void*) buf, arg_buf);
					state = PRINTF_NORMAL_STATE;
					fmt++;
					break;
				case 'x':
					n = (unsigned int) va_arg(ap, int);
					radix = 16;
					__x64_itoa((void*) n, arg_buf, radix);
					__x64_putsbuf(buf, arg_buf);
					fmt++;
					break;
				case '.':
					++fmt;
					f_pres = atoi(*fmt);
					fmt--;
					state = PRINTF_ARGUMENT_STATE;
					break;
				break;
			}

			memset(arg_buf, 0, PRINTF_ARGBUF_MAX);
		} 
		else 
		{
			__x64_putcbuf(buf,(char)*fmt);
			fmt++;
		}

	}

	va_end(argp);
	if (fd != NULL) 
	{
		__x64_syswrite(fd, buf, strlen(buf));
		memset(buf, 0, PRINTF_FMTBUF_MAX);
	}

	return (strlen(buf));
}



void
thx_printf(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	char buf [PRINTF_FMTBUF_MAX];
	thx_printf_core(stdout, buf, fmt, ap);

	va_end(ap);

}

int
thx_fprintf(unsigned int fd, const char *fmt, ...)
{
	va_list ap;
	size_t  ret;

	va_start(ap, fmt);

	char buf [PRINTF_FMTBUF_MAX];
	ret = thx_printf_core(fd, buf, fmt, ap);

	va_end(ap);
	return ret;
}

int 
thx_sprintf(char * buf, const char *fmt, ...)
{
	va_list ap;
	size_t  ret;

	va_start(ap, fmt);

	memset(buf, 0, sizeof buf * sizeof (char*));
	ret = thx_printf_core(NULL, buf, fmt, ap);

	va_end(ap);
	return ret;
}
