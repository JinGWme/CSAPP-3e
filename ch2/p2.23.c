#include "showbytes.h"

int fun1(unsigned word){
	return (int)((word << 24) >> 24);
}

int fun2(unsigned word) {
	return((int)word << 24) >> 24;
}

int main(int argc, char const *argv[])
{
	unsigned a = 0x00000076;
	unsigned b = 0x87654321;
	unsigned c = 0x000000c9;
	unsigned d = 0xedcba987;

	show_int(fun1(a));
	show_int(fun2(a));
	show_int(fun1(b));
	show_int(fun2(b));
	show_int(fun1(c));
	show_int(fun2(c));
	show_int(fun1(d));
	show_int(fun2(d));
	printf("%d\n", fun2(d));

	unsigned short x = 0x0001;
	unsigned short y = 0x0002;
	unsigned short z = (x-y);
	short z1 = (x-y);
	show_short(z);
	show_short(z1);
	printf("%hi, %hu\n", z1, z);

	return 0;
}

