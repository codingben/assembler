#ifndef LINE_H
#define LINE_H

#define ASM_MAX_LINE_LENGTH 81 /* The last character is '\n' */
#define ERROR_MAX_LINE_LENGTH 120
#define MAX_LABEL_LENGTH 31
#define MAX_COMMAND_LENGTH 5
#define MAX_DIRECTIVE_LENGTH 10
#define MAX_REGISTER_LENGTH 3
#define COMMANDS_SIZE 27
#define DIRECTIVES_SIZE 6
#define REGISTER_SIZE 32
#define MAX_OPERANDS_SIZE 80

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

typedef struct
{
    char name[MAX_REGISTER_LENGTH];
    int number;
} Register;

static const Register registers[] = {
    {"$0", 0},
    {"$1", 1},
    {"$2", 2},
    {"$3", 3},
    {"$4", 4},
    {"$5", 5},
    {"$6", 6},
    {"$7", 7},
    {"$8", 8},
    {"$9", 9},
    {"$10", 10},
    {"$11", 11},
    {"$12", 12},
    {"$13", 13},
    {"$14", 14},
    {"$15", 15},
    {"$16", 16},
    {"$17", 17},
    {"$18", 18},
    {"$19", 19},
    {"$20", 20},
    {"$21", 21},
    {"$22", 22},
    {"$23", 23},
    {"$24", 24},
    {"$25", 25},
    {"$26", 26},
    {"$27", 27},
    {"$28", 28},
    {"$29", 29},
    {"$30", 30},
    {"$31", 31}};

typedef struct line
{
    char text[ASM_MAX_LINE_LENGTH];
    int line_number;
    char error_message[ERROR_MAX_LINE_LENGTH];
    statement_type statement_type;
    char label[MAX_LABEL_LENGTH];
    char command[MAX_COMMAND_LENGTH];
    char directive[MAX_DIRECTIVE_LENGTH];
    char operands[MAX_OPERANDS_SIZE][MAX_OPERANDS_SIZE];
    int operands_count;
    struct line *next;
} Line;

typedef struct linked_line
{
    Line *head;
} LinkedLine;

Line *create_line();

LinkedLine *create_linked_line();

Line *add_line(LinkedLine *linked_line);

void delete_linked_line(LinkedLine *linked_line);

#endif
