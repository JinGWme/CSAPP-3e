#include <assert.h>

/*
 * Declaration of data type where 4 bytes are packed
 * into an unsigned
 */
typedef unsigned packed_t;

/* Extract byte from word. Return as signed integer */
int xbyte(packed_t word, int bytenum)
{
	int left_shift = (sizeof(int)-bytenum-1)<<3;
	word <<= left_shift;
	return (int)word >> 24;
}

int main(int argc, char const *argv[])
{
	assert(xbyte(0xff, 0) == 0xffffffff);
	assert(xbyte(0xff00, 0) == 0x0);
	assert(xbyte(0xff0000, 2) == 0xffffffff);
	assert(xbyte(0x110000, 2) == 0x11);
	return 0;
}
