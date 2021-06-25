#include <assert.h>
/*
 * Generate mask indicating left most 1 in x. Assume w = 32.
 * For example 0xff00 -> 0x8000, and 0x6600 -> 0x 4000.
 * If x = 0 then return 0
 */
int leftmost_one(unsigned x){
	// 用第一个1通过移位+或运算使它后面都变成1
	// 由于确定了是32位，所以我们可以通过确定次数的位移实现

	// 第一个1位将它右边的位不管原来是什么变成了1
	// 现在获得了11的两位
	x |= x>>1;

	// 从第一个1位开始的四维都变成了1， 获得了1111
	x |= x>>2;

	// 以此类推
	x |= x>>4;
	x |= x>>8;

	//由于确定了32位，我们最多移位16就可以确保全面覆盖
	// 最差的情况是最高位是1
	x |= x>>16;

	// ~x >> 1 和x只在最高位上同样是1
	return x & (~x>>1);
}

int main(int argc, char const *argv[])
{
	assert(leftmost_one(0xff00) == 0x8000);
	assert(leftmost_one(0x5555) == 0x4000);
	return 0;
}
