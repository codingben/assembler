#include <string.h>
#include "rules.h"

int validate_extension(const char *filename)
{
    char *extension = strrchr(filename, '.');
    return strcmp(extension, ASSEMBLY_EXTENSION) != 0;
}