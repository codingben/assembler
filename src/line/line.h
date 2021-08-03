#ifndef LINE_H
#define LINE_H

#define ASM_MAX_LINE_LENGTH 81 /* The last character is '\n' */
#define ERROR_MAX_LINE_LENGTH 120
#define MAX_LABEL_LENGTH 31
#define MAX_COMMAND_LENGTH 5
#define MAX_DIRECTIVE_LENGTH 10
#define COMMANDS_SIZE 27
#define DIRECTIVES_SIZE 6

typedef struct
{
    char name[MAX_COMMAND_LENGTH];
} Command;

static const Command commands[COMMANDS_SIZE] = {
    {"add"},
    {"sub"},
    {"and"},
    {"or"},
    {"nor"},
    {"move"},
    {"mvhi"},
    {"mvlo"},
    {"addi"},
    {"subi"},
    {"andi"},
    {"ori"},
    {"nori"},
    {"bne"},
    {"beq"},
    {"blt"},
    {"bgt"},
    {"lb"},
    {"sb"},
    {"lw"},
    {"sw"},
    {"lh"},
    {"sh"},
    {"jmp"},
    {"la"},
    {"call"},
    {"stop"}};

typedef struct
{
    char name[MAX_DIRECTIVE_LENGTH];
} Directive;

static const Directive directives[DIRECTIVES_SIZE] = {
    {".db"},
    {".dw"},
    {".dh"},
    {".asciz"},
    {".entry"},
    {".extern"}};

typedef enum
{
    EMPTY,
    COMMENT,
    COMMAND,
    DIRECTIVE
} statement_type;

typedef struct line
{
    char text[ASM_MAX_LINE_LENGTH];
    int line_number;
    int has_error;
    char error_message[ERROR_MAX_LINE_LENGTH];
    statement_type statement_type;
    char label[MAX_LABEL_LENGTH];
    char command[MAX_COMMAND_LENGTH];
    char directive[MAX_DIRECTIVE_LENGTH];
    struct line *next;
    /* TODO: error list (message, column). but, one error is enough */
} Line;

typedef struct linked_line
{
    Line *head;
} LinkedLine;

Line *create_line();

LinkedLine *create_linked_line();

Line *add_line(LinkedLine *linked_line);

void delete_linked_line(LinkedLine *linked_line);

char *copy_line(Line *line);

#endif
