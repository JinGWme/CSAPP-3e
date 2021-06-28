#include <stddef.h>

void *malloc(size_t size);
void *memset(void *s, int c, size_t n);
void *calloc(size_t nmemb, size_t size)
{
	if (nmemb == 0 || size == 0)
	{
		return NULL;
	}

	int bytes = nmemb * size;
	if (bytes/size == nmemb)
	{
		// No overflow
		void *mem = malloc(bytes);
		memset(mem, 0, bytes);
		return mem;
	}
	return NULL;
	
}