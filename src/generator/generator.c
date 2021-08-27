/*
 * Copyright (c) 2021 Ben Ukhanov. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../constants/boolean.h"
#include "../line/line.h"
#include "../line/validator.h"
#include "../symbol/symbol.h"
#include "../utils/line_helper.h"
#include "../utils/file_helper.h"

#define ONE_BYTE 8
#define FOUR_BITS 4
#define LEFT_HEX_DIGIT 0xF0
#define RIGHT_HEX_DIGIT 0x0F
#define OB_ADDRESS_FORMAT "0%d "
#define LEFT_HEX_FORMAT "%X"
#define RIGHT_HEX_FORMAT "%X "
#define NEW_LINE "\n"

void generate_code_image(const char *file_name, FILE *object_file, Line *line);

void generate_data_image(const char *file_name, FILE *object_file, Line *line);

void generate_entry(const char *file_name, FILE *entry_file, Line *line, LinkedSymbol *linked_symbol);

void generate_external(const char *file_name, FILE *extern_file, Line *line, LinkedSymbol *linked_symbol);

int can_generate_entry(Line *line, LinkedSymbol *linked_symbol);

int can_generate_external(Line *line, LinkedSymbol *linked_symbol);

void generate_r_instructions(Line *line, FILE *file);

void generate_i_instructions(Line *line, FILE *file);

void generate_j_instructions(Line *line, FILE *file);

void write_instruction(FILE *file, unsigned int address, unsigned int value);

int generate(const char *file_name, LinkedLine *linked_line, LinkedSymbol *linked_symbol)
{
    Line *line = linked_line->head;
    FILE *object_file = NULL;
    FILE *extern_file = NULL;
    FILE *entry_file = NULL;

    for (; line != NULL; line = line->next)
    {
        if (line->statement_type == COMMAND)
        {
            if (object_file == NULL)
            {
                char *object_file_name =
                    rename_file_name_extension(file_name, OBJECT_FILE_EXTENSION);

                if (object_file_name != NULL)
                {
                    object_file = fopen(object_file_name, "w+");
                }

                free(object_file_name);

                if (object_file == NULL)
                {
                    return FALSE;
                }
            }

            if (can_generate_external(line, linked_symbol))
            {
                if (extern_file == NULL)
                {
                    /* TODO: extern_file = open_file(...) */

                    char *extern_file_name =
                        rename_file_name_extension(file_name, EXTERNAL_FILE_EXTENSION);

                    if (extern_file_name != NULL)
                    {
                        extern_file = fopen(extern_file_name, "w+");
                    }

                    free(extern_file_name);

                    if (extern_file == NULL)
                    {
                        return FALSE;
                    }
                }

                generate_external(file_name, extern_file, line, linked_symbol);
            }

            generate_code_image(file_name, object_file, line);
        }
        else if (line->statement_type == DIRECTIVE)
        {
            if (can_generate_entry(line, linked_symbol))
            {
                if (entry_file == NULL)
                {
                    char *entry_file_name =
                        rename_file_name_extension(file_name, ENTRY_FILE_EXTENSION);

                    if (entry_file_name != NULL)
                    {
                        entry_file = fopen(entry_file_name, "w+");
                    }

                    free(entry_file_name);

                    if (entry_file == NULL)
                    {
                        return FALSE;
                    }
                }

                generate_entry(file_name, entry_file, line, linked_symbol);
            }

            /* Shouldn't it called after this loop in another loop to avoid output conflict? */
            /* generate_data_image(file_name, object_file, line); */
        }
    }

    if (object_file != NULL)
    {
        fclose(object_file);
    }

    if (extern_file != NULL)
    {
        fclose(extern_file);
    }

    if (entry_file != NULL)
    {
        fclose(entry_file);
    }

    return TRUE;
}

void generate_code_image(const char *file_name, FILE *object_file, Line *line)
{
    instruction_type type = find_type(line->command);

    if (type == R)
    {
        generate_r_instructions(line, object_file);
    }
    else if (type == I)
    {
        generate_i_instructions(line, object_file);
    }
    else if (type == J)
    {
        generate_j_instructions(line, object_file);
    }
}

void generate_data_image(const char *file_name, FILE *object_file, Line *line)
{
    /* TODO: Implement */
}

void generate_entry(const char *file_name, FILE *entry_file, Line *line, LinkedSymbol *linked_symbol)
{
    unsigned int symbol_value =
        get_symbol_value(linked_symbol, line->operands[0]);

    fprintf(entry_file, "%s 0%d\n", line->operands[0], symbol_value);
}

int can_generate_entry(Line *line, LinkedSymbol *linked_symbol)
{
    /* In case it's not a ".entry" line. */
    if (is_entry(line->directive) == FALSE)
    {
        return FALSE;
    }

    /* In case the operand of ".entry (operand)" is not found in the symbol table. */
    if (symbol_exists(linked_symbol, line->operands[0]) == FALSE)
    {
        return FALSE;
    }

    return TRUE;
}

void generate_external(const char *file_name, FILE *extern_file, Line *line, LinkedSymbol *linked_symbol)
{
    symbol_type symbol_value =
        get_symbol_type(linked_symbol, line->operands[0]);

    if (symbol_value == EXTERNAL)
    {
        fprintf(extern_file, "%s 0%d\n", line->operands[0], line->address);
    }
}

int can_generate_external(Line *line, LinkedSymbol *linked_symbol)
{
    /* In case it's not a J instruction line. */
    if (is_j_instruction_except_stop(line->command) == FALSE)
    {
        return FALSE;
    }

    /* In case the operand of J instruction is not found in the symbol table. */
    if (symbol_exists(linked_symbol, line->operands[0]) == FALSE)
    {
        return FALSE;
    }

    return TRUE;
}

void generate_r_instructions(Line *line, FILE *file)
{
    unsigned int value = 0;

    value = value | line->r_instruction.opcode << 26; /* 31 - 26 */
    value = value | line->r_instruction.rs << 21;     /* 25 - 21 */
    value = value | line->r_instruction.rt << 16;     /* 20 - 16 */
    value = value | line->r_instruction.rd << 11;     /* 15 - 11 */
    value = value | line->r_instruction.funct << 6;   /* 10 - 6 */
    value = value | line->r_instruction.unused;       /* 5 - 0 */

    write_instruction(file, line->address, value);
}

void generate_i_instructions(Line *line, FILE *file)
{
    unsigned int value = 0;

    value = value | (line->i_instruction.opcode << 26); /* 31 - 26 */
    value = value | (line->i_instruction.rs << 21);     /* 25 - 21 */
    value = value | (line->i_instruction.rt << 16);     /* 20 - 16 */
    value = value | (line->i_instruction.immed);        /* 15 - 0 */

    write_instruction(file, line->address, value);
}

void generate_j_instructions(Line *line, FILE *file)
{
    unsigned int value = 0;

    value = value | (line->j_instruction.opcode << 26);  /* 31 - 26 */
    value = value | (line->j_instruction.reg << 25);     /* 25 */
    value = value | (line->j_instruction.address << 24); /* 24 - 0 */

    write_instruction(file, line->address, value);
}

void write_instruction(FILE *file, unsigned int address, unsigned int value)
{
    int i;

    fprintf(file, OB_ADDRESS_FORMAT, address);

    for (i = 0; i < FOUR_BITS; i++)
    {
        unsigned int left = (value & LEFT_HEX_DIGIT) >> FOUR_BITS;
        unsigned int right = value & RIGHT_HEX_DIGIT;

        fprintf(file, LEFT_HEX_FORMAT, left);
        fprintf(file, RIGHT_HEX_FORMAT, right);

        value = value >> ONE_BYTE;
    }

    fprintf(file, NEW_LINE);
}
