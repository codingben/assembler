/*
 * Copyright (c) 2021 Ben Ukhanov. All rights reserved.
 */

#include "../line/line.h"

#ifndef LINE_HELPER_H
#define LINE_HELPER_H

char *duplicate(char *value);

void remove_whitespaces(char *value);

void remove_new_line_character(char *value);

void remove_quotation_marks(char *value);

char *remove_last_character(char *value);

int find_register(char *value);

instruction_type find_type(char *name);

int find_funct(char *name);

int find_opcode(char *name);

char *convert_asciz_to_hex(char *data);

char *convert_db_to_hex(char *data);

char *convert_dh_to_hex(char *data);

char *convert_dw_to_hex(char *data);

#endif
