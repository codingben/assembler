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

        if (parse_line(line) == 1)
        {
            /* Print errors here (if have) */
            continue;
        }

        /* TODO: Collect errors before encoding to machine code */
        /* printf(LOG_LINE_FORMAT, file_name, line->line_number, line->text); */

        printf("Command: %s\n", line->command);
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
    char *copied_line = copy_line(line);
    char *token = strtok(copied_line, delim);

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

        /* TODO: Check for entry or extern */

        if (is_label(token) == 1)
        {
            if (is_label_above_max_length(token) == 1)
            {
                /* TODO: Add error here */
                return 1;
            }

            if (is_label_equals_command(token) == 0)
            {
                /* TODO: Add error here */
                return 1;
            }

            if (is_label_equals_directive(token) == 0)
            {
                /* TODO: Add error here */
                return 1;
            }

            memcpy(line->label, token, strlen(token) + 1);
        }
        else
        {
            if (is_command(token) == 0)
            {
                memcpy(line->command, token, strlen(token) + 1);
            }
            else if (is_directive(token) == 0)
            {
                memcpy(line->directive, token, strlen(token) + 1);
            }
            else
            {
                /* TODO: Add error here, "invalid syntax" */
            }
        }

        /* TODO: Add symbol table, what is IC? */
        /* TODO: Set other statement type */
        /* TODO: Set directive or command */
        /* TODO: Set registers */
        /* TODO: Check directives/commands and collect errors */
        /* TODO: Make better return types, no 0 or 1 */

        token = strtok(NULL, delim);
    }

    free(copied_line);
    return 0;
}
