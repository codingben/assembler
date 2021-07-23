#include <stdlib.h>
#include "line.h"

Line *create_line()
{
    Line *line = malloc(sizeof(Line));

    if (line == NULL)
    {
        return NULL;
    }

    line->next = NULL;
    return line;
}

LinkedLine *create_linked_line()
{
    LinkedLine *linked_line = malloc(sizeof(LinkedLine));

    if (linked_line == NULL)
    {
        return NULL;
    }

    linked_line->head = NULL;
    return linked_line;
}

Line *add_line(LinkedLine *linked_line)
{
    Line *line = NULL;

    if (linked_line->head == NULL)
    {
        line = create_line();

        linked_line->head = line;
    }
    else
    {
        line = linked_line->head;

        while (line->next != NULL)
        {
            line = line->next;
        }

        line->next = create_line();
        line = line->next;
    }

    return line;
}

void delete_linked_line(LinkedLine *linked_line)
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

        free(current_node);

        current_node = next_node;
    }

    free(linked_line);
}