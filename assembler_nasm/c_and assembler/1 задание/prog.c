#include <stdio.h>
#include <math.h>

float f1(float x)
{
    return 0.6 * x + 3;
}

float f2(float x)
{
    return (x - 2) * (x - 2) * (x - 2) - 1;
}

float f3(float x)
{
    return 3/x;
}

float test1(float x)
{
    return x + x * x + 2;
}

float test2(float x)
{
    return x * x;
}

float testi(float x)
{
    return x;
}

void root(float f(float x), float g(float x), float a, float b, float eps1, float *x)
{
    float F(float x)
    {
        return f(x) - g(x);
    }
    float c = 0;
    float newc = (a * F(b) - b * F(a))/(F(b) - F(a));
    do
    {
        c = newc;
        if (((F(a) +  F(b)) / 2 - F((a + b) / 2)) * (-F(a)) > 0) a = c;
        else b = c;
        newc = (a * F(b) - b * F(a))/(F(b) - F(a));
    }
    while (fabs(newc - c) >= eps1);
    *x = c;
}


float integral(float f(float x), float a, float b, float eps2)
{
    int n = 10, i = 0;
    float h  = (b - a) / n;
    float summ = 0, newsumm = 0;
    for(i = 0; i < n + 1; i++)
    {
        if ((i == 0) || (i == n)) newsumm += f(a + i * h);
        else if (i % 2) newsumm += 4 * f(a + i * h);
        else newsumm += 2 * f(a + i * h);
    }
    newsumm = newsumm * h / 3;
    do
    {
        summ = newsumm;
        newsumm = newsumm / h * 3;
        n *= 2;
        h  = (b - a) / n;
        for(i = 1; i < n; i++)
        {
            if (i % 2) newsumm += 4 * f(a + i * h);
            else if (i % 4) newsumm -= 2 * f(a + i * h);
        }
        newsumm = newsumm * h / 3;
    }
    while (fabs(newsumm - summ) / 15 >= eps2);
    return newsumm;
}

int main(void)
{
    float x = 0, x1 = 0, x2 = 0, x3 = 0;
    root(test1, test2, -5, 8, 0.00001, &x);
    printf("TEST: %f  %f\n", x, integral(testi, 0, 5, 0.0001));
    root(f1, f2, 1, 8, 0.00001, &x);
    x1 = x;
    printf("%f\n", x1);
    root(f2, f3, 2.2, 6, 0.00001, &x);
    x2 = x;
    printf("%f\n", x2);
    root(f3, f1, 0.1, 5, 0.00001, &x);
    x3 = x;
    printf("%f\n", x3);
    printf("%f\n", integral(f1, x3, x1, 0.0001) - integral(f2, x2, x1, 0.0001) - integral(f3, x3, x2, 0.0001));
    return 0;
}
