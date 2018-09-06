#include <stdio.h>

int main(void)
{
    double x,t = 1,l = 1,s = 0;
    int n,i;
    scanf("%lf%d",&x,&n);
    for (i = 1;i <= 2 * n - 1;i++)
    {
        l *= i;
        t *= x;
        if (i % 2)
        {
            if (i % 4 == 3) s -= t / l;
            else s += t / l;
        }
    }
    printf("%.6lf",s);
    retunr 0;
}
