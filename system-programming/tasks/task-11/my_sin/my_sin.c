/*
 * Copyright (c) 2021 Ben Ukhanov. All rights reserved.
 */

#include <stdio.h>
#include <math.h>

double factorial(int x)
{
    int i = 0;
    double result = 1;

    for (i = 1; i <= x; i++)
    {
        result = result * i;
    }

    return result;
}

double power(double x, int y)
{
    int i = 0;
    double result = 1;

    for (i = 1; i <= y; i++)
    {
        result = result * x;
    }

    return result;
}

double my_sin(double x)
{
    int i = 0;
    double result = 0;

    for (i = 0; i < 8; i++)
    {
        result = result + power(-1, i) * power(x, 2 * i + 1) / factorial(2 * i + 1);
    }

    return result;
}

/*
 * The program calculates the sine using Taylor's formula.
 */
int main()
{
    double user_input;

    printf("Enter a value to calculate the sine:\n\n");

    scanf("%lf", &user_input);

    printf("my_sin(%f) = %f\n", user_input, my_sin(user_input));
    printf("sin(%f) = %f\n", user_input, sin(user_input));

    printf("\nProgram completed successfully.");
    return 0;
}