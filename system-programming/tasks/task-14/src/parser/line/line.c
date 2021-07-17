#include <stdio.h>
#include <stdlib.h>
#include "../../constants/rules.h"
#include "line.h"

Line *create_line()
{
    Line *line = calloc(1, sizeof(Line));

    if (line == NULL)
    {
        return NULL;
    }

    line->text = malloc(MAX_LINE_LENGTH);
    line->error_message = malloc(0); /* TODO: Set error message size */
    line->next = NULL;
    return line;
}

LinkedLine *create_linked_line()
{
    Line *line;
    LinkedLine *linked_line = calloc(1, sizeof(LinkedLine));

    if (linked_line == NULL)
    {
        return NULL;
    }

    line = create_line();

    if (line == NULL)
    {
        return NULL;
    }

    linked_line->head = line;
    return linked_line;
}

void free_linked_line(LinkedLine *linked_line)
{
    Line *current_node;
    Line *next_node;

    if (linked_line == NULL)
    {
        return;
    }

    current_node = linked_line->head;
    next_node = current_node;

    while (current_node != NULL)
    {
        next_node = current_node->next;

        free(current_node->text);
        free(current_node->error_message);
        free(current_node);

        current_node = next_node;
    }

    free(linked_line);
}