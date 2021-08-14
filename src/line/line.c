#include <stdlib.h>
#include <string.h>
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
        /* Create new line to set to the head. */
        line = create_line();

        /* Set the new line to the head. */
        linked_line->head = line;
    }
    else
    {
        /* Get the line from the first one. */
        line = linked_line->head;

        /* Iterate until the end line is reached. */
        while (line->next != NULL)
        {
            line = line->next;
        }

        /* Set the new line to the end of the linked list. */
        line->next = create_line();

        /* Set the new line to return it. */
        line = line->next;
    }

    return line;
}

void delete_linked_line(LinkedLine *linked_line)
{
    Line *current_node = NULL;
    Line *next_node = NULL;

    if (linked_line == NULL)
    {
        return;
    }

    current_node = linked_line->head;
    next_node = current_node;

    /* Iterate until the end of linked list is reached. */
    while (current_node != NULL)
    {
        next_node = current_node->next;

        free(current_node);

        current_node = next_node;
    }

    free(linked_line);
}
