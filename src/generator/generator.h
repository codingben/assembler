/*
 * Copyright (c) 2021 Ben Ukhanov. All rights reserved.
 */

#include "../line/line.h"
#include "../symbol/symbol.h"

#ifndef GENERATOR_H
#define GENERATOR_H

int generate(const char *file_name, LinkedLine *linked_line, LinkedSymbol *linked_symbol);

#endif