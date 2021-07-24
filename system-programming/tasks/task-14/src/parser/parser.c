#include <stdio.h>
#include <string.h>
#include "../constants/logger.h"
#include "../constants/messages.h"
#include "../line/line.h"

void parse(const char *file_name, LinkedLine *linked_line)
{
    /* The goal is to parse all the lines for errors and print all of them */
    /* One error for each line is enough */

    /* TODO: Parse syntax, and collect error(s) */
    /* TODO: Iterate here to get the column index */
    /* TODO: (Lexer) Break the line into words (e.g. word[0] = 'MOV', word[1] = "$1, *, ...) */
    /* TODO: (Lexer) Breaking the line can be done with checking for spaces between words. */
    /* TODO: Get a word like 'MOVAB' then you see that is not equal to 'MOV' (then throw an error) */
    /* TODO: When got ';' then remove it until reaches '\n' */
    /* TODO: Remove empty whitespaces? so in case the parser won't throw an error for 'MOV' != ' ' empty space */

    Line *line = linked_line->head;
    int i = 0;

    /* Should used for parsing */
    for (; line != NULL; line = line->next)
    {
        /* Iterate over saved line (the characters) */
        /* Use it to analyze the characters of the line (e.g. skip ";", etc) */
        for (i = 0; i < strlen(line->text) + 1; ++i)
        {
            /* TODO: Set has error (true or false) */
            /* TODO: Set error message */
            /* TODO: Set error column (error_column = i) */
        }

        printf(LOG_LINE_FORMAT, file_name, line->line_number, line->text);
    }
}
