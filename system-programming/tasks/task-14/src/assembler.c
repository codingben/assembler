#include <stdio.h>
#include "constants.h"
#include "logger.h"
#include "utils.h"
#include "parser.h"

int main(int argument_count, char **argument_vector)
{
    int i;
    const char *filename = argument_vector[0];

    if (argument_count < 2)
    {
        printf(LOG_FORMAT, filename, NO_FILE_TO_COMPILE);
        return EXIT_FAILURE;
    }

    for (i = 1; i < argument_count; ++i)
    {
        filename = argument_vector[i];

        /* parse (read_file) */
        /* if (parse) compile */
        /* if (compile) build */

        if (validate_extension(filename) != 0)
        {
            printf(LOG_FORMAT, filename, NO_AS_EXTENSION);
            continue;
        }

        /* Analyze syntax and then send to translator */
        parse(filename);
    }

    return EXIT_SUCCESS;
}