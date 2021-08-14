#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../constants/logger.h"
#include "../constants/messages.h"
#include "../constants/boolean.h"
#include "../line/line.h"
#include "../line/validator.h"
#include "../utils/line_helper.h"
#include "../symbol/symbol.h"

int parse_labels(Line *line, LinkedSymbol *linked_symbol);

int parse_label(Line *line, char *label);

void parse_operands(Line *line, LinkedSymbol *linked_symbol);

void parse_command_operand(Line *line, char *operand, LinkedSymbol *linked_symbol);

void parse_directive_operand(Line *line, char *operand, LinkedSymbol *linked_symbol);

void validate_parsed_line(Line *line);

void display_line_error(const char *file_name, Line *line);

void append_parsed_operand(Line *line, char *operand);

int parse(const char *file_name, LinkedLine *linked_line, LinkedSymbol *linked_symbol)
{
    Line *line = linked_line->head;
    int parsed = FALSE;

    for (; line != NULL; line = line->next)
    {
        /* Parsing the syntax and setting the relevant data (e.g. operands). */
        parsed = parse_labels(line, linked_symbol);
        parse_operands(line, linked_symbol);

        /* Validating the parsed line by known rules (e.g. only $0 operand for `call`). */
        validate_parsed_line(line);

        /* Display error that found in the line after parsing and validating the line. */
        display_line_error(file_name, line);
    }

    /* First need add all the labels to symbol table, and then parse the operands :) */
    /* Need to loops because ABC exists, but in after line */
    /* move $1, ABC*/
    /* ABC: yo*/

    return parsed;
}

int parse_labels(Line *line, LinkedSymbol *linked_symbol)
{
    /* Breaking this line into words (tokens). */
    char delimeter[] = " ,";
    char *duplicated_line = duplicate(line->text);
    char *token = NULL;

    if (duplicated_line == NULL)
    {
        return FALSE;
    }

    token = strtok(duplicated_line, delimeter);

    if (token == NULL)
    {
        free(duplicated_line);
        return FALSE;
    }

    while (token != NULL)
    {
        if (is_empty_line(token))
        {
            line->statement_type = EMPTY;
            break;
        }
        else if (is_comment_line(token))
        {
            line->statement_type = COMMENT;
            break;
        }

        /* Remove '\n' from lines like: "END: stop\n". */
        remove_new_line_character(token);

        if (is_label(token))
        {
            if (parse_label(line, token))
            {
                Symbol *symbol = add_symbol(linked_symbol);

                if (symbol != NULL)
                {
                    memcpy(symbol->label, token, strlen(token) + 1);
                }
            }
        }

        token = strtok(NULL, delimeter);
    }

    free(duplicated_line);
    return TRUE;
}

int parse_label(Line *line, char *label)
{
    if (is_label_empty(label))
    {
        strcpy(line->error_message, NO_LABEL_FOUND);
    }
    else if (is_label_above_max_length(label))
    {
        strcpy(line->error_message, MAX_LENGTH_LABEL);
    }
    else if (is_label_equals_command(label))
    {
        strcpy(line->error_message, MAX_EQUALS_COMMAND);
    }
    else if (is_label_equals_directive(label))
    {
        strcpy(line->error_message, MAX_EQUALS_DIRECTIVE);
    }
    else
    {
        memcpy(line->label, label, strlen(label) + 1);
        return TRUE;
    }

    return FALSE;
}

void parse_operands(Line *line, LinkedSymbol *linked_symbol)
{
    /* Breaking this line into words (tokens). */
    char delimeter[] = " ,";
    char *duplicated_line = duplicate(line->text);
    char *token = NULL;

    if (duplicated_line == NULL)
    {
        return;
    }

    token = strtok(duplicated_line, delimeter);

    if (token == NULL)
    {
        free(duplicated_line);
        return;
    }

    while (token != NULL)
    {
        if (is_empty_line(token))
        {
            line->statement_type = EMPTY;
            break;
        }
        else if (is_comment_line(token))
        {
            line->statement_type = COMMENT;
            break;
        }

        /* Remove '\n' from lines like: "END: stop\n". */
        remove_new_line_character(token);

        if (is_command(token))
        {
            line->statement_type = COMMAND;

            memcpy(line->command, token, strlen(token) + 1);
        }
        else if (is_directive(token))
        {
            line->statement_type = DIRECTIVE;

            memcpy(line->directive, token, strlen(token) + 1);
        }
        else
        {
            if (line->statement_type == COMMAND)
            {
                parse_command_operand(line, token, linked_symbol);
            }
            else if (line->statement_type == DIRECTIVE)
            {
                parse_directive_operand(line, token, linked_symbol);
            }
        }

        token = strtok(NULL, delimeter);
    }

    free(duplicated_line);
}

void parse_command_operand(Line *line, char *operand, LinkedSymbol *linked_symbol)
{
    if (is_register(operand))
    {
        if (is_register_exists(operand))
        {
            append_parsed_operand(line, operand);
        }
        else
        {
            sprintf(line->error_message, INVALID_DEFINITION, operand);
        }
    }
    else if (is_number(operand))
    {
        append_parsed_operand(line, operand);
    }
    else if (symbol_exists(linked_symbol, operand))
    {
        append_parsed_operand(line, operand);
    }
    else
    {
        sprintf(line->error_message, INVALID_DEFINITION, operand);
    }
}

void parse_directive_operand(Line *line, char *operand, LinkedSymbol *linked_symbol)
{
    if (is_number(operand))
    {
        append_parsed_operand(line, operand);
    }
    else if (is_quotation_mark(operand))
    {
        remove_quotation_marks(operand);
        append_parsed_operand(line, operand);
    }
    else if (symbol_exists(linked_symbol, operand))
    {
        append_parsed_operand(line, operand);
    }
    else
    {
        sprintf(line->error_message, INVALID_DEFINITION, operand);
    }
}

void validate_parsed_line(Line *line)
{
    if (line->statement_type == EMPTY || line->statement_type == COMMENT)
    {
        return;
    }

    /*if (line->operands_count == 0)
    {
        line->has_error = TRUE;
        sprintf(line->error_message, NO_OPERANDS_FOUND);
    }*/

    /* TODO: Iterate -> jmp, la, call, stop only one register (call only $0 register) */
    /* TODO: Do I J table */
    if (strcmp(line->command, "call") == 0)
    {
        /* BUG: It'll be 0 because `vall` isn't recognized as an operand */
        /* TODO: Symbol table to fix it */
        if (line->operands_count == 1)
        {
            if (strcmp(line->operands[0], "$0") != 0)
            {
                strcpy(line->error_message, ONLY_ZERO_OPERAND);
            }
        }
        else
        {
            strcpy(line->error_message, ONLY_ONE_OPERAND);
        }
    }
}

void display_line_error(const char *file_name, Line *line)
{
    if (strlen(line->error_message) != 0)
    {
        printf(ERROR_LINE_FORMAT, file_name, line->line_number, line->error_message);
    }
}

void append_parsed_operand(Line *line, char *operand)
{
    int count = line->operands_count;

    strcpy(line->operands[count], operand);

    line->operands_count = count + 1;
}
