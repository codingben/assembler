#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "rules.h"
#include "messages.h"
#include "logger.h"
#include "line.h"

/* 
 * Data Structure: Line
 * Data Structure implementation: Linked List
 * 
 * line.h
 * linked_line.h
 */

/* File name shouldn't be here */
int parse_buffer(char *buffer, const char *filename)
{
    /* TODO: Analyze syntax, and collect error(s) */
    /* TODO: Iterate here to get the column index */

    LinkedLine *line_list = createList();

    /*if (line_list == NULL)
    {
        return 1;
    }*/

    Line *current_line = line_list->head;
    Line *cur_line = line_list->head;

    char line_buffer[MAX_LINE_LENGTH];
    int line_number = 1;
    int i;

    for (i = 0; i < strlen(buffer); i++)
    {
        /* Add characters to the line */
        strncat(line_buffer, &buffer[i], 1);

        /* If line end is reached, then save it and reset it */
        if (buffer[i] == '\n')
        {
            /* Creates a new line */
            Line *new_line = createLine();

            /* Copy line buffer to saved line */
            memcpy(current_line->line, line_buffer, sizeof(current_line->line) + 1);

            /* Set line number */
            current_line->line_number = line_number;

            /* Set next new line */
            current_line->next = new_line;

            /* Set new line */
            current_line = new_line;

            /* Increment line number */
            line_number++;

            /* Clear line buffer */
            memset(line_buffer, 0, sizeof(line_buffer) + 1);
        }
    }

    /* Print all saved lines */
    /* Should used for analyzation */
    for (; cur_line != NULL; cur_line = cur_line->next)
    {
        int i = 0;
        char text[MAX_LINE_LENGTH];

        /* Iterate over saved line (the characters) */
        /* Use it to analyze the characters of the line (e.g. skip ";", etc) */
        for (i = 0; i < strlen(cur_line->line); ++i)
        {
            strncat(text, &cur_line->line[i], 1);

            /* TODO: Set has error (true or false) */
            /* TODO: Set error message */
            /* TODO: Set error column (error_column = i) */
        }

        /* Print the line */
        printf(LOG_LINE_FORMAT, filename, cur_line->line_number, text);

        /* Clear line buffer */
        memset(text, 0, sizeof(text));
    }

    freeList(line_list);
    return 0;
}

int parse_file(FILE *file, const char *filename)
{
    /* Read all the file into a buffer */
    /* Then parse it and on each '\n' character add new line */
    /* The goal is to analyze all the lines for errors and print all of them */
    /* One error for each line is enough */

    char *buffer;
    long file_length;

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
    parse_buffer(buffer, filename);

    /* Free buffer from the memory */
    free(buffer);
    return 0;
}

int parse(const char *filename)
{
    FILE *file = fopen(filename, "rb");

    if (file != NULL)
    {
        /* Parse file to analyze syntax */
        parse_file(file, filename);

        /* Close file after parsing */
        fclose(file);
    }
    else
    {
        perror(FAILED_OPEN_FILE);
    }

    return 0;
}