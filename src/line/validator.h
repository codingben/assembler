#ifndef VALIDATOR_H
#define VALIDATOR_H

int is_empty_line(char *value);

int is_comment_line(char *value);

int is_error_message_empty(char *value);

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

int is_arthematic_logic_r_instructions(char *name);

int is_copy_r_instructions(char *name);

int is_arthematic_logic_i_instructions(char *name);

int is_conditional_branching_i_instructions(char *name);

int is_load_save_i_instructions(char *name);

int is_stop_instruction(char *name);

int is_j_instruction_except_stop(char *name);

#endif
