#ifndef PARSER_H
#define PARSER_H

int parse_file(FILE *file, const char *filename);

int parse_line(const char *filename, char *line, int line_index);

#endif