/* $begin waitpid1 */
#include "csapp.h"
#define N 2

int main()
{
    int status, i;
    pid_t pid;

    /* Parent creates N children */
    for (i = 0; i < N; i++)                  //line:ecf:waitpid1:for
        if ((pid = Fork()) == 0) /* Child */ //line:ecf:waitpid1:fork
        {
            int *p = 0x400000;
            *p = 1;
        }
    // exit(100+i);                          //line:ecf:waitpid1:exit

    /* Parent reaps N children in no particular order */
    while ((pid = waitpid(-1, &status, 0)) > 0)
    {                          //line:ecf:waitpid1:waitpid
        if (WIFEXITED(status)) //line:ecf:waitpid1:wifexited
            printf("child %d terminated normally with exit status=%d\n",
                   pid, WEXITSTATUS(status)); //line:ecf:waitpid1:wexitstatus
        else if (WIFSIGNALED(status))
        {
            char msg[60];
            sprintf(msg, "child %d terminated abnormally with signal=%d", pid, WTERMSIG(status));
            // printf("child %d terminated abnormally with signal=%d: ", pid, WTERMSIG(status));
            psignal(WTERMSIG(status), msg);
        }
        else
            printf("child %d terminated abnormally with status=\n", pid);
    }

    /* The only normal termination is if there are no more children */
    if (errno != ECHILD) //line:ecf:waitpid1:errno
        unix_error("waitpid error");

    exit(0);
}
/* $end waitpid1 */
