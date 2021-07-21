#include <stdio.h>
#include <stdlib.h>
#include "../../constants/rules.h"
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
    Line *line;
    LinkedLine *linked_line = malloc(sizeof(LinkedLine));

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

        if (current_node->text != NULL)
        {
            free(current_node->text);
        }

        if (current_node->error_message != NULL)
        {
            free(current_node->error_message);
        }

        free(current_node);

        current_node = next_node;
    }

    free(linked_line);
}