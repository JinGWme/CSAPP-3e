#include <stdio.h>
int main(int argc, char const *argv[])
{
	printf("%x\n", -2147483647);
	printf("%x\n", 2147483647);
	printf("%x\n", -2147483647-1U);
	printf("%d\n", -2147483647-1U < 2147483647 );
	return 0;
}
