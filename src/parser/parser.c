/*
 * Copyright (c) 2021 Ben Ukhanov. All rights reserved.
 */

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

int first_parse(const char *file_name, Line *line, LinkedSymbol *linked_symbol);

int second_parse(const char *file_name, Line *line, LinkedSymbol *linked_symbol);

int parse_symbols(Line *line, LinkedSymbol *linked_symbol);

int parse_label(Line *line, char *label);

int parse_instructions(Line *line, LinkedSymbol *linked_symbol);

int parse_operands(Line *line, LinkedSymbol *linked_symbol);

void parse_command_operand(Line *line, char *operand, LinkedSymbol *linked_symbol);

void parse_directive_operand(Line *line, char *operand, LinkedSymbol *linked_symbol);

void parse_symbol_type(Line *line, char *operand, LinkedSymbol *linked_symbol);

void validate_parsed_operands(Line *line, LinkedSymbol *linked_symbol);

void display_line_error(const char *file_name, Line *line);

void append_parsed_operand(Line *line, char *operand);

void update_symbol_value(Line *line, LinkedSymbol *linked_symbol);

void update_instruction_counter(Line *line);

int instruction_counter = 100;
int data_counter = 0;

int parse(const char *file_name, LinkedLine *linked_line, LinkedSymbol *linked_symbol)
{
    /* First pass, parse all symbols (for symbol table). */
    int succeed = first_parse(file_name, linked_line->head, linked_symbol);

    if (succeed)
    {
        /* Second pass, parse all instructions and operands. */
        second_parse(file_name, linked_line->head, linked_symbol);
    }

    return succeed;
}

int first_parse(const char *file_name, Line *line, LinkedSymbol *linked_symbol)
{
    int parsed = FALSE;

    for (; line != NULL; line = line->next)
    {
        if (is_empty_line(line->text))
        {
            line->statement_type = EMPTY;
            continue;
        }
        else if (is_comment_line(line->text))
        {
            line->statement_type = COMMENT;
            continue;
        }

        parsed = parse_symbols(line, linked_symbol);

        display_line_error(file_name, line);
    }

    return parsed;
}

int second_parse(const char *file_name, Line *line, LinkedSymbol *linked_symbol)
{
    for (; line != NULL; line = line->next)
    {
        if (line->statement_type == EMPTY || line->statement_type == COMMENT)
        {
            continue;
        }

        if (parse_instructions(line, linked_symbol))
        {
            update_instruction_counter(line);
            update_symbol_value(line, linked_symbol);

            if (parse_operands(line, linked_symbol))
            {
                validate_parsed_operands(line, linked_symbol);
            }
        }

        display_line_error(file_name, line);
    }

    return TRUE;
}

int parse_symbols(Line *line, LinkedSymbol *linked_symbol)
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
        /* Remove '\n' from lines like: "END: stop\n". */
        remove_new_line_character(token);

        if (is_label(token))
        {
            if (parse_label(line, token))
            {
                Symbol *symbol = add_symbol(linked_symbol);

                if (symbol != NULL)
                {
                    char *label = remove_last_character(token);

                    if (label != NULL)
                    {
                        memcpy(symbol->name, label, strlen(label) + 1);
                    }

                    free(label);
                }
            }
        }

        /* Example scenario below in comments: */
        /* Line to parse: .extern vall */
        /* Token: .extern */
        if (is_extern(token))
        {
            line->statement_type = DIRECTIVE;

            memcpy(line->directive, token, strlen(token) + 1);
        }
        else if (line->statement_type == DIRECTIVE)
        {
            /* Token: vall */
            if (symbol_exists(linked_symbol, token) == FALSE)
            {
                Symbol *symbol = add_symbol(linked_symbol);

                if (symbol != NULL)
                {
                    memcpy(symbol->name, token, strlen(token) + 1);
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

int parse_instructions(Line *line, LinkedSymbol *linked_symbol)
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

        token = strtok(NULL, delimeter);
    }

    if (line->statement_type == UNKNOWN_STATEMENT)
    {
        strcpy(line->error_message, NO_INSTRUCTION_FOUND);
        return FALSE;
    }

    free(duplicated_line);
    return TRUE;
}

int parse_operands(Line *line, LinkedSymbol *linked_symbol)
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
        /* Remove '\n' from lines like: "END: stop\n". */
        remove_new_line_character(token);

        /* Don't parse labels. */
        if (is_label(token) == FALSE)
        {
            if (line->statement_type == COMMAND)
            {
                /* Don't parse "add $1, $2" but only "$1, $2" operands. */
                if (is_command(token) == FALSE)
                {
                    parse_command_operand(line, token, linked_symbol);
                }
            }
            else if (line->statement_type == DIRECTIVE)
            {
                /* Don't parse ".db 5, -10" but only "5, -10" operands. */
                if (is_directive(token) == FALSE)
                {
                    parse_directive_operand(line, token, linked_symbol);
                }

                parse_symbol_type(line, token, linked_symbol);
            }
        }

        token = strtok(NULL, delimeter);
    }

    free(duplicated_line);
    return TRUE;
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

void parse_symbol_type(Line *line, char *operand, LinkedSymbol *linked_symbol)
{
    if (is_entry(line->directive))
    {
        set_symbol_type(linked_symbol, operand, ENTRY);
    }
    else if (is_extern(line->directive))
    {
        set_symbol_type(linked_symbol, operand, EXTERNAL);
    }
    else if (is_label_empty(line->label) == FALSE)
    {
        char *temp = duplicate(line->label);
        temp = remove_last_character(temp);

        if (get_symbol_type(linked_symbol, temp) == CODE)
        {
            if (is_asciz(line->directive))
            {
                set_symbol_type(linked_symbol, temp, DATA);
            }
            else if (is_db(line->directive))
            {
                set_symbol_type(linked_symbol, temp, DATA);
            }
            else if (is_dh(line->directive))
            {
                set_symbol_type(linked_symbol, temp, DATA);
            }
            else if (is_dw(line->directive))
            {
                set_symbol_type(linked_symbol, temp, DATA);
            }
        }

        free(temp);
    }
}

void validate_parsed_operands(Line *line, LinkedSymbol *linked_symbol)
{
    if (line->operands_count == 0) /* Throw an error for insturctions without operands. */
    {
        if (is_stop_instruction(line->command)) /* Only `stop` instruction is without operands. */
        {
            return;
        }

        sprintf(line->error_message, NO_OPERANDS_FOUND);
    }
    else
    {
        if (is_j_instruction_except_stop(line->command)) /* jmp, la, call */
        {
            if (line->operands_count > 1) /* Only one register or label. */
            {
                sprintf(line->error_message, ONE_OPERAND_OR_LABEL);
            }
            else if (is_register(line->operands[0]) == FALSE) /* If it's not a register, then label? */
            {
                char *label = line->operands[0];

                if (label[0] == '\0')
                {
                    label = "(NULL)";
                }

                /* Check if the operand is label that is defined. */
                if (symbol_exists(linked_symbol, label) == FALSE)
                {
                    sprintf(line->error_message, NO_LABEL_DEFINED, label);
                }
            }
        }
        else if (is_stop_instruction(line->command)) /* stop */
        {
            sprintf(line->error_message, NO_INSTRUCTION_OPERANDS);
        }
    }
}

void display_line_error(const char *file_name, Line *line)
{
    if (is_error_message_empty(line->error_message) == FALSE)
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

void update_symbol_value(Line *line, LinkedSymbol *linked_symbol)
{
    if (is_label_empty(line->label) == FALSE)
    {
        char *temp = duplicate(line->label);
        temp = remove_last_character(temp);

        set_symbol_value(linked_symbol, temp, line->address);
    }
}

void update_instruction_counter(Line *line)
{
    if (line->statement_type == COMMAND)
    {
        line->address = instruction_counter;

        instruction_counter += 4;
    }
    else if (line->statement_type == DIRECTIVE)
    {
        if (is_entry(line->directive) == FALSE && is_extern(line->directive) == FALSE)
        {
            instruction_counter += 4;
            data_counter += 4;
        }

        line->address = instruction_counter;
    }
}
