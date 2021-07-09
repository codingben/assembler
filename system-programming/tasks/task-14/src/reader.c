#include <stdio.h>
#include <string.h>
#include "parser.h"

int validate_extension(const char *filename)
{
    char *extension;
    char *ext = ".as"; /* TODO: Move to constants */

    extension = strrchr(filename, '.');

    if (strcmp(extension, ext) != 0)
    {
        return 1;
    }

    return 0;
}

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