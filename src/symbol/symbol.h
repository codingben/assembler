#ifndef SYMBOL_H
#define SYMBOL_H

#define NAME_LENGTH 31

typedef struct symbol
{
    char name[NAME_LENGTH];
    struct symbol *next;
} Symbol;

typedef struct linked_symbol
{
    Symbol *head;
} LinkedSymbol;

Symbol *create_symbol();

LinkedSymbol *create_linked_symbol();

Symbol *add_symbol(LinkedSymbol *linked_symbol);

int symbol_exists(LinkedSymbol *linked_symbol, char *name);

void delete_linked_symbol(LinkedSymbol *linked_symbol);

#endif
