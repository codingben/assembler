#include <stdio.h>
#include "constants/logger.h"
#include "constants/messages.h"
#include "constants/rules.h"
#include "utils/file.h"
#include "parser/parser.h"

int main(int argument_count, char **argument_vector)
{
    int i;
    const char *filename = argument_vector[0];

    if (argument_count < 2)
    {
        printf(NO_FILE_TO_COMPILE);
        printf("#---------------------------------------------------#\n");
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
            printf(ERROR_FORMAT, filename, NO_AS_EXTENSION);
            printf("#---------------------------------------------------#\n");
            continue;
        }

        /* Analyze syntax and then send to translator */
        parse(filename);

        /* Add space for a new file */
        printf("\n#---------------------------------------------------#\n");
    }

    return EXIT_SUCCESS;
}