#include <assert.h>
#include "showbytes.h"
#include <limits.h>

int int_size_is_32() {
	int set_msb = 1 << 31;
	int beyond_msb = set_msb << 1;

	return set_msb && !beyond_msb;
}

int int_size_is_32_for_16bit(){
	int set_smb = 1 << 15 << 15 << 1;
	int beyond_smb = set_smb << 1;
	return set_smb && !beyond_smb;
}

int main(int argc, char const *argv[])
{
	assert(int_size_is_32()==1);
	assert(int_size_is_32_for_16bit()==1);
	return 0;
}

