/*
 * Copyright (c) 2021 Ben Ukhanov. All rights reserved.
 */

#include "../symbol/symbol.h"

#ifndef PARSER_H
#define PARSER_H

int parse(const char *file_name, LinkedLine *linked_line, LinkedSymbol *linked_symbol);

#endif
