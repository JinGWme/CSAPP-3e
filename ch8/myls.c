#include <stdio.h>
#include <unistd.h>
extern char **environ;

int main(int argc, char const *argv[])
{
	execve("/usr/bin/ls", argv, environ);
}
