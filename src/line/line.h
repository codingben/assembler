#ifndef LINE_H
#define LINE_H

#define ASM_MAX_LINE_LENGTH 81 /* The last character is '\n' */
#define ERROR_MAX_LINE_LENGTH 120
#define MAX_LABEL_LENGTH 30
#define MAX_COMMAND_LENGTH 5
#define MAX_DIRECTIVE_LENGTH 10
#define MAX_REGISTER_LENGTH 3
#define COMMANDS_SIZE 27
#define DIRECTIVES_SIZE 6
#define REGISTER_SIZE 32
#define MAX_OPERANDS_SIZE 80

typedef struct
{
    unsigned int opcode : 6;
    unsigned int rs : 5;
    unsigned int rt : 5;
    unsigned int rd : 5;
    unsigned int funct : 5;
    unsigned int unused : 6;
} R_Instruction;

typedef struct
{
    unsigned int opcode : 6;
    unsigned int rs : 5;
    unsigned int rt : 5;
    unsigned int immed : 16;
} I_Instruction;

typedef struct
{
    unsigned int opcode : 6;
    unsigned int reg : 1;
    unsigned int address : 25;
} J_Instruction;

typedef enum
{
    R,
    I,
    J
} instruction_type;

typedef struct
{
    char name[MAX_COMMAND_LENGTH];
    instruction_type instruction_type;
    int funct;
    int opcode;
} Command;

static const Command commands[COMMANDS_SIZE] = {
    {"add", R, 1, 0},
    {"sub", R, 2, 0},
    {"and", R, 3, 0},
    {"or", R, 4, 0},
    {"nor", R, 5, 0},
    {"move", R, 1, 1},
    {"mvhi", R, 2, 1},
    {"mvlo", R, 3, 1},
    {"addi", I, 0, 10},
    {"subi", I, 0, 11},
    {"andi", I, 0, 12},
    {"ori", I, 0, 13},
    {"nori", I, 0, 14},
    {"bne", I, 0, 15},
    {"beq", I, 0, 16},
    {"blt", I, 0, 17},
    {"bgt", I, 0, 18},
    {"lb", I, 0, 19},
    {"sb", I, 0, 20},
    {"lw", I, 0, 21},
    {"sw", I, 0, 22},
    {"lh", I, 0, 23},
    {"sh", I, 0, 24},
    {"jmp", J, 0, 30},
    {"la", J, 0, 31},
    {"call", J, 0, 32},
    {"stop", J, 0, 63}};

typedef struct
{
    char name[MAX_DIRECTIVE_LENGTH];
} Directive;

static const Directive directives[DIRECTIVES_SIZE] = {
    {".db"},
    {".dh"},
    {".dw"},
    {".asciz"},
    {".entry"},
    {".extern"}};

typedef enum
{
    UNKNOWN_STATEMENT,
    EMPTY,
    COMMENT,
    COMMAND, /* Rename it to opcode (or something else) */
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
    char command[MAX_COMMAND_LENGTH];     /* remove it and make instruction only */
    char directive[MAX_DIRECTIVE_LENGTH]; /* remove it and make instruction only */
    char operands[MAX_OPERANDS_SIZE][MAX_OPERANDS_SIZE];
    int operands_count;
    unsigned int address;
    R_Instruction r_instruction;
    I_Instruction i_instruction;
    J_Instruction j_instruction;
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
