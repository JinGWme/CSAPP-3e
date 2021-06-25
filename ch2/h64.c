#include <assert.h>
#include "showbytes.h"

/* Return 1 when any odd bit of x equals 1;
   0 otherwise. Assume w=32 */
int any_odd_one(unsigned x) {
	unsigned mask = 0xaaaaaaaa;
	return (mask & x) != 0;
}

int main(int argc, char const *argv[])
{
	int a = 0xabcdef;
	assert(any_odd_one(0x0)==0);
	assert(any_odd_one(0x1)==0);
	assert(any_odd_one(0x2)==1);
	assert(any_odd_one(0x5)==0);
	assert(any_odd_one(0xa)==1);
	assert(any_odd_one(0xb)==1);
	return 0;
}
 