#ifndef SYMBOL_H
#define SYMBOL_H

#define NAME_LENGTH 31

typedef enum
{
    CODE,
    DATA,
    ENTRY,
    EXTERNAL
} symbol_type;

typedef struct symbol
{
    char name[NAME_LENGTH];
    unsigned int value;
    symbol_type symbol_type;
    struct symbol *next;
} Symbol;

typedef struct linked_symbol
{
    Symbol *head;
} LinkedSymbol;

Symbol *create_symbol();

LinkedSymbol *create_linked_symbol();

Symbol *add_symbol(LinkedSymbol *linked_symbol);

void set_symbol_type(LinkedSymbol *linked_symbol, char *name, symbol_type type);

symbol_type get_symbol_type(LinkedSymbol *linked_symbol, char *name);

void set_symbol_value(LinkedSymbol *linked_symbol, char *name, unsigned int value);

int symbol_exists(LinkedSymbol *linked_symbol, char *name);

void delete_linked_symbol(LinkedSymbol *linked_symbol);

#endif
