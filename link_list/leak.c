#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    char *buf = malloc(10);
    free(buf);

    buf = malloc(5);

    return 0;
}
