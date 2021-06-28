#include <limits.h>
#include <assert.h>
#include "showbytes.h"

/* Addtiona that saturates to TMin or TMax */
int saturating_add(int x, int y)
{
	int mask = INT_MIN;
	int sum = x + y;

	int pos_overflow = !(x&mask) &&!(y&mask) && (sum&mask);
	int neg_overflow = (x&mask) && (y&mask) && !(sum&mask);
	show_int(x);
	show_int(y);
	show_int(sum);
	show_int(pos_overflow);
	show_int(neg_overflow);
	(pos_overflow && (sum = INT_MAX)) || (neg_overflow && (sum = INT_MIN));
	return sum;
}

int main(int argc, char const *argv[])
{
	assert(saturating_add(1,2) == 3);

	assert(saturating_add(INT_MIN, -0x1) == INT_MIN);

	assert(saturating_add(INT_MAX, 0x1) == INT_MAX);
	return 0;
}
