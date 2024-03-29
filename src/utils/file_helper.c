/*
 * Copyright (c) 2021 Ben Ukhanov. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../constants/boolean.h"
#include "../constants/messages.h"
#include "../constants/logger.h"
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

    memcpy(new_file_name, file_name, length);

    /* Remove ".as" extension from the file name. */
    temp = strstr(new_file_name, ASSEMBLY_EXTENSION);

    if (temp)
    {
        *temp = '\0';
    }

    /* Add the new file with a new extension. */
    strcat(new_file_name, extension);
    return new_file_name;
}

FILE *open_file(const char *file_name, const char *extension)
{
    char *new_file_name =
        rename_file_name_extension(file_name, extension);

    if (new_file_name != NULL)
    {
        FILE *file = fopen(new_file_name, "w+");

        if (file == NULL)
        {
            printf(ERROR_FORMAT, file_name, FAILED_CREATE_FILE);
            exit(1);
        }

        free(new_file_name);
        return file;
    }

    return NULL;
}
