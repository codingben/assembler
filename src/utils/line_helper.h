#include "../line/line.h"

#ifndef LINE_HELPER_H
#define LINE_HELPER_H

char *duplicate(char *value);

void remove_whitespaces(char *value);

void remove_new_line_character(char *value);

void remove_quotation_marks(char *value);

char *remove_last_character(char *value);

int find_register(char *value);

command_type find_command_type(char *name);

int find_command_funct(char *name);

int find_command_opcode(char *name);

#endif
