#ifndef VALIDATOR_H
#define VALIDATOR_H

int is_empty_line(char *value);

int is_comment_line(char *value);

int is_label(char *value);

int is_label_empty(char *value);

int is_label_above_max_length(char *value);

int is_label_equals_command(char *value);

int is_label_equals_directive(char *value);

int is_command(char *value);

int is_directive(char *value);

int is_register(char *value);

int is_number(char *value);

int is_register_exists(char *value);

int is_quotation_mark(char *value);

int is_extern(char *value);

int is_entry(char *value);

int is_asciz(char *value);

int is_db(char *value);

int is_dh(char *value);

int is_dw(char *value);

#endif
