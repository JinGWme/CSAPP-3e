#include <assert.h>
#include <limits.h>
#include "showbytes.h"
int tadd_ok(int x, int y) {
	int z = x + y;
	if (x > 0 && y > 0 && z < 0) {
		return 1;
	}
	if (x < 0 && y < 0 && z > 0)
	{
		return 1;
	}
	if (x == INT_MIN && y == INT_MIN)
	{
		return 1;
	}
	
	return 0;	
}
int tsub_ok(int x, int y) {
	return tadd_ok(x, -y);
}
int main(int argc, char const *argv[])
{
	assert(tsub_ok(1,1)==0);
	assert(tsub_ok(INT_MAX ,INT_MAX) == 0);
	assert(tsub_ok(INT_MIN, INT_MIN)==1);
	assert(tsub_ok(INT_MAX, INT_MIN) == 1);
	show_int(INT_MIN);
	show_int(-INT_MIN);
	return 0;
}