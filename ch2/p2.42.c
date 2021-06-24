#include <assert.h>
int div16(int x) {
	int bias = (x>>31)&0xf;
	return (x+bias) >> 4;
}

int main(int argc, char const *argv[])
{
	assert(div16(16) == 1);
	assert(div16(-16) == -1);
	assert(div16(-15) == 0);
	assert(div16(15) == 0);
	assert(div16(31) == 1);
	assert(div16(-31) == -1);

	return 0;
}
