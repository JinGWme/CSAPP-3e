#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "aux.h"

void psum1(float a[], float p[], long n)
{
	long i;
	p[0] = a [0];
	for ( i = 1; i < n; i++)
		p[i] = p[i-1] + a[i];
}

int main(int argc, char const *argv[])
{
	long loops = 0;
	if (argc != 2)
	{
		printf("Need loop count");
		return -1;
	}
	else
	{
		loops = atol(argv[1]);
	}
	if (loops < 1000)
	{
		printf("Allow more elements to get accurate CPE");
		return -1;
	}
	
	float source[loops];
	float target[loops];
	
	populate(source, loops);
	clock_t begin = clock();
	psum1(source, target, loops);
	clock_t end = clock();
	// dump(source, loops);
	// dump(target, loops);
	get_cpe(begin, end, loops);

	return 0;
}
 