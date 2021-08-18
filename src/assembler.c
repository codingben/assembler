/*
 * Copyright (c) 2021 Ben Ukhanov. All rights reserved.
 */

#include <stdio.h>
#include "constants/logger.h"
#include "constants/messages.h"
#include "constants/boolean.h"
#include "utils/file_helper.h"
#include "scanner/analyzer.h"
#include "parser/parser.h"
#include "symbol/symbol.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
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
        LinkedSymbol *linked_symbol = NULL;
        LinkedLine *linked_line = NULL;
        int validated = FALSE;
        int parsed = FALSE;
        int translated = FALSE;

        /* Steps:
         * 1. if (validated) analyze (scanner)
         * 2. if (analyzed) parse
         * 3. if (parsed) translate
         * 4. if (translated) build 
         */

        printf("# Validating File: %s\n", file_name);

        /* Check if the assembly file has ".as" extension. */
        validated = validate_extension(file_name);

        if (validated == FALSE)
        {
            printf(ERROR_FORMAT, file_name, NO_AS_EXTENSION);
            continue;
        }

        printf("# Analyzing File: %s\n", file_name);

        /* Reading the assembly source code. */
        linked_line = analyze(file_name);

        if (linked_line == NULL)
        {
            printf(ERROR_FORMAT, file_name, FAILED_ANALYZE_FILE);
            continue;
        }

        /* Syntax parsing. */
        linked_symbol = create_linked_symbol();

        if (linked_symbol == NULL)
        {
            printf(ERROR_FORMAT, file_name, FAILED_ANALYZE_FILE);
            continue;
        }

        printf("# Parsing File: %s\n", file_name);

        parsed = parse(file_name, linked_line, linked_symbol);

        if (parsed)
        {
            /* TODO: compiled = compile(...) */
        }
        else
        {
            printf(ERROR_FORMAT, file_name, FAILED_ANALYZE_FILE);
            continue;
        }

        if (translated)
        {
            /* TODO: Build object file (and other files if needed) */
        }

        delete_linked_line(linked_line);
        delete_linked_symbol(linked_symbol);
    }

    return EXIT_SUCCESS;
}
