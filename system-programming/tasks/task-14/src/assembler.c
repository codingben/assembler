#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    int i;

    if (argc < 2)
    {
        printf("error: could not find a file to compile.\n");
        return 0;
    }

    for (i = 1; i < argc; ++i)
    {
        FILE *file;
        char character;
        char *extension;
        char *ext = ".as";

        printf("Read: %s\n\n", argv[i]);

        extension = strrchr(argv[i], '.');

        if (strcmp(extension, ext) != 0)
        {
            printf("The assembly file must be with .as extension.\n\n");
            continue;
        }

        /* Open the source file with the ".c" extension (e.g. prnt.c). */
        file = fopen(argv[i], "r");

        /* If something is wrong then print the error message. */
        if (file == NULL)
        {
            perror("Unable to open file");
            printf("\n");
            continue;
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

        printf("\n\n");

        fclose(file);
    }

    return 0;
}