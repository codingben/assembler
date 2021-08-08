#include <string.h>
#include "../constants/boolean.h"

#define ASSEMBLY_EXTENSION ".as"

int validate_extension(const char *filename)
{
    /* Extract extension from file name. */
    char *extension = strrchr(filename, '.');

    /* Compare extracted extension with expected one. */
    return strcmp(extension, ASSEMBLY_EXTENSION) != FALSE;
}
