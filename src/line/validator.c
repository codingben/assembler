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

int is_label(char *value)
{
    return value[strlen(value) - 1] == ':' ? TRUE : FALSE;
}

int is_label_empty(char *value)
{
    return strlen(value) == 1 ? TRUE : FALSE;
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
        /* Compare given value with known commands. */
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
        /* Compare given value with known commands. */
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
        /* Compare given value with known commands. */
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
        /* Compare given value with known commands. */
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
        /* Compare given value with known registers. */
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
