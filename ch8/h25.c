#include <stdio.h>

char *tfgets(int size, FILE *stream);

int main(int argc, char const *argv[])
{
  printf("Input: %s", tfgets(60, stdin));
  return 0;
}
