#include <thx_types.h>
#include <thx_io.h>

/*
 * thx_puts - output of a strings.
 *
 * Parameters:
 *	char *s - a pointer to a char
 */
void
thx_puts(char* s)
{
	while(*s) { thx_putc(s); s++; };
}

/*
 * thx_putc - output of characters and strings.
 *
 * Parameters:
 *	char *c - a pointer to a char
 */
void 
thx_putc(char* c)
{ __x64_syswrite(stdout, c, strlen(c)); }

/*
 * thx_printf_core - printf family base method.
 *
 * Prototype:
 *
 * static int thx_printf_core(
 *	unsigned int fd, 
 *	char* buf, 
 *	const char *fmt, 
 *	va_list ap)
 *
 * Paramenters:
 *	unsigned int fd - file descriptor  usedin: { fprintf }
 *	char* buf	- buffer	   usedin: { sprintf } 
 *	const char *fmt - format	   usedin: { printf, sprintf, fprintf} 
 *	va_list ap      - argument list    usedin: { printf, sprintf, fprintf} 
 *
 * Returns: void
 */
static int 
thx_printf_core(unsigned int fd, char* buf, const char *fmt, va_list ap)
{
	va_list argp;

	va_copy(argp, ap);

	long long int n;
	double f;

	char arg_buf[PRINTF_ARGBUF_MAX];

	int state  = 0;
	int f_pres = 0;
	int radix  = 10;

	memset(buf, 0, sizeof buf * sizeof(char*));
	while (*fmt != '\0')
	{
		if (*fmt == '%' || state == PRINTF_ARGUMENT_STATE)
		{
			++fmt;
			switch (*fmt)
			{
				case 's':
					char* str = va_arg(ap, char*);
					__x64_memcats((void*) buf, str);
					fmt++;
					break;
				case 'c':
					char c = va_arg(ap, int);
					__x64_memcatc(buf, c);
					fmt++;
					break;
				case 'i':
				case 'd':
					n = (int) va_arg(ap, int);
					radix = 10;
					__x64_itoa((void*) n, arg_buf, radix);
					__x64_memcats(buf, arg_buf);
					fmt++;
					break;
				case 'p':
					n = (uintptr_t) va_arg(ap, uintptr_t);
					radix = 16;
					__x64_itoa((void*) n, arg_buf, radix);
					__x64_memcats(buf, arg_buf);
					fmt++;
					break;
				case 'f':
					f = va_arg(ap, double);
					ftoa(f, arg_buf, (f_pres) ? f_pres : 6); 
					__x64_memcats((void*) buf, arg_buf);
					state = PRINTF_NORMAL_STATE;
					fmt++;
					break;
				case 'x':
					n = (unsigned int) va_arg(ap, int);
					radix = 16;
					__x64_itoa((void*) n, arg_buf, radix);
					__x64_memcats(buf, arg_buf);
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
		else { __x64_memcatc(buf,(char)*fmt); fmt++; }

	}

	va_end(argp);
	if (fd != NULL) 
	{
		__x64_syswrite(fd, buf, strlen(buf));
		memset(buf, 0, PRINTF_FMTBUF_MAX);
	}

	return (strlen(buf));
}



/*
 * thx_printf - format and print data.
 *
 * Prototype:
 *	int  thx_printf(const char *fmt, ...).
 *
 * Paramenters:
 *	const char* fmt  - format specification.
 *	va_list     ...  - values to pass on formated output.
 *
 * Returns: void
 */
void
thx_printf (const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	char buf [PRINTF_FMTBUF_MAX];
	thx_printf_core(stdout, buf, fmt, ap);

	va_end(ap);

}

/*
 * thx_fprintf - formatted output conversion
 *
 * Prototype:
 *	int  thx_sprintf(unsigned in fd, const char *fmt, ...).
 *
 * Paramenters:
 *	unsigned int fd  - file descriptor to print data.
 *	const char* fmt  - format specification.
 *	va_list     ...  - values to pass on file descriptor.
 *
 * Returns: written size.
 */
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

/*
 * thx_sprintf - formatted output conversion
 *
 * Prototype:
 *	int  thx_sprintf(char*, const char *fmt, ...).
 *
 * Paramenters:
 *	char* buf        - destination buffer.
 *	const char* fmt  - format specification.
 *	va_list     ...  - values to pass on destination buffer.
 *
 * Returns: written size.
 */
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

/*
 * thx_sscanf - input string format conversion
 *
 * Prototype:
 *	static void thx_sscanf_getstr(char *dst, const char *src, int* p_n, char c_end);
 *
 * Paramenters:
 *	char *dst  - destination buffer.
 *	char *src  - source buffer.
 *	int  *p_n  - buffer char position.
 *	char c_end - character before sscanf format symbol example %s, c_end = ','.
 * Returns: void
 */
static void
thx_sscanf_getstr(char *dst, const char* src, int* p_n, char c_end)
{
	int  pos  = *p_n;
	int  size =  (sizeof src * sizeof (char*));
	int  i = 0;
	char c;

	while (1)
	{
		c = *(src + pos);
		if (c == c_end || pos == size) break;

		*(dst + i) = c;
		i++;
		pos++;
	}

	if (*(dst + i) != '\0') *(dst + i) = '\0';

	*p_n = pos;
}

/*
 * thx_sscanf - input string format conversion
 *
 * Prototype:
 *	thx_sscanf(char *buffer, const char *format, ...);
 *
 * Paramenters:
 *	char* buf - source buffer for data extraction
 *	const char* fmt
 *
 * Returns: void
 */

void
thx_sscanf(char* buf, const char* fmt, ...)
{
	va_list ap;
	int	p = 0;
	char	nbuf[128];
	char*   sbuf;
	int*    n;
	float*  f;

	memset (nbuf, 0, sizeof nbuf);
	va_start(ap, fmt);

	while (*fmt != '\0')
	{
		if (*fmt == '%')
		{
			++fmt;
			switch (*fmt)
			{
				case 's':
					sbuf = va_arg(ap, char*);
					thx_sscanf_getstr(sbuf, buf, &p, *(fmt + 1));
					fmt++;
					break;
				case 'i':
				case 'd':
					n = va_arg(ap, int*);
					thx_sscanf_getstr(nbuf, buf, &p, *(fmt + 1));
					*n = __x64_atoi(nbuf);
					fmt++;
					break;
				case 'f':
					f = (float*) va_arg(ap, double*);
					thx_sscanf_getstr(nbuf, buf, &p, *(fmt + 1));
					*f = (float) __x64_atof(nbuf);
					fmt++;
					break;
				case 'x':
					n = va_arg(ap, int*);
					thx_sscanf_getstr(nbuf, buf, &p, *(fmt + 1));
					*n = __x64_atoh(nbuf);
					fmt++;
				break;
			}
		} 
		else { fmt++; p++; }
	}
	va_end(ap);
}
