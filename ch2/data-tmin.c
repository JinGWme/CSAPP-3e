#include <stdio.h>

int main(int argc, char const *argv[])
{
	int dpos32 = (-2147483648 >0);
	int hpos32 = (0x80000000 > 0);
	printf("%u, %u\n", dpos32, hpos32);
	return 0;
}
