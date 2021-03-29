/*
 * Copyright (c) 2021 Ben Ukhanov. All rights reserved.
 */

#include <stdio.h>
#include <math.h>

/*
 * Returns x factorial as an integer.
 */
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

/*
 * Returns x raised to the power of y.
 */
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

/*
 * Returns the sine of a radian angle x.
 */
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

    printf("Enter value (between -25.0 to 25.0) to calculate the sine:\n");

    scanf("%lf", &user_input);

    if (user_input < -25.0 || user_input > 25.0)
    {
        printf("The input value must be between -25.0 and 25.0.");
        return 0;
    }

    printf("\nmy_sin(%f) = %f", user_input, my_sin(user_input));
    printf("\nsin(%f) = %f", user_input, sin(user_input));

    printf("\n\nProgram completed successfully.");
    return 0;
}