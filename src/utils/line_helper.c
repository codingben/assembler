#include <stdlib.h>
#include <string.h>

char *duplicate(char *value)
{
    int length = strlen(value) + 1;
    char *new_line = malloc((length) * sizeof(char));

    if (new_line == NULL)
    {
        return 0;
    }

    memcpy(new_line, value, length);
    return new_line;
}

void remove_whitespaces(char *value)
{
    char *temp;

    for (temp = value; *temp; ++temp)
    {
        if (*temp != ' ')
        {
            *value++ = *temp;
        }
    }

    *value = 0;
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
