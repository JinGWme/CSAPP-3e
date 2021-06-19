
#include <assert.h>
#include <limits.h>
#include <stdio.h>
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


int tadd_ok1(int x, int y){
    printf("x=%d, y=%d\n", x, y);
    int sum = x + y;
    int neg = x < 0 && y < 0 && sum >= 0;
    if(neg){
        printf("negative overflow, sum - x = %d \n", (sum-x));
    }
    int pos = x >= 0 && y >= 0 && sum < 0;
    if(pos){
        printf("positive overflow, sum - x = %d \n", (sum - x));
    }
    return !neg && !pos;
}

int tadd_ok2(int x, int y) {
	int sum = x + y;
	int neg_over = x < 0 && y < 0 && sum >= 0;
	int pos_over = x >= 0 && y >= 0 && sum < 0;
	return !neg_over && !pos_over;
}

int main(int argc, char const *argv[])
{
	assert(tadd_ok(1,2)==0);
	assert(tadd_ok(-1,-2)==0);
	assert(tadd_ok(-1,0)==0);
	assert(tadd_ok(INT_MAX, INT_MAX)==1);
	assert(tadd_ok(INT_MIN, INT_MIN+1)==1);
	assert(tadd_ok2(INT_MIN, INT_MIN)==1);
	// assert(tadd_ok(INT_MIN, INT_MIN) == 1);
	show_int(INT_MAX);
	show_int(-INT_MAX);
	show_int(-INT_MAX-1);
	// show_int(INT_MAX+INT_MAX);
	// show_int(INT_MIN);
	// show_int(INT_MIN+INT_MIN);

	return 0;
}
