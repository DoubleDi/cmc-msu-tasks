#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LEFT 0

double H;
int SIZE;

///========================FUNCTIONS_FOR_METHODS===========================

void second_order_1 (double x[SIZE], double y[SIZE], int ITER);

void second_order_2 (double x[SIZE], double u[SIZE], double v[SIZE], int ITER);

void fourth_order_1 (double x[SIZE], double y[SIZE], int ITER);

void fourth_order_2 (double x[SIZE], double u[SIZE], double v[SIZE], int ITER);


///=================================OUTPUT==================================

void print_1 (double x[SIZE], double y[SIZE]);

void print_2 (double x[SIZE], double u[SIZE], double v[SIZE]);

///=============================ONE_EQUATION================================

double sol (double x);

double func (double x, double y);

///=========================SYSTEM_OF_TWO_EQUATIONS=========================

double sys_1 (double x, double u, double v);

double sys_2 (double x, double u, double v);

///===============================MAIN======================================

int main(void)
{
    double RIGHT;
    int ORDER, TYPE, i;

    printf("\nINPUT:\n");
    printf("    1)TYPE:\n        [1] - one_equatation\n");
    printf("        [2] - system_of_two\n");
     printf("         ");
    scanf("%d", &TYPE);
    printf("    2)ORDER:\n        [2] - second\n");
    printf("        [4] - fourth\n");
     printf("         ");
    scanf("%d", &ORDER);
    printf("    3)RIGHT_BBORDER: ");
    scanf("%lf", &RIGHT);
    printf("    4)NUMBER_OF_STEPS: ");
    scanf("%d", &SIZE);
    printf("\nOUTPUT:\n");

    H = (RIGHT - LEFT) / SIZE;

    if (TYPE == 1)
    {
        double x[SIZE], y[SIZE];

        x[0] = LEFT;
        y[0] = 10;

        if (ORDER == 2)
        {
            for (i = 0; i < SIZE; i++)
            {
                second_order_1(x, y, i);
            }

            print_1(x, y);
        }
        else if (ORDER == 4)
        {
            for (i = 0; i < SIZE; i++)
            {
                fourth_order_1(x, y, i);
            }

            print_1(x, y);
        }
        else
        {
            printf("\nINCORRECT_INPUT\n");
        }
    }
    else if (TYPE == 2)
    {
        double x[SIZE], u[SIZE],
                v[SIZE];

        x[0] = LEFT;
        u[0] = 1;
        v[0] = 0.5;

        if (ORDER == 2)
        {
            for (i = 0; i < SIZE; i++)
            {
                second_order_2(x, u, v, i);
            }

            print_2(x, u, v);
        }
        else if (ORDER == 4)
        {
            for (i = 0; i < SIZE; i++)
            {
                fourth_order_2(x, u, v, i);
            }

            print_2(x, u, v);
        }
        else
        {
            printf("\nINCORRECT_INPUT\n");
        }
    }
    else
    {
        printf("\nINCORRECT_INPUT\n");
        exit(-1);
    }

    return 0;
}

///==========================FUNCTION's_BODIES==============================

void second_order_1 (double x[SIZE], double y[SIZE], int ITER)
{
    double k1, k2;

    k1 = func(x[ITER], y[ITER]);
    k2 = func(x[ITER] + H, y[ITER] + H * k1);

    y[ITER + 1] = y[ITER] + (H / 2) * (k1 + k2);
    x[ITER + 1] = x[ITER] + H;
}

void second_order_2 (double x[SIZE], double u[SIZE], double v[SIZE], int ITER)
{
    double k1, k2, l1, l2;

    k1 = sys_1(x[ITER], u[ITER], v[ITER]);
    l1 = sys_2(x[ITER], u[ITER], v[ITER]);

    k2 = sys_1(x[ITER] + H, u[ITER] + H* k1, v[ITER] + H * l1);
    l2 = sys_2(x[ITER] + H, u[ITER] + H* k1, v[ITER] + H * l1);

    u[ITER + 1] = u[ITER] + (H / 2) * (k1 + k2);
    x[ITER + 1] = x[ITER] + H;
    v[ITER + 1] = v[ITER] + (H / 2) * (l1 + l2);
}

void fourth_order_1 (double x[SIZE], double y[SIZE], int ITER)
{
    double k1, k2, k3, k4;

    k1 = func(x[ITER], y[ITER]);
    k2 = func(x[ITER] + (H / 2), y[ITER] + (H / 2) * k1);
    k3 = func(x[ITER] + (H / 2), y[ITER] + (H / 2) * k2);
    k4 = func(x[ITER] + H, y[ITER] + H * k3);

    y[ITER + 1] = y[ITER] + (H / 6) * (k1 + 2 * k2 + 2 * k3 + k4);
    x[ITER + 1] = x[ITER] + H;
}

void fourth_order_2 (double x[SIZE], double u[SIZE], double v[SIZE], int ITER)
{
    double k1, k2, k3, k4;
    double l1, l2, l3, l4;

    k1 = sys_1(x[ITER], u[ITER], v[ITER]);
    l1 = sys_2(x[ITER], u[ITER], v[ITER]);

    k2 = sys_1(x[ITER] + (H / 2), u[ITER] + (H / 2) * k1, v[ITER] + (H / 2) * l1);
    l2 = sys_2(x[ITER] + (H / 2), u[ITER] + (H / 2) * k1, v[ITER] + (H / 2) * l1);

    k3 = sys_1(x[ITER] + (H / 2), u[ITER] + (H / 2) * k2, v[ITER] + (H / 2) * l2);
    l3 = sys_2(x[ITER] + (H / 2), u[ITER] + (H / 2) * k2, v[ITER] + (H / 2) * l2);

    k4 = sys_1(x[ITER] + H, u[ITER] + H * k3, v[ITER] + H * l3);
    l4 = sys_2(x[ITER] + H, u[ITER] + H * k3, v[ITER] + H * l3);

    u[ITER + 1] = u[ITER] + (H / 6) * (k1 + 2 * k2 + 2 * k3 + k4);
    x[ITER + 1] = x[ITER] + H;
    v[ITER + 1] = v[ITER] + (H / 6) * (l1 + 2 * l2 + 2 * l3 + l4);
}

void print_1 (double x[SIZE], double y[SIZE])
{
    int i;
    double tmp = 0;
    for (i = 0; i <= SIZE; i++)
    {
        printf("x: %5.5f counted: %5.5f given: %5.5f ", x[i], y[i], sol(x[i]));
        tmp  += x[i] + y[i];
    }
    tmp /= SIZE;
    printf("error: %lf\n", tmp);
}

void print_2 (double x[SIZE], double u[SIZE], double v[SIZE])
{
    int i;

    for (i = 0; i <= SIZE; i++)
    {
        printf("x: %5.5f counted y1: %5.5f counted y2: %5.5f\n", x[i], u[i], v[i]);
    }
}

double sol (double x)
{
    double tmp;
    tmp = (-1) * ((x * x) + 2);
    tmp += (2 * x) + 12 * exp(-x);
    return tmp;
}

double func (double x, double y)
{
    return ((-1) * ((x * x) + y));
}

double sys_1 (double x, double u, double v)
{
    return pow(M_E, -u * u - v * v) + 2 * x;
}

double sys_2 (double x, double u, double v)
{
    return 2 * u * u + v;
}
