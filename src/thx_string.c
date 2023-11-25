#include <thx_string.h>

long unsigned int strlen(const char *s)
{
	int i = 0;
	while(*s) 
	{ i++; s++; }
	return i;
}


void* 
memset(void * dst, int c, size_t n)
{
	return __x64_memset(dst, c, n); 
}

int
atoi(char c)
{ 
	int n = c - '0'; 
	return n; 
}


void
ftoa(float n, char* buf, int pres)
{
	char dec_buf[128];
	char frac_buf[128];
	int radix = 10;
	int f;
	int d = (int) n;
	float frac = d - (float) n;

	while (pres != 0)
	{ frac *= 10; pres--; }

	memset(dec_buf,  0, (sizeof dec_buf));
	memset(frac_buf, 0, (sizeof dec_buf));
	memset(buf,      0, (sizeof buf));


	if (frac < 0) f = (unsigned int) frac * -1;
	else          f = (unsigned int) frac;

	__x64_itoa((void*)(uintptr_t) d, dec_buf, radix);
	__x64_itoa((void*)(uintptr_t) f, frac_buf, radix);
	__x64_memcats((void*) buf, dec_buf);
	__x64_memcatc(buf, '.');
	__x64_memcats((void*) buf, frac_buf);
}
