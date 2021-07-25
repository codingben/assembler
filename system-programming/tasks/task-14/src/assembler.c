#include <stdio.h>
#include "constants/logger.h"
#include "constants/messages.h"
#include "utils/file.h"
#include "scanner/analyzer.h"
#include "parser/parser.h"

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#define DEFAULT_ARG_COUNT 2

int main(int argument_count, char **argument_vector)
{
    int i;

    /* Check the number of passed arguments. */
    if (argument_count < DEFAULT_ARG_COUNT)
    {
        printf(NO_FILE_TO_COMPILE);
        return EXIT_FAILURE;
    }

    for (i = 1; i < argument_count; ++i)
    {
        const char *file_name = argument_vector[i];
        LinkedLine *linked_line;

        /* Steps:
         * 1. if (validated) analyze (scanner)
         * 2. if (analyzed) parse
         * 3. if (parsed) compile
         * 4. if (compiled) build 
         */

        /* Check if the assembly file has ".as" extension. */
        if (validate_extension(file_name) != 0)
        {
            printf(ERROR_FORMAT, file_name, NO_AS_EXTENSION);
            continue;
        }

        /* Reading the assembly source code. */
        linked_line = analyze(file_name);

        if (linked_line == NULL)
        {
            printf(ERROR_FORMAT, file_name, FAILED_ANALYZE_FILE);
            continue;
        }

        /* Syntax parsing. */
        parse(file_name, linked_line);

        /* Free saved lines. */
        delete_linked_line(linked_line);
    }

    return EXIT_SUCCESS;
}
