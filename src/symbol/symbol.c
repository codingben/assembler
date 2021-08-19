#include <stdlib.h>
#include <string.h>
#include "symbol.h"
#include "../constants/boolean.h"

Symbol *create_symbol()
{
    Symbol *symbol = malloc(sizeof(Symbol));

    if (symbol == NULL)
    {
        return NULL;
    }

    symbol->symbol_type = CODE;
    symbol->next = NULL;
    return symbol;
}

LinkedSymbol *create_linked_symbol()
{
    LinkedSymbol *linked_symbol = malloc(sizeof(LinkedSymbol));

    if (linked_symbol == NULL)
    {
        return NULL;
    }

    linked_symbol->head = NULL;
    return linked_symbol;
}

Symbol *add_symbol(LinkedSymbol *linked_symbol)
{
    Symbol *symbol = NULL;

    if (linked_symbol->head == NULL)
    {
        /* Create new symbol to set to the head. */
        symbol = create_symbol();

        /* Set the new symbol to the head. */
        linked_symbol->head = symbol;
    }
    else
    {
        /* Get the symbol from the first one. */
        symbol = linked_symbol->head;

        /* Iterate until the end symbol is reached. */
        while (symbol->next != NULL)
        {
            symbol = symbol->next;
        }

        /* Set the new symbol to the end of the linked list. */
        symbol->next = create_symbol();

        /* Set the new symbol to return it. */
        symbol = symbol->next;
    }

    return symbol;
}

void set_symbol_type(LinkedSymbol *linked_symbol, char *name, symbol_type type)
{
    Symbol *symbol = linked_symbol->head;

    for (; symbol != NULL; symbol = symbol->next)
    {
        if (strcmp(symbol->name, name) == 0)
        {
            symbol->symbol_type = type;
            break;
        }
    }
}

symbol_type get_symbol_type(LinkedSymbol *linked_symbol, char *name)
{
    Symbol *symbol = linked_symbol->head;

    for (; symbol != NULL; symbol = symbol->next)
    {
        if (strcmp(symbol->name, name) == 0)
        {
            return symbol->symbol_type;
        }
    }

    return DATA;
}

void set_symbol_value(LinkedSymbol *linked_symbol, char *name, unsigned int value)
{
    Symbol *symbol = linked_symbol->head;

    for (; symbol != NULL; symbol = symbol->next)
    {
        if (strcmp(symbol->name, name) == 0)
        {
            symbol->value = value;
        }
    }
}

int symbol_exists(LinkedSymbol *linked_symbol, char *name)
{
    Symbol *symbol = linked_symbol->head;

    for (; symbol != NULL; symbol = symbol->next)
    {
        if (strcmp(symbol->name, name) == 0)
        {
            return TRUE;
        }
    }

    return FALSE;
}

void delete_linked_symbol(LinkedSymbol *linked_symbol)
{
    Symbol *current_node = NULL;
    Symbol *next_node = NULL;

    if (linked_symbol == NULL)
    {
        return;
    }

    current_node = linked_symbol->head;
    next_node = current_node;

    /* Iterate until the end of linked list is reached. */
    while (current_node != NULL)
    {
        next_node = current_node->next;

        free(current_node);

        current_node = next_node;
    }

    free(linked_symbol);
}
