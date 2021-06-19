#include <assert.h>
int funcA(int x) {
	return x+1 == 0;
}

int funcB(int x) {
	return x+1 == 1;
}

int funcC(int x) {
	return (x&0xff) == 0xff;
}

int funcD(int x) {
	return (x>>(sizeof(int)-1)*8) == 0x00;
}

int main(int argc, char const *argv[])
{
	assert(funcA(-1) == 1);
	assert(funcA(29283) == 0);

	assert(funcB(0) == 1);
	assert(funcB(1928) == 0);

	assert(funcC(0xaeff) == 1);
	assert(funcC(0xaefe) == 0);

	assert(funcD(0x00123456) == 1);
	assert(funcD(0x01abcdef) == 0);
	return 0;
}
