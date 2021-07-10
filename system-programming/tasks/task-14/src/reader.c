#include <stdio.h>
#include "constants.h"
#include "parser.h"

void read_file(const char *filename)
{
    FILE *file = fopen(filename, "r");

    if (file != NULL)
    {
        parse_file(file, filename);
        fclose(file);
    }
    else
    {
        perror(FAILED_OPEN_FILE);
    }
}