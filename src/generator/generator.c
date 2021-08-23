/*
 * Copyright (c) 2021 Ben Ukhanov. All rights reserved.
 */

#include <stdio.h>
#include "../constants/boolean.h"
#include "../line/line.h"
#include "../utils/line_helper.h"

void generate_r_instructions(Line *line);

void generate_i_instructions(Line *line);

void generate_j_instructions(Line *line);

int generate(LinkedLine *linked_line)
{
    Line *line = linked_line->head;

    for (; line != NULL; line = line->next)
    {
        if (line->statement_type == COMMAND)
        {
            instruction_type type;

            type = find_type(line->command);

            if (type == R)
            {
                generate_r_instructions(line);
            }
            else if (type == I)
            {
                generate_i_instructions(line);
            }
            else if (type == J)
            {
                generate_j_instructions(line);
            }
        }
        else if (line->statement_type == DIRECTIVE)
        {
            /* TODO: Implement */
        }
    }

    return TRUE;
}

void generate_r_instructions(Line *line)
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

    printf("0%d ", line->address);

    for (i = 0; i < 4; i++)
    {
        printf("%X", (bit & 0xF0) >> 4); /* High nibble. */
        printf("%X ", bit & 0x0F);       /* Low nibble. */

        /* Finished 1 byte, now shift right 8 bit to get the next byte. */
        bit >>= 8;
    }

    printf("\n");
}

void generate_i_instructions(Line *line)
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

    printf("0%d ", line->address);

    for (i = 0; i < 4; i++)
    {
        printf("%X", (bit & 0xF0) >> 4); /* high nibble. */
        printf("%X ", bit & 0x0F);       /* low nibble. */

        /* Finished 1 byte, now shift right 8 bit to get the next byte. */
        bit >>= 8;
    }

    printf("\n");
}

void generate_j_instructions(Line *line)
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

    printf("0%d ", line->address);

    for (i = 0; i < 4; i++)
    {
        printf("%X", (bit & 0xF0) >> 4); /* high nibble. */
        printf("%X ", bit & 0x0F);       /* low nibble. */

        /* Finished 1 byte, now shift right 8 bit to get the next byte. */
        bit >>= 8;
    }

    printf("\n");
}
