#include <stdio.h>

int is_little_endian() {
	short one = 0x1234;
	if ( (char)one == 0x34 )
	{
		return 1;
	}
	return 0;
	
}
int main(int argc, char const *argv[])
{
	printf("%d", is_little_endian());
	return 0;
}
