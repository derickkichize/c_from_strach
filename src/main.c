#include <thxio.h>
#include <thx_string.h>

void 
__test_02_buffjoin(void)
{

	char dst[255] = "Hello, ";
	char *src = "world";
	__x64_putsbuf(dst, src);

	thx_printf("%s", dst);
}

void 
__test_01_itoa(void)
{
	int number = 10;
	char buffer[255];

	__x64_itoa(0x5500a4, buffer, 16);
	thx_printf("hex: %s\n", buffer);

	memset(buffer, 0, strlen(buffer));
	__x64_itoa((void*) 10, buffer, 10);
	thx_printf("decimal: %s\n",buffer);

	memset(buffer, 0, strlen(buffer));
	__x64_itoa((void*) 42, buffer, 2);
	thx_printf("binary: %s\n",buffer);
}

void
__test_03_floats()
{
	thx_printf("%s %.2f\n","PI", 3.15);
	thx_printf("%s %.5f\n","Golden Ratio", 1.61803);
}

void
__test_02_stress()
{
	for (int i = 0; i < 100000; i++) 
		thx_printf("%p %x:%d \n", &i, i, i);
}

void
__test_01_printf()
{
	char *msg = "hi";
	int n = 1337;
	int sig_n = -15;

	thx_printf("Hello, %s %s! %p. %d %i char '%c'\n", 
		"world", "from c", &msg, n, sig_n, 'a'
	);

	thx_printf("Pointer %p.\n", &msg);
}

int 
main()
{
	__test_02_stress();
	__test_01_printf();
	__test_03_floats();
	__test_01_itoa();
}
