#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../constants/logger.h"
#include "../constants/messages.h"
#include "../constants/boolean.h"
#include "../line/line.h"
#include "../line/validator.h"
#include "../utils/line_helper.h"

int parse_line(Line *line);

int validate_label(Line *line, char *label);

int parse_operands(Line *line, char *operand);

void parse(const char *file_name, LinkedLine *linked_line)
{
    Line *line = linked_line->head;

    for (; line != NULL; line = line->next)
    {
        if (parse_line(line) == TRUE)
        {
            if (line->has_error == TRUE)
            {
                printf(ERROR_LINE_FORMAT, file_name, line->line_number, line->error_message);
            }
        }

        /* printf(LOG_LINE_FORMAT, file_name, line->line_number, line->text); */
    }
}

/* TODO: Make the return type better of this function */
int parse_line(Line *line)
{
    /* TODO: Parse syntax, and collect error(s) */
    /* TODO: Check for entry or extern to create output files */
    /* TODO: Add symbol table, what is IC? */
    /* TODO: Detect and set registers */

    /* Breaking this line into words (tokens). */
    char delimeter[] = " ,";
    char *duplicated_line = duplicate(line->text);
    char *token = strtok(duplicated_line, delimeter);

    while (token != NULL)
    {
        if (is_empty_line(*token))
        {
            line->statement_type = EMPTY;
            return TRUE;
        }

        if (is_comment_line(*token))
        {
            line->statement_type = EMPTY;
            return TRUE;
        }

        /* Remove '\n' from lines like: "END: stop\n". */
        remove_new_line_character(token);

        if (is_label(token))
        {
            if (validate_label(line, token) == FALSE)
            {
                return TRUE;
            }

            memcpy(line->label, token, strlen(token) + 1);
        }
        else
        {
            if (is_command(token))
            {
                /* TODO: Call it "operation code (opcode)" */

                line->statement_type = COMMAND;
                memcpy(line->command, token, strlen(token) + 1);
            }
            else if (is_directive(token))
            {
                /* TODO: Check if it's a number or "string" */

                line->statement_type = DIRECTIVE;
                memcpy(line->directive, token, strlen(token) + 1);
            }
            else
            {
                if (parse_operands(line, token) == FALSE)
                {
                    return TRUE;
                }

                line->has_error = TRUE;
                sprintf(line->error_message, UNKNOWN_LINE_STATEMENT);
            }
        }

        token = strtok(NULL, delimeter);
    }

    free(duplicated_line);
    return FALSE;
}

int validate_label(Line *line, char *label)
{
    if (is_label_above_max_length(label))
    {
        line->has_error = TRUE;
        strcpy(line->error_message, MAX_LENGTH_LABEL);
        return FALSE;
    }

    if (is_label_equals_command(label))
    {
        line->has_error = TRUE;
        strcpy(line->error_message, MAX_EQUALS_COMMAND);
        return FALSE;
    }

    if (is_label_equals_directive(label))
    {
        line->has_error = TRUE;
        strcpy(line->error_message, MAX_EQUALS_DIRECTIVE);
        return FALSE;
    }

    return TRUE;
}

int parse_operands(Line *line, char *operand)
{
    /* TODO: Use symbol table to see what labels defined */
    /* TODO: Check if the operand is a label */
    /* TODO: Check if the operand is a "string" */

    if (line->statement_type == COMMAND)
    {
        /* TODO: Check if it's a number, use isdigit */

        if (is_register(operand))
        {
            /* TODO: If it's not a register, check if it's number or label name or by .extern */

            if (is_register_exists(operand))
            {
                printf("Command: %s\n", operand);
                return TRUE;
            }
            else
            {
                line->has_error = TRUE;
                sprintf(line->error_message, INVALID_DEFINITION, operand);
                return FALSE;
            }
        }
        else if (is_number(operand))
        {
            /* TODO: What need to check here? */

            printf("Number: %s\n", operand);
            return TRUE;
        }
        else
        {
            line->has_error = TRUE;
            sprintf(line->error_message, INVALID_DEFINITION, operand);
            return FALSE;
        }
    }
    else if (line->statement_type == DIRECTIVE)
    {
        /* TODO: Check if it's a number, use isdigit */

        if (is_number(operand))
        {
            printf("Directive: %s\n", operand);
            return TRUE;
        }
        else
        {
            line->has_error = TRUE;
            sprintf(line->error_message, INVALID_DEFINITION, operand);
            return FALSE;
        }
    }

    return TRUE;
}
