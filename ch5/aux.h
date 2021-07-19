#ifndef AUX_H
#define AUX_H 1
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void populate(float src[], long n)
{
	time_t t;
	srand((unsigned)time(&t));
	for (size_t i = 0; i < n; i++)
		src[i] = (float)rand()/((float)RAND_MAX);
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

// CPE is defined as cycle per element(#loops)
// The # of cycle in one sec is CLOCKS_PER_SEC
void get_cpe(clock_t begin, clock_t end, long loops)
{
	long time_spent = end - begin;
	long ticks_spent = ((double)time_spent/CLOCKS_PER_SEC)*(2.8*1000*1000*1000); // expected to run on 2.8Ghz G3900
	printf("ticks spent in excution %ld\n", ticks_spent);
	double cpe = ticks_spent/(double)loops;
	printf("CPE %lf\n",  cpe);
}
#endif