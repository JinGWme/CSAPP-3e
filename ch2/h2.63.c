#include <limits.h>
#include "showbytes.h"

unsigned srl(unsigned x, int k) {
	/* Perform shift arithmetically */
	unsigned xsra = (int) x >> k;
	unsigned delta = ((int)x&INT_MIN)>>(k-1);
	return xsra - delta;
}

int sra(int x, int k) {
	/* Perform shift logically */
	int xsrl = (unsigned) x >> k;
	int delta = (x & INT_MIN) >> (k-1);
	return xsrl+delta;
}

int main(int argc, char const *argv[])
{
	show_int(UINT_MAX);
	show_int(srl(UINT_MAX, 2));
	show_int(INT_MAX);
	show_int(srl(INT_MAX, 2));

	show_int(UINT_MAX);
	show_int(sra(UINT_MAX, 2));
	show_int(INT_MIN);
	show_int(sra(INT_MIN, 3));
	return 0;
}

