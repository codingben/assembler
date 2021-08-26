/*
 * Copyright (c) 2021 Ben Ukhanov. All rights reserved.
 */

#include <stdio.h>
#include <string.h>
#include "../constants/boolean.h"
#include "../line/line.h"
#include "../line/validator.h"
#include "../symbol/symbol.h"
#include "../utils/line_helper.h"
#include "../utils/file_helper.h"

void generate_r_instructions(Line *line, FILE *file);

void generate_i_instructions(Line *line, FILE *file);

void generate_j_instructions(Line *line, FILE *file);

int generate(const char *file_name, LinkedLine *linked_line, LinkedSymbol *linked_symbol)
{
    Line *line = linked_line->head;
    FILE *object_file = NULL;
    FILE *extern_file = NULL;
    FILE *entry_file = NULL;

    /* TODO: Split to functions to return name for obj/ext/ent and then decide if create them before going through all the lines */
    /* TODO: Split to command and to directive, e.g. generate_code_image, generate_data_image, generate_entry, and generate_extern */

    for (; line != NULL; line = line->next)
    {
        if (line->statement_type == COMMAND)
        {
            instruction_type type;

            type = find_type(line->command);

            if (object_file == NULL)
            {
                char *object_file_name =
                    rename_file_name_extension(file_name, OBJECT_FILE_EXTENSION);

                if (object_file_name != NULL)
                {
                    object_file = fopen(object_file_name, "w+");
                }
            }

            if (object_file == NULL)
            {
                return FALSE;
            }

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
        else if (line->statement_type == DIRECTIVE)
        {
            /* TODO: Implement */
        }

        /* TODO: Split to functions */

        if (is_entry(line->directive))
        {
            if (entry_file == NULL)
            {
                char *entry_file_name =
                    rename_file_name_extension(file_name, ENTRY_FILE_EXTENSION);

                printf("entry_file: %s\n", entry_file_name);

                if (entry_file_name != NULL)
                {
                    entry_file = fopen(entry_file_name, "w+");
                }
            }

            if (entry_file == NULL)
            {
                return FALSE;
            }

            if (symbol_exists(linked_symbol, line->operands[0]))
            {
                unsigned int symbol_value =
                    get_symbol_value(linked_symbol, line->operands[0]);

                fprintf(entry_file, "%s %d\n", line->operands[0], symbol_value);
            }
        }

        if (is_j_instruction_except_stop(line->command))
        {
            if (extern_file == NULL)
            {
                char *extern_file_name =
                    rename_file_name_extension(file_name, EXTERNAL_FILE_EXTENSION);

                printf("extern_file: %s\n", extern_file_name);

                if (extern_file_name != NULL)
                {
                    extern_file = fopen(extern_file_name, "w+");
                }
            }

            if (extern_file == NULL)
            {
                return FALSE;
            }

            if (symbol_exists(linked_symbol, line->operands[0]))
            {
                fprintf(extern_file, "%s %d\n", line->operands[0], line->address);
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

void generate_r_instructions(Line *line, FILE *file)
{
    int i;
    unsigned int bit = 0;
    unsigned int data;

    data = line->r_instruction.opcode;
    bit |= (data << 26);

    data = line->r_instruction.rs;
    bit |= (data << 21);

    data = line->r_instruction.rt;
    bit |= (data << 16);

    data = line->r_instruction.rd;
    bit |= (data << 11);

    data = line->r_instruction.funct;
    bit |= (data << 6);

    data = line->r_instruction.unused;
    bit |= (data);

    fprintf(file, "0%d ", line->address);

    for (i = 0; i < 4; i++)
    {
        fprintf(file, "%X", (bit & 0xF0) >> 4); /* High nibble. */
        fprintf(file, "%X ", bit & 0x0F);       /* Low nibble. */

        /* Finished 1 byte, now shift right 8 bit to get the next byte. */
        bit >>= 8;
    }

    fprintf(file, "\n");
}

void generate_i_instructions(Line *line, FILE *file)
{
    int i;
    unsigned int bit = 0;
    unsigned int data;

    data = line->i_instruction.opcode;
    bit |= (data << 26);

    data = line->i_instruction.rs;
    bit |= (data << 21);

    data = line->i_instruction.rt;
    bit |= (data << 16);

    data = line->i_instruction.immed;
    bit |= (data);

    fprintf(file, "0%d ", line->address);

    for (i = 0; i < 4; i++)
    {
        fprintf(file, "%X", (bit & 0xF0) >> 4); /* high nibble. */
        fprintf(file, "%X ", bit & 0x0F);       /* low nibble. */

        /* Finished 1 byte, now shift right 8 bit to get the next byte. */
        bit >>= 8;
    }

    fprintf(file, "\n");
}

void generate_j_instructions(Line *line, FILE *file)
{
    int i;
    unsigned int bit = 0;
    unsigned int data;

    data = line->j_instruction.opcode;
    bit |= (data << 26);

    data = line->j_instruction.reg;
    bit |= (data << 25);

    data = line->j_instruction.address;
    bit |= (data << 24);

    fprintf(file, "0%d ", line->address);

    for (i = 0; i < 4; i++)
    {
        fprintf(file, "%X", (bit & 0xF0) >> 4); /* high nibble. */
        fprintf(file, "%X ", bit & 0x0F);       /* low nibble. */

        /* Finished 1 byte, now shift right 8 bit to get the next byte. */
        bit >>= 8;
    }

    fprintf(file, "\n");
}
