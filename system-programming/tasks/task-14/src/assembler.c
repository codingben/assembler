#include <stdio.h>
#include "utils.h"
#include "reader.h"

int main(int arguments_count, char **arguments)
{
    int i;

    if (arguments_count < 2)
    {
        printf("Could not find a file to compile.\n");
        return 1; /* EXIT_FAILURE */
    }

    for (i = 1; i < arguments_count; ++i)
    {
        const char *filename = arguments[i];

        /* parse (read_file) */
        /* if (parse) compile */
        /* if (compile) build */

        if (validate_extension(filename) != 0)
        {
            printf("Assembly file must be with .as extension.\n\n");
            continue;
        }

        read_file(filename);
    }

    return 0; /* EXIT_SUCCESS */
}