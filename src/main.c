#include <thx_io.h>

void
__test_03_floats()
{
	thxio.printf("%s %.2f\n","PI", 3.15);
	thxio.printf("%s %.5f\n","Golden Ratio", 1.61803);
}

void
__test_02_stress()
{
	for (int i = 0; i < 100000; i++) 
		thxio.printf("%p %x:%d \n", &i, i, i);
}

void
__test_01_printf()
{
	char *msg = "hi";
	int n = 1337;
	int sig_n = -15;

	thxio.printf("Hello, %s %s! %p. %d %i char '%c' %.2f\n", "world", "from c", &msg, n, sig_n, 'a', 3.15);
	thxio.printf("Pointer %p.\n", &msg);
}

void
__test_00()
{
	__test_02_stress();

	char buffer[255];
	thxio.sprintf(buffer, "INSERT TABLE %s VALUE %.2f\n","PI", 3.15);
	thxio.printf("%s\n",buffer);
	thxio.fprintf(stdout, "FPRINTF: %s\n", buffer);
}

void
__test_scanf()
{
	char *str = "Hello, World -1337 PI: 3.15 NEGATIVE_F: -3.15 0x100";
	char buf1[32];
	int   n;
	int   h;
	float f;
	float f2;

	thxio.sscanf(str, "Hello, %s %d PI: %f NEGATIVE_F: %f %x", buf1, &n, &f, &f2, &h);
	thxio.printf("%s %d %.2f,%.4f %x\n", buf1, n, f, f2, h);
}

int 
main()
{
	__test_02_stress();
	__test_00();
	__test_01_printf();
	__test_03_floats();
	__test_scanf();
	return 0;
}
