#include <stdio.h>

int main(int argc, char **argv)
{
    int i;

    if (argc < 2)
    {
        printf("error: could not find a file to compile.\n");
        return 0;
    }

    for (i = 1; i < argc; ++i)
    {
        printf("file[%d]: %s\n", i, argv[i]);
    }

    return 0;
}