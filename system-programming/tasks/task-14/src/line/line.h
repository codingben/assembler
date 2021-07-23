#ifndef LINE_H
#define LINE_H

#define ASM_MAX_LINE_LENGTH 81 /* The last character is '\n' */
#define ERROR_MAX_LINE_LENGTH 120

typedef struct line
{
    char text[ASM_MAX_LINE_LENGTH];
    int line_number;
    int has_error;
    char error_message[ERROR_MAX_LINE_LENGTH];
    int error_column;
    struct line *next;
    /* TODO: error list (message, column). but, one error is enough */
} Line;

typedef struct linked_line
{
    Line *head;
} LinkedLine;

Line *create_line();

LinkedLine *create_linked_line();

Line *add_line(LinkedLine *linked_line);

void delete_linked_line(LinkedLine *linked_line);

#endif