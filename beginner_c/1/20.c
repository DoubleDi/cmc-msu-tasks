#include <stdio.h>
#include <math.h>

int main(void)
{
    double a,b,c,d,t1,t2;
    scanf("%lf%lf%lf%lf",&a,&b,&c,&d);
if (c > d)
{
    t1 = c;
    c = d;
    d = t1;
}
if (a > b)
{
    t1 = a;
    a = b;
    b = t1;
}
     if ((a <= 0) || (b <= 0) || (c <= 0) || (d <= 0)) printf("NO");
    else if (((c <= a) && (d <= b)) || ((c <= b) && (d <= a))) printf("YES");
    else if (((c > a) && (d > b)) || ((c > b) && (d > a))) printf("NO");
    else
    {
        t1 = 2*atan((c - sqrt(c * c + d * d - b * b))/(b + d));
        t2 = 2*atan((c + sqrt(c * c + d * d - b * b))/(b + d));
        if ((( d * cos(t1) + c * sin(t1) <= b + 0.00001) && (c * cos(t1) + d * sin(t1) <= a + 0.00001)) &&
            (( d * cos(t2) + c * sin(t2) <= b + 0.00001) && (c * cos(t2) + d * sin(t2) <= a + 0.00001))) printf("YES");
        else printf("NO");
    }
    return 0;
}
