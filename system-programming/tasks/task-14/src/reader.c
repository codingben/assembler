#include <stdio.h>
#include "parser.h"

void read_file(const char *filename)
{
    /* Open the source file with the ".c" extension (e.g. prnt.c). */
    FILE *file = fopen(filename, "r");

    /* If something is wrong then print the error message. */
    if (file != NULL)
    {
        /* Check syntax and then send to translator */
        parse_file(file, filename);

        /* Close file after parsing */
        fclose(file);
    }
    else
    {
        perror("Unable to open file");
    }
}