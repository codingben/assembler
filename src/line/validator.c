#include <stdlib.h>
#include <string.h>
#include "line.h"

int is_empty_line(char value)
{
    return value == '\n';
}

int is_comment_line(char value)
{
    return value == ';';
}

int is_label(char *value)
{
    return value[strlen(value) - 1] == ':';
}

int is_label_above_max_length(char *value)
{
    return strlen(value) > MAX_LABEL_LENGTH;
}

/* DRY: Make generic function similar to is_label_equals_directive(). */
int is_label_equals_command(char *value)
{
    int i = 0;
    int result = 0;

    /* Allocate new temp value. */
    char *temp = malloc(strlen(value) + 1);

    /* Copy the value beacuse we need to remove ":" character. */
    memcpy(temp, value, strlen(value) + 1);

    /* Remove ":" character. */
    temp[strlen(temp) - 1] = 0;

    for (i = 0; i < COMMANDS_SIZE; i++)
    {
        /* Compare given value with known commands. */
        result = strcmp(commands[i].name, temp);

        if (result == 0)
        {
            break;
        }
    }

    free(temp);
    return result;
}

/* DRY: Make generic function similar to is_label_equals_command(). */
int is_label_equals_directive(char *value)
{
    int i = 0;
    int result = 0;

    /* Allocate new temp value. */
    char *temp = malloc(strlen(value) + 1);

    /* Copy the value beacuse we need to remove ":" character. */
    memcpy(temp, value, strlen(value) + 1);

    /* Remove ":" character. */
    temp[strlen(temp) - 1] = 0;

    for (i = 0; i < DIRECTIVES_SIZE; i++)
    {
        /* Compare given value with known commands. */
        result = strcmp(directives[i].name, temp);

        if (result == 0)
        {
            break;
        }
    }

    free(temp);
    return result;
}

int is_command(char *value)
{
    int i = 0;
    int result = 0;

    for (i = 0; i < COMMANDS_SIZE; i++)
    {
        /* Compare given value with known commands. */
        result = strcmp(commands[i].name, value);

        if (result == 0)
        {
            break;
        }
    }

    return result;
}

int is_directive(char *value)
{
    int i = 0;
    int result = 0;

    for (i = 0; i < DIRECTIVES_SIZE; i++)
    {
        /* Compare given value with known commands. */
        result = strcmp(directives[i].name, value);

        if (result == 0)
        {
            break;
        }
    }

    return result;
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
