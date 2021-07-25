#include <stdio.h>
#include <string.h>
#include "../constants/logger.h"
#include "../constants/messages.h"
#include "../line/line.h"

LinkedLine *analyze(const char *file_name)
{
    FILE *file;
    LinkedLine *linked_line;
    char text[ASM_MAX_LINE_LENGTH];
    int line_number = 1;

    file = fopen(file_name, "r");

    if (file == NULL)
    {
        return NULL;
    }

    linked_line = create_linked_line();

    if (linked_line == NULL)
    {
        return NULL;
    }

    /* Analyze the assembly file for syntax parsing. */
    while (fgets(text, ASM_MAX_LINE_LENGTH, file) != NULL)
    {
        /* Add the new line to the linked lines. */
        Line *line = add_line(linked_line);

        /* Copy line text from the file to the new line. */
        memcpy(line->text, text, strlen(text) + 1);

        /* Set the line number of the copied line. */
        line->line_number = line_number;
        line_number++;
    }

    /* Close file after analyzing. */
    fclose(file);

    /* Linked lines for syntax parsing. */
    return linked_line;
}
