#include <limits.h>
#include <assert.h>

/* Determine whether arguments can be subtracted without overflow */
int tsub_ok_my(int x, int y)
{
	int del = x - y;
	int mask = INT_MIN;

	int pos_over = !(x&mask)&&(y&mask)&&(del&mask);
	int neg_over = (x&mask)&&!(y&mask)&&!(del&mask);

  return !(pos_over || neg_over);
}

/* 抄来的方法，供参考 */
int tsub_ok(int x, int y)
{
	if (y == INT_MIN)
	{
		return 0;
	}

	int neg_y = -y;
	int sum = x + neg_y;
	int pos_over = x > 0 && neg_y > 0 && sum < 0;
	int neg_over = x < 0 && neg_y < 0 && sum >= 0;
	return !(pos_over|| neg_over);
}

int main(int argc, char const *argv[])
{
	assert(tsub_ok(1,2)==1);
	assert(tsub_ok(-1,INT_MAX)==1);
	assert(tsub_ok(-2,INT_MAX)==0);
	assert(tsub_ok(INT_MIN, 1) == 0);
	assert(tsub_ok(INT_MIN, 0) == 1);
	assert(tsub_ok(INT_MAX, -1) == 0);
	assert(!tsub_ok_my(0x00, INT_MIN));
	assert(tsub_ok_my(0x00, 0x00));
	return 0;
}
