#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../constants/logger.h"
#include "../constants/messages.h"
#include "../line/line.h"
#include "../line/validator.h"

int parse_line(Line *line);

void parse(const char *file_name, LinkedLine *linked_line)
{
    Line *line = linked_line->head;

    for (; line != NULL; line = line->next)
    {
        if (parse_line(line) == 1)
        {
            if (line->has_error == 1)
            {
                printf(ERROR_LINE_FORMAT, file_name, line->line_number, line->error_message);
            }

            continue;
        }

        /* printf(LOG_LINE_FORMAT, file_name, line->line_number, line->text); */
    }
}

int parse_line(Line *line)
{
    /* TODO: Parse syntax, and collect error(s) */
    /* TODO: Check for entry or extern to create output files */
    /* TODO: Add symbol table, what is IC? */
    /* TODO: Detect and set registers */
    /* TODO: Make better return types, no 0 or 1 */

    /* Breaking this line into words (tokens). */
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

        /* Remove '\n' from lines like: "END: stop\n". */
        remove_new_line_character(token);

        if (is_label(token) == 1)
        {
            if (is_label_above_max_length(token) == 1)
            {
                line->has_error = 1;
                strcpy(line->error_message, MAX_LENGTH_LABEL);
                return 1;
            }

            if (is_label_equals_command(token) == 0)
            {
                line->has_error = 1;
                strcpy(line->error_message, MAX_EQUALS_COMMAND);
                return 1;
            }

            if (is_label_equals_directive(token) == 0)
            {
                line->has_error = 1;
                strcpy(line->error_message, MAX_EQUALS_DIRECTIVE);
                return 1;
            }

            memcpy(line->label, token, strlen(token) + 1);
        }
        else
        {
            if (is_command(token) == 0)
            {
                line->statement_type = COMMAND;
                memcpy(line->command, token, strlen(token) + 1);
            }
            else if (is_directive(token) == 0)
            {
                line->statement_type = DIRECTIVE;
                memcpy(line->directive, token, strlen(token) + 1);
            }
            else
            {
                line->has_error = 1;
                sprintf(line->error_message, INVALID_DEFINITION, token);
                return 1;
            }
        }

        token = strtok(NULL, delim);
    }

    free(copied_line);
    return 0;
}
