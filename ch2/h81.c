#include <limits.h>
#include <assert.h>

int funcA(int k)
{
	int w = sizeof(int)<<3;
	int x = INT_MIN;
	return x >> (w-k-1);
}

int funcB(int k, int j)
{
	int w = sizeof(int)<<3;
	int x = INT_MIN;
	x >>= (k-1);
	return (unsigned)x >> (w-k-j);
}

int main(int argc, char const *argv[])
{
	assert(funcA(8) == 0xffffff00);
	assert(funcA(9) == 0xfffffe00);
	assert(funcB(8,8) == 0x0000ff00);
	return 0;
}

