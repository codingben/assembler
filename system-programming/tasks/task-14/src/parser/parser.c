#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../constants/logger.h"
#include "../constants/messages.h"
#include "../line/line.h"
#include "../line/validator.h"

int parse_line(Line *line);

/* What it returns? */
void parse(const char *file_name, LinkedLine *linked_line)
{
    /* The goal is to parse all the lines for errors and print all of them */
    /* One error for each line is enough */

    Line *line = linked_line->head;

    int result = 0;
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

        result = parse_line(line);

        if (result == 1)
        {
            continue;
        }

        /* TODO: Collect errors before encoding to machine code */

        printf(LOG_LINE_FORMAT, file_name, line->line_number, line->text);
    }
}

int parse_line(Line *line)
{
    /* TODO: Parse syntax, and collect error(s) */
    /* TODO: Iterate here to get the column index */
    /* TODO: (Lexer) Break the line into words (e.g. word[0] = 'MOV', word[1] = "$1, *, ...) */
    /* TODO: (Lexer) Breaking the line can be done with checking for spaces between words. */
    /* TODO: Get a word like 'MOVAB' then you see that is not equal to 'MOV' (then throw an error) */
    /* TODO: When got ';' then remove it until reaches '\n' */
    /* TODO: Remove empty whitespaces? so in case the parser won't throw an error for 'MOV' != ' ' empty space */

    const char delim[1] = " ";
    char *token = strtok(copy_line(line), delim);

    while (token != NULL)
    {
        if (is_empty_line(*token))
        {
            line->statement_type = EMPTY;
            return 1;
        }

        if (is_comment_line(*token))
        {
            line->statement_type = EMPTY;
            return 1;
        }

        /* TODO: Add symbol table, what is IC? *
        /* TODO: Set other statement type */
        /* TODO: Set label */
        /* TODO: Set directive or command */
        /* TODO: Set registers */
        /* TODO: Make sure label has ":" and is no more than 31 characters ('\n' including) */
        /* TODO: The char ":" used to know the end of the label */
        /* TODO: After that, make sure label isn't command name or directive name */
        /* TODO: Check directives/commands and collect errors */

        token = strtok(NULL, delim);
    }

    return 0;
}
