/*
 * Copyright (c) 2021 Ben Ukhanov. All rights reserved.
 */

#include <stdlib.h>
#include <string.h>
#include "../constants/boolean.h"
#include "../utils/file_helper.h"

int validate_extension(const char *filename)
{
    /* Extract extension from file name. */
    char *extension = strrchr(filename, '.');

    /* Compare extracted extension with expected one. */
    return strcmp(extension, ASSEMBLY_EXTENSION) != 0 ? FALSE : TRUE;
}

char *rename_file_name_extension(const char *file_name, const char *extension)
{
    int length = strlen(file_name) + 1;
    char *new_file_name = malloc((length) * sizeof(char));
    char *temp = NULL;

    if (new_file_name == NULL)
    {
        return NULL;
    }

    /* Remove ".as" from the file name. */
    temp = strstr(new_file_name, ASSEMBLY_EXTENSION);

    if (temp)
    {
        *temp = '\0';
    }

    /* Add the new file extension ".ob". */
    strcat(new_file_name, OBJECT_FILE_EXTENSION);
    return new_file_name;
}
