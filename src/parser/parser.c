#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../constants/logger.h"
#include "../constants/messages.h"
#include "../constants/boolean.h"
#include "../line/line.h"
#include "../line/validator.h"
#include "../utils/line_helper.h"

void parse_line(Line *line);

void parse_label(Line *line, char *label);

void parse_operands(Line *line, char *operand);

void parse(const char *file_name, LinkedLine *linked_line)
{
    Line *line = linked_line->head;

    for (; line != NULL; line = line->next)
    {
        parse_line(line);

        /*
            1. Validate parsed line, like it it's command or directive.
            2. If it has operands, check if this command can have more than one operand (e.g. register).
        */

        if (line->has_error == TRUE)
        {
            printf(ERROR_LINE_FORMAT, file_name, line->line_number, line->error_message);
        }
    }
}

void parse_line(Line *line)
{
    /* TODO: Parse syntax, and collect error(s) */
    /* TODO: Check for entry or extern to create output files */
    /* TODO: Add symbol table, what is IC? */

    /* Breaking this line into words (tokens). */
    char delimeter[] = " ,";
    char *duplicated_line = duplicate(line->text);
    char *token = strtok(duplicated_line, delimeter);

    while (token != NULL)
    {
        if (is_empty_line(token))
        {
            line->statement_type = EMPTY;
            return;
        }
        else if (is_comment_line(token))
        {
            line->statement_type = COMMENT;
            return;
        }

        /* Remove '\n' from lines like: "END: stop\n". */
        remove_new_line_character(token);

        if (is_label(token))
        {
            parse_label(line, token);
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
                parse_operands(line, token);
            }
        }

        token = strtok(NULL, delimeter);
    }

    free(duplicated_line);
}

void parse_label(Line *line, char *label)
{
    if (is_label_above_max_length(label))
    {
        line->has_error = TRUE;
        strcpy(line->error_message, MAX_LENGTH_LABEL);
    }
    else if (is_label_equals_command(label))
    {
        line->has_error = TRUE;
        strcpy(line->error_message, MAX_EQUALS_COMMAND);
    }
    else if (is_label_equals_directive(label))
    {
        line->has_error = TRUE;
        strcpy(line->error_message, MAX_EQUALS_DIRECTIVE);
    }
    else
    {
        memcpy(line->label, label, strlen(label) + 1);
    }
}

void parse_operands(Line *line, char *operand)
{
    /* TODO: Use symbol table to see what labels defined */
    /* TODO: Check if the operand is a label (symbol table) */
    /* TODO: Check if the operand is a "string" */
    /* TODO: What will happen when no operands found? Error? */

    if (line->statement_type == COMMAND)
    {
        if (is_register(operand))
        {
            /* TODO: If it's not a register, check if it's number or label name or by .extern */

            if (is_register_exists(operand))
            {
                strcpy(line->operands[line->operands_count], operand);
                line->operands_count = line->operands_count + 1;
            }
            else
            {
                line->has_error = TRUE;
                sprintf(line->error_message, INVALID_DEFINITION, operand);
            }
        }
        else if (is_number(operand))
        {
            /* TODO: What need to check here? */

            strcpy(line->operands[line->operands_count], operand);
            line->operands_count = line->operands_count + 1;
        }
        else
        {
            line->has_error = TRUE;
            sprintf(line->error_message, INVALID_DEFINITION, operand);
        }
    }
    else if (line->statement_type == DIRECTIVE)
    {
        if (is_number(operand))
        {
            /* TODO: What need to check here? */

            strcpy(line->operands[line->operands_count], operand);
            line->operands_count = line->operands_count + 1;
        }
        else
        {
            line->has_error = TRUE;
            sprintf(line->error_message, INVALID_DEFINITION, operand);
        }
    }
}
