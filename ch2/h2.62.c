#include <assert.h>

int int_shifts_are_arithmetic() {
	return (-1 >> 1) < 0;
}

int main(int argc, char const *argv[])
{
	assert(int_shifts_are_arithmetic() ==1);
	return 0;
}
