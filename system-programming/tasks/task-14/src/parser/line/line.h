#ifndef LINE_H
#define LINE_H

typedef struct line
{
    char *line;
    int line_number;
    int has_error;
    char *error_message;
    int error_column;
    struct line *next;
    /* TODO: error list (message, column) but one error is enough */
} Line;

typedef struct linked_line
{
    Line *head;
} LinkedLine;

Line *create_line();

LinkedLine *create_linked_line();

void free_linked_line();

#endif