#include <limits.h>

int mul3div4(int x) 
{
	// *3
	int mul3 = x<<1+x;
	
	// /4, add a bias if negative
	int is_neg = x & INT_MIN;
	(is_neg && (x = x + (1<<2) -1));
	return x >> 2;
}

