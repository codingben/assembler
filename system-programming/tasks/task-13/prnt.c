/*
 * Copyright (c) 2021 Ben Ukhanov. All rights reserved.
 */

#include <stdio.h>
#include <string.h>

#define FILENAME_LENGTH 255

/* 
 * The program will print the entire content of the original file.
 *
 * How it works:
 * 1. Get the file name (e.g. ""./print").
 * 2. Copy the file name.
 * 3. Check if need to remove the ".exe" extension (e.g. "./print.exe" -> "./print").
 * 4. Try to open the file. If not, then print the error message.
 * 5. If the file is open, then print all the content.
 */
int main(int argc, char *argv[])
{
    FILE *file;

    char filename[FILENAME_LENGTH];
    char character;

    /* Copy the file name to new location. */
    strcpy(filename, argv[0]);

    /* Check if need to remove the ".exe" extension. */
#ifdef _WIN32
    char *temp;

    temp = strstr(filename, ".exe");

    if (temp)
    {
        *temp = '\0';
    }

    puts(filename);
#endif

    /* Open the source file with the ".c" extension (e.g. prnt.c). */
    file = fopen(strcat(filename, ".c"), "r");

    /* If something is wrong then print the error message. */
    if (file == NULL)
    {
        perror("Unable to open file");
        return -1;
    }

    /* Print all the file content. */
    while (1)
    {
        character = fgetc(file);

        if (character == EOF)
        {
            break;
        }

        printf("%c", character);
    }

    fclose(file);
    return 0;
}
