/*
 * Copyright (c) 2021 Ben Ukhanov. All rights reserved.
 */

#ifndef MESSAGES_H
#define MESSAGES_H

#define NO_FILE_TO_COMPILE "error: could not find an assembly file to compile.\n"
#define NO_AS_EXTENSION "an assembly file must be with .as extension.\n"
#define FAILED_ANALYZE_FILE "unable to analyze the assembly file.\n"
#define FAILED_TRANSLATE_FILE "unable to translate the assembly file.\n"
#define GENERATION_FAILED "unable to generate output files.\n"
#define MAX_LENGTH_LABEL "label length has reached its limit.\n"
#define MAX_EQUALS_COMMAND "label cannot be command.\n"
#define MAX_EQUALS_DIRECTIVE "label cannot be directive.\n"
#define INVALID_DEFINITION "unrecognized definiton: %s\n"
#define NO_OPERANDS_FOUND "could not find operands.\n"
#define NO_INSTRUCTION_OPERANDS "no operands can be used for this instruction.\n"
#define ONE_OPERAND_OR_LABEL "only one operand or label can be used.\n"
#define NO_LABEL_FOUND "no label found.\n"
#define NO_LABEL_DEFINED "no label `%s` defined.\n"
#define NO_INSTRUCTION_FOUND "no instruction found.\n"

#endif
