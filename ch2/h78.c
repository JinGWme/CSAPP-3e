#include <limits.h>

/* Divide by power of 2. Assume 0 <= k < w -1 */
int divide_power2(int x, int k)
{
	int is_neg = x & INT_MIN;
	// 对于有符号数除以2的幂，在被除数是负数的时候需要加上一个预置偏移
	// 这样才能在被除数为负的时候试先向上舍入
	// 这种行为的目的是无论被除数是正数还是负数都可以实现向0舍入
	(is_neg && (x = x + (1 << k) -1));
	return x >> k; 
}