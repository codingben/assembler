#include <stdio.h>
#include "constants/logger.h"
#include "constants/messages.h"
#include "utils/file.h"
#include "scanner/analyzer.h"
#include "parser/parser.h"

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

int main(int argument_count, char **argument_vector)
{
    int i;
    const char *file_name = argument_vector[0];
    LinkedLine *linked_line;

    if (argument_count < 2)
    {
        printf(NO_FILE_TO_COMPILE);
        printf("#---------------------------------------------------#\n");
        return EXIT_FAILURE;
    }

    for (i = 1; i < argument_count; ++i)
    {
        file_name = argument_vector[i];

        /* Steps:
         * 1. if (validated) analyze (scanner)
         * 2. if (analyzed) parse
         * 3. if (parsed) compile
         * 4. if (compiled) build 
         */

        if (validate_extension(file_name) != 0)
        {
            printf(ERROR_FORMAT, file_name, NO_AS_EXTENSION);
            printf("#---------------------------------------------------#\n");
            continue;
        }

        /* Scanner analysis */
        linked_line = analyze(file_name);

        if (linked_line == NULL)
        {
            /* TODO: Add error message here */
            continue;
        }

        /* Syntax parsing */
        parse(file_name, linked_line);

        /* Free saved lines */
        delete_linked_line(linked_line);

        /* Add space for a new file */
        printf("#---------------------------------------------------#\n");
    }

    return EXIT_SUCCESS;
}