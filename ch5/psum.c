#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000000
float source[N];
float target[N];
void psum1(float a[], float p[], long n)
{
	long i;
	p[0] = a [0];
	for ( i = 1; i < n; i++)
		p[i] = p[i-1] + a[i];
}

void psum2(float a[], float p[], long n)
{
	long i;
	p[0] = a[0];
	for (i = 1; i < n; i+=2)
	{
		float mid_val = p[i-1] + a[i];
		p[i] = mid_val;
		p[i+1] = mid_val + a[i+1];
	}
	if (i < n)
		p[i] = p[i-1] + a[i];	
}

void populate(float src[], long n)
{
	time_t t;
	srand((unsigned)time(&t));
	for (size_t i = 0; i < n; i++)
		source[i] = (float)rand()/((float)RAND_MAX);
}
void dump(float src[], long n)
{
	printf("Dumping float array\n");
	for (size_t i = 0; i < n; i++)
	{
		printf("%f\t", src[i]);
	}
	printf("\n");
}
int main(int argc, char const *argv[])
{
	long loops = 0;
	if (argc != 2)
	{
		printf("Need loop count");
		return 0;
	}
	else
	{
		loops = atol(argv[1]);
	}
	
	populate(source, loops);
	clock_t begin = clock();
	psum1(source, target, loops);
	clock_t end = clock();
	long time_spent = end - begin;
	printf("%ld", time_spent);
	return 0;
}
 