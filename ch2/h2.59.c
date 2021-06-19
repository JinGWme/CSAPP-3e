#include <stdio.h>
#include "showbytes.h"

int combine(int x, int y){
	return (x&0xff)|(y&~0xff);
}

int main(int argc, char const *argv[])
{
	show_int(combine(0x89abcdef, 0x76543210));
	return 0;
}
