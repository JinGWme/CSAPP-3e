#include <fcntl.h>
#include "csapp.h"


int main(int argc, char const *argv[])
{
    int fd = Open("hello.txt", O_RDWR, S_IRWXU);
    
    struct  stat buf;
    Stat("hello.txt", &buf);

    int length = buf.st_size;

    char * txt = (char*)Mmap(NULL, length, PROT_WRITE, MAP_SHARED, fd, 0);

    txt[0] = 'J';

    // Close(fd);
    
    return 0;
}
