#include <assert.h>
#include <stdio.h>

/* Return 1 when x contains an odd number of 1s;
   0 otherwise
	 Assume w = 32 */
int odd_ones_my(unsigned x) {
	unsigned cnt = 0;
	for (size_t i = 0; i < 32; i++)
	{
		if ( (x >> i) & 0x1)
		{
			cnt++;
		}
	}
	return cnt & 0x1;
}


int odd_ones(unsigned x) {
	// 将x的每一位和他的前一位异或，结果表达了这两位中有多少个1
	// 如果结果是0，说明有偶数个1
	// 如果结果是1，说明有基数个1
	// 结果存放在每个偶数位中(0,2,4,6,8,10,12...30) 共16个
	x ^= (x>>1);
	
	// 此时只考虑偶数位了，因为偶数已经表达了和他之前的奇数位的1的个数
	// 此时计算的结果是每四个位中的1有多少个
	// 如果有偶数个1，结果是0
	// 如果有奇数个1，结果是1，这是由异或的运算决定的
	// 结果存放在位数可以被4整除的位上(0,4,8,12,16,20,24,28) 共8个
	x ^= (x>>2);

	// 此时只考虑可以整除4的位数，结果存放在可以被8整除的位上(0,8,16,24) 共4个
	// 每个对应位上的结果表明之前的8个位中是否有奇数个1
	x ^= (x>>4);

	// 结果存放在可以被16整除的位上(0,16) 共2个
	x ^= (x>>8);

	// 最终结果存放在可以被32 整除的位上（0）
	x ^= (x>>16);

	return x&1;
}

int main(int argc, char const *argv[])
{
	assert(odd_ones(0x0)==0);
	assert(odd_ones(0x1)==1);
	assert(odd_ones(0x2)==1);
	assert(odd_ones(0x3)==0);
	assert(odd_ones(0x3333) == 0);
	assert(odd_ones(0x3433) == 1);
	return 0;
}
