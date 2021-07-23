#include <string.h>

#define ASSEMBLY_EXTENSION ".as"

int validate_extension(const char *filename)
{
    char *extension = strrchr(filename, '.');
    return strcmp(extension, ASSEMBLY_EXTENSION) != 0;
}