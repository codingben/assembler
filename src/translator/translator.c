#include <stdio.h>
#include <string.h>
#include "../constants/boolean.h"
#include "../line/line.h"
#include "../symbol/symbol.h"
#include "../utils/line_helper.h"

void translate_r_instruction(Line *line);

void translate_i_instruction(Line *line, LinkedSymbol *linked_symbol);

void translate_j_instruction(Line *line, LinkedSymbol *linked_symbol);

int *translate(LinkedLine *linked_line, LinkedSymbol *linked_symbol)
{
    Line *line = linked_line->head;

    for (; line != NULL; line = line->next)
    {
        if (line->statement_type != COMMAND)
        {
            continue;
        }

        instruction_type type = find_instruction_type(line->command);

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
        line->i_instruction.opcode = find_command_opcode(line->command); /* addi $9, -45, $8 */
        line->i_instruction.rs = find_register(line->operands[0]);       /* $9 */
        line->i_instruction.rt = find_register(line->operands[1]);       /* $8 */
        line->i_instruction.immed = line->operands[2];                   /* -45 */
    }
    else if (is_conditional_branching_i_instructions(line->command)) /* beq, bne, blt, bgt */
    {
        char label[MAX_LABEL_LENGTH];

        line->i_instruction.opcode = find_command_opcode(line->command); /* blt $5, $24, loop */
        line->i_instruction.rs = find_register(line->operands[0]);       /* $5 */
        line->i_instruction.rt = find_register(line->operands[1]);       /* $24 */

        strcpy(label, line->operands[2]);

        unsigned int curr_address = line->address;                          /* 300 */
        unsigned int dest_address = get_symbol_value(linked_symbol, label); /* 200 */
        unsigned int address = (dest_address - curr_address);               /* 200 - 300 */

        line->i_instruction.immed = address;
    }
    else if (is_load_save_i_instructions(line->command)) /* lb, sb, lw, sw, lh, sh */
    {
        line->i_instruction.opcode = find_command_opcode(line->command); /* lh $9, 34, $2 */
        line->i_instruction.rs = find_register(line->operands[0]);       /* $9 */
        line->i_instruction.rt = find_register(line->operands[1]);       /* $2 */
        line->i_instruction.immed = line->operands[2];                   /* 34 */
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
    else /* jmp, la, call */
    {
        line->j_instruction.opcode = find_opcode(line->command);  /* jmp $register / jmp label */
        line->j_instruction.reg = is_register(line->operands[0]); /* $register / label */

        if (line->j_instruction.reg == FALSE)
        {
            if (symbol_exsts(linked_symbol, line->operands[0]))
            {
                line->j_instruction.address = get_symbol_value(linked_symbol, line->operands[0]); /* label */
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
