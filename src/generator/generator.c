/*
 * Copyright (c) 2021 Ben Ukhanov. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../constants/boolean.h"
#include "../constants/messages.h"
#include "../constants/logger.h"
#include "../line/line.h"
#include "../line/validator.h"
#include "../symbol/symbol.h"
#include "../utils/line_helper.h"
#include "../utils/file_helper.h"

#define IC_DEFAULT 100
#define HIGH_NIBBLE(x) (((x) >> 4) & 0x0F)
#define LOW_NIBBLE(x) ((x)&0x0F)
#define ONE_BYTE_OFFSET 8
#define FOUR_BYTES 4
#define OB_ADDRESS_FORMAT "0%d "
#define LEFT_HEX_FORMAT "%X"
#define RIGHT_HEX_FORMAT "%X "
#define NEW_LINE "\n"
#define ENTRY_FORMAT "%s 0%d\n"
#define EXTERNAL_FORMAT "%s 0%d\n"
#define COUNTERS_FORMAT "\t %d %d\n"
#define DATA_FORMAT "%c%c "

extern int instruction_counter;
extern int data_counter;

void generate_code_image(const char *file_name, FILE *file, Line *line);

/* void generate_data_image(const char *file_name, FILE *file, Line *line); */

void generate_entry(const char *file_name, FILE *file, Line *line, LinkedSymbol *linked_symbol);

void generate_external(const char *file_name, FILE *file, Line *line, LinkedSymbol *linked_symbol);

void generate_r_instructions(Line *line, FILE *file);

void generate_i_instructions(Line *line, FILE *file);

void generate_j_instructions(Line *line, FILE *file);

void write_counters(FILE *file);

void write_code_image(FILE *file, unsigned int address, unsigned int value);

void write_data_image(FILE *file, unsigned int address, char *data);

int has_entry(Line *line, LinkedSymbol *linked_symbol);

int has_external(Line *line, LinkedSymbol *linked_symbol);

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
            if (has_external(line, linked_symbol))
            {
                if (extern_file == NULL)
                {
                    extern_file = open_file(file_name, EXTERNAL_FILE_EXTENSION);
                }

                generate_external(file_name, extern_file, line, linked_symbol);
            }

            if (object_file == NULL)
            {
                object_file = open_file(file_name, OBJECT_FILE_EXTENSION);

                write_counters(object_file);
            }

            generate_code_image(file_name, object_file, line);
        }
        else if (line->statement_type == DIRECTIVE)
        {
            if (has_entry(line, linked_symbol))
            {
                if (entry_file == NULL)
                {
                    entry_file = open_file(file_name, ENTRY_FILE_EXTENSION);
                }

                generate_entry(file_name, entry_file, line, linked_symbol);
            }
            else
            {
                if (object_file == NULL)
                {
                    object_file = open_file(file_name, OBJECT_FILE_EXTENSION);

                    write_counters(object_file);
                }

                if (is_asciz(line->directive))
                {
                    char *hex = convert_asciz_to_hex(line->operands[0]);

                    write_data_image(object_file, line->address, hex);

                    free(hex);
                }
            }
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

void generate_code_image(const char *file_name, FILE *file, Line *line)
{
    instruction_type type = find_type(line->command);

    if (type == R)
    {
        generate_r_instructions(line, file);
    }
    else if (type == I)
    {
        generate_i_instructions(line, file);
    }
    else if (type == J)
    {
        generate_j_instructions(line, file);
    }
}

void generate_entry(const char *file_name, FILE *file, Line *line, LinkedSymbol *linked_symbol)
{
    unsigned int symbol_value =
        get_symbol_value(linked_symbol, line->operands[0]);

    fprintf(file, ENTRY_FORMAT, line->operands[0], symbol_value);
}

void generate_external(const char *file_name, FILE *file, Line *line, LinkedSymbol *linked_symbol)
{
    symbol_type symbol_value =
        get_symbol_type(linked_symbol, line->operands[0]);

    if (symbol_value == EXTERNAL)
    {
        fprintf(file, EXTERNAL_FORMAT, line->operands[0], line->address);
    }
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

    write_code_image(file, line->address, value);
}

void generate_i_instructions(Line *line, FILE *file)
{
    unsigned int value = 0;

    value = value | (line->i_instruction.opcode << 26); /* 31 - 26 */
    value = value | (line->i_instruction.rs << 21);     /* 25 - 21 */
    value = value | (line->i_instruction.rt << 16);     /* 20 - 16 */
    value = value | (line->i_instruction.immed);        /* 15 - 0 */

    write_code_image(file, line->address, value);
}

void generate_j_instructions(Line *line, FILE *file)
{
    unsigned int value = 0;

    value = value | (line->j_instruction.opcode << 26);  /* 31 - 26 */
    value = value | (line->j_instruction.reg << 25);     /* 25 */
    value = value | (line->j_instruction.address << 24); /* 24 - 0 */

    write_code_image(file, line->address, value);
}

void write_counters(FILE *file)
{
    int ic = instruction_counter - IC_DEFAULT;
    int dc = data_counter + 1;

    fprintf(file, COUNTERS_FORMAT, ic, dc);
}

void write_code_image(FILE *file, unsigned int address, unsigned int value)
{
    int i;

    fprintf(file, OB_ADDRESS_FORMAT, address);

    for (i = 0; i < FOUR_BYTES; i++)
    {
        fprintf(file, LEFT_HEX_FORMAT, HIGH_NIBBLE(value));
        fprintf(file, RIGHT_HEX_FORMAT, LOW_NIBBLE(value));

        value = value >> ONE_BYTE_OFFSET;
    }

    fprintf(file, NEW_LINE);
}

void write_data_image(FILE *file, unsigned int address, char *data)
{
    int i;
    int length = strlen(data); /* E.g. "00B0E0N0" = 8. */
    int data_counter = 1;
    int line_address = (instruction_counter - FOUR_BYTES) + address;

    fprintf(file, OB_ADDRESS_FORMAT, line_address);

    for (i = 0; i < length; i += 2)
    {
        /* Will print: "00" (data[i] = '0' and data[i + 1] = '0'). */
        fprintf(file, DATA_FORMAT, data[i], data[i + 1]);

        /* If we have: "00 B0 E0 N0", then new line. */
        if (data_counter == 4)
        {
            fprintf(file, NEW_LINE);

            data_counter = 1;
        }
        else
        {
            data_counter++;
        }
    }
}

int has_entry(Line *line, LinkedSymbol *linked_symbol)
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

int has_external(Line *line, LinkedSymbol *linked_symbol)
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
