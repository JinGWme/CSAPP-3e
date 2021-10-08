
#include "csapp.h"

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./hex2dd <hex-ip-addr>");
        return -1;
    }

    struct in_addr dst;
    unsigned int tmp;

    Inet_pton(AF_INET, argv[1], &tmp);
    dst.s_addr = ntohl(tmp);

    printf("0x%x\n", dst.s_addr);
    return 0;
}
