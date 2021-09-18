#include <stdio.h>
#include "csapp.h"


int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("need a file name");
        exit(EXIT_FAILURE);
    }
    struct stat buffer;

    int fd = open(argv[1], O_RDONLY);
    stat(argv[1], &buffer);
    int length = buffer.st_size;
    printf("Open %s, get fd %d, size %d\n", argv[1], fd, length);
    


    void *c = Mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd, 0);

    Write(STDOUT_FILENO, c, length);

    return 0;
}
