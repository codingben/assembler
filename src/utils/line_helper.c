/*
 * Copyright (c) 2021 Ben Ukhanov. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../line/line.h"

char *duplicate(char *value)
{
    int length = strlen(value) + 1;
    char *new_line = malloc((length) * sizeof(char));

    if (new_line == NULL)
    {
        return NULL;
    }

    memcpy(new_line, value, length);
    return new_line;
}

void remove_whitespaces(char *value)
{
    int i = 0;
    int count = 0;

    for (i = 0; value[i]; i++)
    {
        if (value[i] != ' ')
        {
            value[count++] = value[i];
        }
    }

    value[count] = 0;
}

void remove_new_line_character(char *value)
{
    int i = 0;

    for (i = 0; value[i]; i++)
    {
        if (value[i] == '\n')
        {
            value[i] = 0;
        }
    }
}

void remove_quotation_marks(char *value)
{
    /* Remove `"` character in first index. */
    memmove(&value[0], &value[1], strlen(value));

    /* Remove `"` character in last index. */
    value[strlen(value) - 1] = 0;
}

char *remove_last_character(char *value)
{
    /* Allocate new temp value. */
    char *temp = malloc(strlen(value) + 1);

    /* Copy the value beacuse we need to remove last character. */
    memcpy(temp, value, strlen(value) + 1);

    /* Remove last character. */
    temp[strlen(temp) - 1] = 0;
    return temp;
}

int find_register(char *value)
{
    int i = 0;

    for (i = 0; i < REGISTER_SIZE; i++)
    {
        if (strcmp(registers[i].name, value) == 0)
        {
            return registers[i].number;
        }
    }

    return -1;
}

instruction_type find_type(char *name)
{
    int i = 0;

    for (i = 0; i < COMMANDS_SIZE; i++)
    {
        if (strcmp(commands[i].name, name) == 0)
        {
            return commands[i].instruction_type;
        }
    }

    return 0;
}

int find_funct(char *name)
{
    int i = 0;

    for (i = 0; i < COMMANDS_SIZE; i++)
    {
        if (strcmp(commands[i].name, name) == 0)
        {
            return commands[i].funct;
        }
    }

    return 0;
}

int find_opcode(char *name)
{
    int i = 0;

    for (i = 0; i < COMMANDS_SIZE; i++)
    {
        if (strcmp(commands[i].name, name) == 0)
        {
            return commands[i].opcode;
        }
    }

    return 0;
}

char *convert_asciz_to_hex(char *data)
{
    int i;
    int length = strlen(data); /* E.g. "aBcd" = 4. */
    char *result = calloc(0, length * sizeof(char));
    Asciz_Word asciz_word;

    for (i = 0; i < length; i++)
    {
        char temp[3];
        asciz_word.data = data[i];
        sprintf(temp, "%02X", asciz_word.data);
        strncat(result, temp, 3);
    }

    return result;
}
