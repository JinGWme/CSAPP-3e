#include <stdio.h>

int main(int argc, char const *argv[])
{
	long lresult = 1;
	long result = 1;
	int n = 1;
	while (result/n == lresult)
	{
		lresult = result;
		result *=++n;
		printf("%d, %ld\n", n,result);
	}
	printf("%d\n", n);	
	return 0;
}
