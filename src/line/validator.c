#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "line.h"
#include "../constants/boolean.h"
#include "../utils/line_helper.h"

int is_empty_line(char *value)
{
    while (isspace(*value) && value++)
    {
        /* Left blank intentionally. */
    };

    return !*value ? TRUE : FALSE;
}

int is_comment_line(char *value)
{
    return value[0] == ';' ? TRUE : FALSE;
}

int is_error_message_empty(char *value)
{
    return strlen(value) == 0 ? TRUE : FALSE;
}

int is_label(char *value)
{
    return value[strlen(value) - 1] == ':' ? TRUE : FALSE;
}

int is_label_empty(char *value)
{
    return strlen(value) == 0 ? TRUE : FALSE;
}

int is_label_above_max_length(char *value)
{
    return strlen(value) > MAX_LABEL_LENGTH ? TRUE : FALSE;
}

/* DRY: Make generic function similar to is_label_equals_directive(). */
int is_label_equals_command(char *value)
{
    int i = 0;
    char *temp = duplicate(value);

    temp = remove_last_character(temp);

    for (i = 0; i < COMMANDS_SIZE; i++)
    {
        if (strcmp(commands[i].name, temp) == 0)
        {
            return TRUE;
        }
    }

    return FALSE;
}

/* DRY: Make generic function similar to is_label_equals_command(). */
int is_label_equals_directive(char *value)
{
    int i = 0;

    for (i = 0; i < DIRECTIVES_SIZE; i++)
    {
        if (strcmp(directives[i].name, value) == 0)
        {
            return TRUE;
        }
    }

    return FALSE;
}

int is_command(char *value)
{
    int i = 0;

    for (i = 0; i < COMMANDS_SIZE; i++)
    {
        if (strcmp(commands[i].name, value) == 0)
        {
            return TRUE;
        }
    }

    return FALSE;
}

int is_directive(char *value)
{
    int i = 0;

    for (i = 0; i < DIRECTIVES_SIZE; i++)
    {
        if (strcmp(directives[i].name, value) == 0)
        {
            return TRUE;
        }
    }

    return FALSE;
}

int is_register(char *value)
{
    return value[0] == '$' ? TRUE : FALSE;
}

int is_number(char *value)
{
    char *result = NULL;

    strtol(value, &result, 0);

    if (result == NULL)
    {
        return 0;
    }

    return *result == (char)0;
}

int is_register_exists(char *value)
{
    int i = 0;

    for (i = 0; i < REGISTER_SIZE; i++)
    {
        if (strcmp(registers[i].name, value) == 0)
        {
            return TRUE;
        }
    }

    return FALSE;
}

int is_quotation_mark(char *value)
{
    return value[0] == '"' && value[strlen(value) - 1] == '"';
}

int is_extern(char *value)
{
    return strcmp(".extern", value) == 0 ? TRUE : FALSE;
}

int is_entry(char *value)
{
    return strcmp(".entry", value) == 0 ? TRUE : FALSE;
}

int is_asciz(char *value)
{
    return strcmp(".asciz", value) == 0 ? TRUE : FALSE;
}

int is_db(char *value)
{
    return strcmp(".db", value) == 0 ? TRUE : FALSE;
}

int is_dh(char *value)
{
    return strcmp(".dh", value) == 0 ? TRUE : FALSE;
}

int is_dw(char *value)
{
    return strcmp(".dw", value) == 0 ? TRUE : FALSE;
}

int is_arthematic_logic_r_instructions(char *name)
{
    int is_add = strcmp("add", name) == 0;
    int is_sub = strcmp("sub", name) == 0;
    int is_and = strcmp("and", name) == 0;
    int is_or = strcmp("or", name) == 0;
    int is_nor = strcmp("nor", name) == 0;

    return is_add || is_sub || is_and || is_or || is_nor;
}

int is_copy_r_instructions(char *name)
{
    int is_move = strcmp("move", name) == 0;
    int is_mvhi = strcmp("mvhi", name) == 0;
    int is_mvlo = strcmp("mvlo", name) == 0;

    return is_move || is_mvhi || is_mvlo;
}

int is_arthematic_logic_i_instructions(char *name)
{
    int is_addi = strcmp("addi", name) == 0;
    int is_subi = strcmp("subi", name) == 0;
    int is_andi = strcmp("andi", name) == 0;
    int is_ori = strcmp("ori", name) == 0;
    int is_nori = strcmp("nori", name) == 0;

    return is_addi || is_subi || is_andi || is_ori || is_nori;
}

int is_conditional_branching_i_instructions(char *name)
{
    int is_beq = strcmp("beq", name) == 0;
    int is_bne = strcmp("bne", name) == 0;
    int is_blt = strcmp("blt", name) == 0;
    int is_bgt = strcmp("bgt", name) == 0;

    return is_beq || is_bne || is_blt || is_bgt;
}

int is_load_save_i_instructions(char *name)
{
    int is_lb = strcmp("lb", name) == 0;
    int is_sb = strcmp("sb", name) == 0;
    int is_lw = strcmp("lw", name) == 0;
    int is_sw = strcmp("sw", name) == 0;
    int is_lh = strcmp("lh", name) == 0;
    int is_sh = strcmp("sh", name) == 0;

    return is_lb || is_sb || is_lw || is_sw || is_lh || is_sh;
}

int is_stop_instruction(char *name)
{
    return strcmp("stop", name) == 0;
}

int is_j_instruction_except_stop(char *name)
{
    int is_jmp = strcmp("jmp", name) == 0;
    int is_la = strcmp("la", name) == 0;
    int is_call = strcmp("call", name) == 0;

    return is_jmp || is_la || is_call;
}
