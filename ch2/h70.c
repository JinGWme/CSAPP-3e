#include <assert.h>

/*
 * Return 1 when x can be represented as an n-bit, 2's-complement
 * number; 0 otherwise
 * Assume 1 <= n <= w
 */
int fits_bits(int x, int n) 
{
	/* 
	 * 只去掉n-1位，算术右移
	 * 如果是正数的话只留下x的最高位，在结果的最低位，可能是0或者1，其他位必然是0
	 * 如果是负数的话，只留下x的最高位（必然是1）， 移位的结果就是全1
	 */
	x >>= n - 1;
	/*
	 * If x > 0, x >> (n-1) >> 1 会剩下最高的w-n位，此时应该全为0，此时取NOT为1
	 * 如果 x < 0, ~x会是0， 此时取NOT为1
	 */
	return !(x>>1) || !~x;

}

int main(int argc, char const *argv[])
{
	assert(fits_bits(0xFF, 8));
	assert(!fits_bits(0xFFFFFF00, 8));
}
