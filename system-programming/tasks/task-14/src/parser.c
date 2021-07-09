#include <stdio.h>
#include <string.h>
#include "logger.h"

/* TODO: Make sure it's not 81 */
/* TODO: Move this define out of here */
#define MAX_LINE_LENGTH 80

int parse_line(const char *filename, char *line, int line_index)
{
    /* TODO: Syntax parser and error collector for output */
    /* TODO: Check syntax and then send to translator */
    /* TODO: Iterate here to get the column index */

    printf(LOG_FORMAT, filename, line_index, line);
    return 0;
}

int parse_file(FILE *file, const char *filename)
{
    char character;
    char line[MAX_LINE_LENGTH];
    int line_index = 1;

    do
    {
        character = fgetc(file);

        if (character == EOF || character == '\n')
        {
            /* line parser */
            parse_line(filename, line, line_index);

            /* clear line */
            memset(line, 0, sizeof(line));

            /* start reading next line */
            line_index++;
        }
        else
        {
            /* add character to line */
            strncat(line, &character, 1);
        }
    } while (character != EOF);

    return 0;
}