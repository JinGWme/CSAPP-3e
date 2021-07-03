#include <limits.h>
#include <assert.h>
#include "showbytes.h"

int main(int argc, char const *argv[])
{
	int x = INT_MIN;
	show_int(x);
	show_int(-x);
	return 0;
}
