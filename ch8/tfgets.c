#include <stdio.h>
#include "csapp.h"

jmp_buf buf;

void sigalrm_handler(int s)
{
  Sio_puts("SIGALRM received\n");
  longjmp(buf, 1);
}

char *tfgets(int size, FILE *stream)
{
  switch (setjmp(buf))
  {
  case 0:
    Signal(SIGALRM, sigalrm_handler);
    alarm(5);
    char *msg = (char*)Malloc(size+1);
    return fgets(msg, size, stream);
    break;
  case 1:
    printf("Returned from longjmp\n");
    return NULL;
  
  }
}