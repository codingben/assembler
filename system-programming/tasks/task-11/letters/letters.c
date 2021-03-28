/*
 * Copyright (c) 2021 Ben Ukhanov. All rights reserved.
 */

#include <ctype.h>
#include <stdio.h>

/*
 * The program will receive input and output according to certain rules.
 */
int main()
{
    unsigned char character;
    unsigned char end_of_sentence = '.';
    unsigned char is_in_quote = 0;

    printf("Please enter a letter:\n\n");

    while (1)
    {
        int is_end_of_line = scanf("%c", &character) == EOF;
        int is_number = isdigit(character);          /* Check if the character is number */
        int is_quote = character == '"';             /* Check if the character is a quote */
        int is_period = end_of_sentence == '.';      /* Check if the character is period */
        int is_not_whitepsace = !isspace(character); /* Check if the character is not whitespace */
        int is_not_quote = character != '"';         /* Check if the character is not quote */

        if (is_end_of_line)
        {
            break;
        }

        if (is_number)
        {
            continue;
        }

        if (is_quote)
        {
            is_in_quote = is_in_quote ^ 1;
        }

        if (is_period || is_in_quote)
        {
            character = toupper(character);
        }
        else
        {
            character = tolower(character);
        }

        if (is_not_whitepsace)
        {
            if (is_not_quote)
            {
                end_of_sentence = character;
            }
        }

        printf("%c", character);
    }

    printf("\n\nProgram completed successfully.");
    return 0;
}