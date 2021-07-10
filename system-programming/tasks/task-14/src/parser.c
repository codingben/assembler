#include <stdio.h>
#include <string.h>
#include "constants.h"
#include "logger.h"

int parse_line(const char *filename, char *line, int line_index)
{
    /* TODO: Analyze syntax, and collect error(s) */
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
            /* Line parser */
            parse_line(filename, line, line_index);

            /* Clear line */
            memset(line, 0, sizeof(line));

            /* Go to next line */
            line_index++;
        }
        else
        {
            /* Add character to line */
            strncat(line, &character, 1);
        }
    } while (character != EOF);

    return 0;
}

int parse(const char *filename)
{
    FILE *file = fopen(filename, "r");

    if (file != NULL)
    {
        /* Parse file to analyze syntax */
        parse_file(file, filename);

        /* Close file after parsing */
        fclose(file);
    }
    else
    {
        perror(FAILED_OPEN_FILE);
    }

    return 0;
}