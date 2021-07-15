#include <stdio.h>
#include "line.h"

Line *createLine()
{
    Line *new_line = calloc(1, sizeof(Line));

    if (new_line == NULL)
    {
        return NULL;
    }

    new_line->line = malloc(0);
    new_line->error_message = malloc(0);
    new_line->next = NULL;

    return new_line;
}

LinkedLine *createList()
{
    LinkedLine *list = calloc(1, sizeof(LinkedLine));

    if (list == NULL)
    {
        return NULL;
    }

    list->head = createLine();

    if (list->head == NULL)
    {
        return NULL;
    }

    return list;
}

void freeLinkedLine(LinkedLine *list)
{
    if (list != NULL)
    {
        Line *node = list->head;
        Line *next_node = node;

        while (node != NULL)
        {
            next_node = node->next;

            free(node);

            node = next_node;
        }

        free(list);
    }
}