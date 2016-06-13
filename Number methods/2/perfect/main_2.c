#include <stdio.h>
#include <stdlib.h>
#include <math.h>

///определяем граничные условия
///A11 * y (LEFT) + A12 * y'(RIGHT) = B1
///A21 * y (LEFT) + A22 * y'(RIGHT) = B2
#define LEFT 0.0
#define RIGHT 1.0
#define A11 1.0
#define A12 -1.0
#define B1 0
#define A21 1.0
#define A22 0.0
#define B2 3.718


double H;
int SIZE;

///======================COEFFICIENTS_OF_EQUATION==========================
///=====================y" + p(x) * y' + q(x) * y = r(x)===================

double sol (double x);

double p_func (double x);

double q_func (double x);

double r_func (double x);

///==========================FUNCTION_TO_FIND_Y=============================

void tridiagonal_solution (double alpha[SIZE + 1], double betta[SIZE + 1], double y[SIZE + 1]);

///=================================OUTPUT==================================

void print (double y[SIZE + 1]);

///===============================MAIN======================================

int main(void)
{
    printf("\nINPUT:\n");
    printf("    1)NUMBER_OF_STEPS: ");
    scanf("%d", &SIZE);
    printf("\nOUTPUT:\n");
    H = (RIGHT - LEFT) / SIZE;

    double alpha[SIZE + 1], betta[SIZE + 1], y[SIZE + 1];

    tridiagonal_solution(alpha, betta, y);
    print(y);

    return 0;
}

///==========================FUNCTION's_BODIES==============================

double p_func (double x)
{
    return (-1) * 2.0 * x;
}

double q_func (double x)
{
    return (-1) * 2.0;
}

double r_func (double x)
{
    return (-1) * 4.0 * x;
}

double sol (double x)
{
   return x + exp(x * x);
}

void print (double y[SIZE + 1])
{
    int i;
    double x = LEFT;

    for (i = 0; i < (SIZE + 1); i++)
    {
        printf("x: %3.3f counted: %5.5f given: %5.5f\n", x, y[i], sol(x));
        x += H;
    }
}

void tridiagonal_solution (double alpha[SIZE + 1], double betta[SIZE + 1], double y[SIZE + 1])
{
    int i;
    double x = LEFT + H, a, b, c;

    ///прямой ход

    ///определяем нач. значения исходя из левого граничного условия
    alpha[0] = A12 / (A12 - A11 * H);
    betta[0] = (B1 * H) / (A11 * H - A12);

    for (i = 1; i < (SIZE + 1); i++)
    {
        a = (1 / H - (p_func(x) / 2)) / H;
        b = (2 / (H * H)) - q_func(x);
        c = (1 / H  + (p_func(x) / 2 )) / H;
        alpha[i] = c / (b - a * alpha[i - 1]);
        betta[i] = (betta[i - 1] * a - r_func(x)) / (b - a * alpha[i - 1]);
        x += H;
    }

    ///обратный ход

    ///определяем нач. значения исходя из правого граничного условия
    y[SIZE] = (A22 * betta[SIZE] + B2 * H);
    y[SIZE] /= ((A22 * (1 - alpha[SIZE])) + A21 * H);

    for (i = SIZE; i > 0; i--)
    {
        y[i - 1] = alpha[i - 1] * y[i] + betta[i - 1];
    }
}
