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

void translate_r_instruction(Line *line);

void translate_i_instruction(Line *line, LinkedSymbol *linked_symbol);

void translate_j_instruction(Line *line, LinkedSymbol *linked_symbol);

int translate(LinkedLine *linked_line, LinkedSymbol *linked_symbol)
{
    Line *line = linked_line->head;

    /* NOTE: All lines passed validation and should have operands, etc. */

    for (; line != NULL; line = line->next)
    {
        instruction_type type;

        if (line->statement_type != COMMAND)
        {
            continue;
        }

        type = find_type(line->command);

        if (type == R)
        {
            translate_r_instruction(line);
        }
        else if (type == I)
        {
            translate_i_instruction(line, linked_symbol);
        }
        else if (type == J)
        {
            translate_j_instruction(line, linked_symbol);
        }
    }

    return TRUE;
}

void translate_r_instruction(Line *line)
{
    if (is_arthematic_logic_r_instructions(line->command)) /* add, sub, and, or, nor */
    {
        line->r_instruction.opcode = find_opcode(line->command);   /* add $3, $19, $8 */
        line->r_instruction.rs = find_register(line->operands[0]); /* $3 */
        line->r_instruction.rt = find_register(line->operands[1]); /* $19 */
        line->r_instruction.rd = find_register(line->operands[2]); /* $8 */
        line->r_instruction.funct = find_funct(line->command);     /* 1 */
        line->r_instruction.unused = 0;                            /* 0 always */
    }
    else if (is_copy_r_instructions(line->command)) /* move, mvhi, mvlo */
    {
        line->r_instruction.opcode = find_opcode(line->command);   /* move */
        line->r_instruction.rs = find_register(line->operands[0]); /* $20 */
        line->r_instruction.rt = 0;                                /* 0 */
        line->r_instruction.rd = find_register(line->operands[1]); /* $4 */
        line->r_instruction.funct = find_funct(line->command);     /* 1 */
        line->r_instruction.unused = 0;                            /* 0 always */
    }
}

void translate_i_instruction(Line *line, LinkedSymbol *linked_symbol)
{
    if (is_arthematic_logic_i_instructions(line->command)) /* addi, subi, andi, ori, nori */
    {
        line->i_instruction.opcode = find_opcode(line->command);   /* addi $9, -45, $8 */
        line->i_instruction.rs = find_register(line->operands[0]); /* $9 */
        line->i_instruction.immed = atoi(line->operands[1]);       /* -45 */
        line->i_instruction.rt = find_register(line->operands[2]); /* $8 */
    }
    else if (is_conditional_branching_i_instructions(line->command)) /* beq, bne, blt, bgt */
    {
        char label[MAX_LABEL_LENGTH];
        unsigned int curr_address = 0;
        unsigned int dest_address = 0;
        unsigned int address = 0;

        line->i_instruction.opcode = find_opcode(line->command);   /* blt $5, $24, loop */
        line->i_instruction.rs = find_register(line->operands[0]); /* $5 */
        line->i_instruction.rt = find_register(line->operands[1]); /* $24 */

        strcpy(label, line->operands[2]);

        curr_address = line->address;                          /* 300 */
        dest_address = get_symbol_value(linked_symbol, label); /* 200 */
        address = (dest_address - curr_address);               /* 200 - 300 */

        line->i_instruction.immed = address;
    }
    else if (is_load_save_i_instructions(line->command)) /* lb, sb, lw, sw, lh, sh */
    {
        line->i_instruction.opcode = find_opcode(line->command);   /* lh $9, 34, $2 */
        line->i_instruction.rs = find_register(line->operands[0]); /* $9 */
        line->i_instruction.immed = atoi(line->operands[1]);       /* 34 */
        line->i_instruction.rt = find_register(line->operands[2]); /* $2 */
    }
}

void translate_j_instruction(Line *line, LinkedSymbol *linked_symbol)
{
    if (is_stop_instruction(line->command)) /* stop */
    {
        line->j_instruction.opcode = find_opcode(line->command); /* stop */
        line->j_instruction.reg = 0;
        line->j_instruction.address = 0;
    }
    else if (is_j_instruction_except_stop(line->command)) /* jmp, la, call */
    {
        line->j_instruction.opcode = find_opcode(line->command);  /* jmp $register / jmp label */
        line->j_instruction.reg = is_register(line->operands[0]); /* $register / label */

        if (line->j_instruction.reg == FALSE)
        {
            if (symbol_exists(linked_symbol, line->operands[0]))
            {
                /* TODO: Fix here this shit (do data image after instruction image) */

                /* printf("Label: %s\n", line->operands[0]); */

                line->j_instruction.address = get_symbol_value(linked_symbol, line->operands[0]); /* label */

                /* printf("Value: %d\n", line->j_instruction.address); */
            }
            else
            {
                line->j_instruction.address = 0;
            }
        }
        else
        {
            line->j_instruction.address = find_register(line->operands[0]); /* $register */
        }
    }
}
