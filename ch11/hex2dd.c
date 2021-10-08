#include "csapp.h"
int main(int argc, char const *argv[])
{
    char dst[16];
    struct in_addr src;
    src.s_addr = 0;

    if (argc != 2)
    {
        printf("Usage: ./hex2dd <hex-ip-addr>");
        return -1;
    }
    src.s_addr = strtol(argv[1], NULL, 16);

    inet_ntop(AF_INET, &src, dst, 16);

    printf("%s\n", dst);

    return 0;
}

