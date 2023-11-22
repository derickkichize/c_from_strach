#include <thx_io.h>
#include <thx_string.h>

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

	thx_printf("Hello, %s %s! %p. %d %i char '%c' %.2f\n", "world", "from c", &msg, n, sig_n, 'a', 3.15);
	thx_printf("Pointer %p.\n", &msg);
}

void
__test_00()
{
	__test_02_stress();

	char buffer[255];
	thx_sprintf(buffer, "INSERT TABLE %s VALUE %.2f\n","PI", 3.15);
	thx_printf("%s\n",buffer);
	
	__test_01_printf();
	__test_03_floats();

	thx_fprintf(stderr, "_ERR: %s\n", buffer);
}

int 
main()
{
	__test_00();
	return -1;
}
