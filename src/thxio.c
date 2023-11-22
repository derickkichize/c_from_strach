#include <thx_types.h>
#include <thx_io.h>
#include <thx_syscall.h>

void 
thx_printf(const char *fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);

	long long int n;
	double f;
	char buf[PRINTF_BUF_MAX];
	char arg_buf[PRINTF_ARGBUF_MAX];

	int  state = 0;
	int  radix = 10;
	int  f_pres = 0;

	while(*fmt != '\0')
	{
		if (*fmt == '%' || state == PRINTF_ARGUMENT_STATE)
		{
			++fmt;
			switch(*fmt)
			{
				case 's':
					char* str = va_arg(argp, char*);
					__x64_putsbuf((void*) buf, str);
					fmt++;
					break;
				case 'c':
					char c = va_arg(argp, int);
					__x64_putcbuf(buf, c);
					fmt++;
					break;
				case 'i':
				case 'd':
					n = (int) va_arg(argp, int);
					radix = 10;
					__x64_itoa((void*) n, arg_buf, radix);
					__x64_putsbuf(buf, arg_buf);
					fmt++;
					break;
				case 'p':
					n = (uintptr_t) va_arg(argp, uintptr_t);
					radix = 16;
					__x64_itoa((void*) n, arg_buf, radix);
					__x64_putsbuf(buf, arg_buf);
					fmt++;
					break;
				case 'f':
					f = va_arg(argp, double);
					ftoa(f, arg_buf, (f_pres) ? f_pres : 6); 
					__x64_putsbuf((void*) buf, arg_buf);
					state = PRINTF_NORMAL_STATE;
					fmt++;
					break;
				case 'x':
					n = (unsigned int) va_arg(argp, int);
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
			__x64_putcbuf(buf,  (char)*fmt);
			fmt++;
		}

	}

	__x64_putstr(buf);

	memset(buf, 0, PRINTF_BUF_MAX);
	va_end(argp);
}
