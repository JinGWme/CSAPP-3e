#include "showbytes.h"

unsigned replace_byte(unsigned x, int i, unsigned char b){
	return (x & ~(0xff<<i*8)) | (b<< i*8 );
}

int main(int argc, char const *argv[])
{
	show_int(0x12345678);
	show_int(replace_byte(0x12345678, 3, 0xab));
	show_int(replace_byte(0x12345678, 2, 0xab));
	show_int(replace_byte(0x12345678, 1, 0xab));
	show_int(replace_byte(0x12345678, 0, 0xab));
	return 0;
}
