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
#include "translator/translator.h"
#include "generator/generator.h"

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
        int analyzed = FALSE;
        int parsed = FALSE;
        int translated = FALSE;

        /* Steps:
         * 1. if (validated) analyze (scanner)
         * 2. if (analyzed) parse
         * 3. if (parsed) translate
         * 4. if (translated) generate
         */

        printf("# File: %s\n", file_name);
        printf("# Validating...\n");

        /* Check if the assembly file has ".as" extension. */
        validated = validate_extension(file_name);

        if (validated == FALSE)
        {
            printf(ERROR_FORMAT, file_name, NO_AS_EXTENSION);
            continue;
        }

        printf("# Analyzing...\n");

        /* Read the assembly source code. */
        linked_line = analyze(file_name);

        /* Create symbol table. */
        linked_symbol = create_linked_symbol();

        /* Check if analyzed and symbol table created. */
        analyzed = linked_line != NULL && linked_symbol != NULL;

        if (analyzed)
        {
            printf("# Parsing...\n");

            /* Parse the syntax. */
            parsed = parse(file_name, linked_line, linked_symbol);

            if (parsed)
            {
                printf("# Translating...\n");

                /* Translate the parsed syntax. */
                translated = translate(linked_line, linked_symbol);

                if (translated)
                {
                    printf("# Generating...\n");

                    if (generate(linked_line, linked_symbol))
                    {
                        printf("# Generated.\n");
                    }
                }
                else
                {
                    printf(ERROR_FORMAT, file_name, FAILED_TRANSLATE_FILE);
                }
            }
        }
        else
        {
            printf(ERROR_FORMAT, file_name, FAILED_ANALYZE_FILE);
        }

        delete_linked_line(linked_line);
        delete_linked_symbol(linked_symbol);
    }

    return EXIT_SUCCESS;
}
