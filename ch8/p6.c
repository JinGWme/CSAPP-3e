// myecho, print parameters and envs
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char const *argv[])
{
	printf("Command line arguments:\n");
	for (size_t i = 0; i < argc; i++)
	{
		printf("argv[%d]: %s\n", i, argv[i]);
	}
	assert(argv[argc] == NULL);
	printf("Environment variables:\n");
	int cnt = 0;
	while (1)
	{
		const char *envp = argv[argc+cnt+1];
		if (envp == NULL)
		{
			return 0;
		}
		
		printf("envp[%d]: %s\n", cnt, envp);
		cnt++;
	}
	
}
