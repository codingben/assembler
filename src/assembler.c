#include <stdio.h>
#include "constants/logger.h"
#include "constants/messages.h"
#include "constants/boolean.h"
#include "utils/file_helper.h"
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
        LinkedLine *analyzed = NULL;
        int validated = FALSE;
        int parsed = FALSE;
        int compiled = FALSE;

        /* Steps:
         * 1. if (validated) analyze (scanner)
         * 2. if (analyzed) parse
         * 3. if (parsed) compile
         * 4. if (compiled) build 
         */

        /* Check if the assembly file has ".as" extension. */
        validated = validate_extension(file_name);

        if (validated == FALSE)
        {
            printf(ERROR_FORMAT, file_name, NO_AS_EXTENSION);
            continue;
        }

        /* Reading the assembly source code. */
        analyzed = analyze(file_name);

        if (analyzed == NULL)
        {
            printf(ERROR_FORMAT, file_name, FAILED_ANALYZE_FILE);
            continue;
        }

        /* Syntax parsing. */
        parsed = parse(file_name, analyzed);

        if (parsed)
        {
            /* TODO: compiled = compile(...) */
        }
        else
        {
            printf(ERROR_FORMAT, file_name, FAILED_ANALYZE_FILE);
            continue;
        }

        if (compiled)
        {
            /* TODO: Build object file (and other files if needed) */
        }

        /* Free saved lines. */
        delete_linked_line(analyzed);
    }

    return EXIT_SUCCESS;
}
