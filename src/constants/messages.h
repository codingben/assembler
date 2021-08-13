#ifndef MESSAGES_H
#define MESSAGES_H

#define NO_FILE_TO_COMPILE "error: could not find an assembly file to compile.\n"
#define NO_AS_EXTENSION "an assembly file must be with .as extension.\n"
#define FAILED_ANALYZE_FILE "unable to analyze the assembly file.\n" /* No need '\n' here because used in perror(...). */
#define MAX_LENGTH_LABEL "label length has reached its limit.\n"
#define MAX_EQUALS_COMMAND "label cannot be command.\n"
#define MAX_EQUALS_DIRECTIVE "label cannot be directive.\n"
#define INVALID_DEFINITION "unrecognized definiton: %s\n"
#define NO_OPERANDS_FOUND "could not find operands.\n"
#define ONLY_ZERO_OPERAND "only $0 register can be used for `call` command.\n"
#define ONLY_ONE_OPERAND "only one operand required.\n"
#define NO_LABEL_FOUND "no label found.\n"

#endif
