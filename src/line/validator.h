#ifndef VALIDATOR_H
#define VALIDATOR_H

int is_empty_line(char value);

int is_comment_line(char value);

int is_label(char *value);

int is_label_above_max_length(char *value);

int is_label_equals_command(char *value);

int is_label_equals_directive(char *value);

int is_command(char *value);

int is_directive(char *value);

int is_register(char *value);

#endif
