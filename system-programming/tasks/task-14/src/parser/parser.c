#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../constants/logger.h"
#include "../constants/messages.h"
#include "../constants/rules.h"
#include "line/line.h"

LinkedLine *parse_buffer(char *buffer)
{
    int i;
    int line_number = 1;

    LinkedLine *linked_line = create_linked_line();
    Line *line;

    if (linked_line == NULL)
    {
        return NULL;
    }

    line = linked_line->head;

    for (i = 0; i < strlen(buffer); i++)
    {
        /* Add characters to the line */
        strncat(line->text, &buffer[i], 1);

        /* TODO: When will happen when you reach the end of the line_buffer? */
        /* TODO: Raise an error saying no more than 80 characters allowed? */

        /* If line end is reached, then save it and reset it */
        if (buffer[i] == '\n')
        {
            Line *new_line = create_line();
            line->line_number = line_number;
            line->next = new_line;
            line = new_line;

            line_number = line_number + 1;

            /* It works, but when there's '\n' (empty line) and it's not called therefore you get 0 by default */
        }
    }

    return linked_line;
}

int analyze(const char *filename, LinkedLine *linked_line)
{
    /* TODO: Analyze syntax, and collect error(s) */
    /* TODO: Iterate here to get the column index */
    /* TODO: (Lexer) Break the line into words (e.g. word[0] = 'MOV', word[1] = "$1, *, ...) */
    /* TODO: (Lexer) Breaking the line can be done with checking for spaces between words. */
    /* TODO: Get a word like 'MOVAB' then you see that is not equal to 'MOV' (then throw an error) */
    /* TODO: When got ';' then remove it until reaches '\n' */
    /* TODO: Remove empty whitespaces? so in case the analyzer won't throw an error for 'MOV' != ' ' empty space */

    Line *line = linked_line->head;
    int i = 0;

    /* Print all saved lines */
    /* Should used for analyzation */
    for (; line != NULL; line = line->next)
    {
        /* Iterate over saved line (the characters) */
        /* Use it to analyze the characters of the line (e.g. skip ";", etc) */
        for (i = 0; i < strlen(line->text); ++i)
        {
            /* TODO: Set has error (true or false) */
            /* TODO: Set error message */
            /* TODO: Set error column (error_column = i) */
        }

        /* Print the line */
        printf(LOG_LINE_FORMAT, filename, line->line_number, line->text);
    }

    return 0;
}

LinkedLine *parse_file(FILE *file, const char *filename)
{
    /* Read all the file into a buffer */
    /* Then parse it and on each '\n' character add new line */
    /* The goal is to analyze all the lines for errors and print all of them */
    /* One error for each line is enough */

    char *buffer;
    long file_length;
    LinkedLine *linked_line;

    /* Jump to the end of the file */
    fseek(file, 0, SEEK_END);

    /* Get the current byte offset in the file */
    file_length = ftell(file);

    /* Jump back to the beginning of the file */
    rewind(file);

    /* Enough memory for the file */
    buffer = (char *)malloc(file_length * sizeof(char));

    /* Read in the entire file */
    fread(buffer, file_length, 1, file);

    /* Parse the buffer from file */
    linked_line = parse_buffer(buffer);

    /* Free buffer from the memory */
    free(buffer);

    /* Return parsed lines */
    return linked_line;
}

int parse(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    LinkedLine *linked_line;

    if (file != NULL)
    {
        /* Parse file to analyze syntax */
        linked_line = parse_file(file, filename);

        if (linked_line == NULL)
        {
            return 1;
        }

        /* Analyze syntax */
        analyze(filename, linked_line);

        /* Free analyzed lines */
        free_linked_line(linked_line);

        /* Close file after parsing */
        fclose(file);
    }
    else
    {
        perror(FAILED_OPEN_FILE);
    }

    return 0;
}