/*
 * Copyright (c) 2021 Ben Ukhanov. All rights reserved.
 */

#ifndef FILE_HELPER_H
#define FILE_HELPER_H

#define FILENAME_LENGTH 255
#define ASSEMBLY_EXTENSION ".as"
#define OBJECT_FILE_EXTENSION ".ob"
#define EXTERNAL_FILE_EXTENSION ".ext"
#define ENTRY_FILE_EXTENSION ".ent"

int validate_extension(const char *filename);

char *rename_file_name_extension(const char *file_name, const char *extension);

FILE *open_file(const char *file_name, const char *extension);

#endif
