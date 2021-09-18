#include "csapp.h"

unsigned int snooze(unsigned int secs)
{
	unsigned int left = sleep(secs);
	printf("Slept for %d of %d secs.\n", (secs-left), secs);
	return left;
}

void sigint_handler(int sig)
{
	printf("Ctrl+C\n");
}
int main(int argc, char const *argv[])
{
	if(argc != 2)
		exit(1);
	int sec = atoi(argv[1]);
	if (sec <= 0)
	{
		printf("Snooze more than 1 sec");
		exit(2);
	}
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
		unix_error("signal error");
	snooze(sec);
	
	return 0;
}
