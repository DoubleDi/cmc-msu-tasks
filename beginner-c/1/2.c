#include <stdio.h>

int main(void)
{
    int i,n,x,max,t = 1;
    scanf("%d",&n);
    scanf("%d",&max);
    for(i = 0;i < n - 1;i++)
    {
        scanf("%d",&x);
        if (x == max) t++;
        else if (x > max)
        {
            max = x;
            t = 1;
        }
    }
    printf("%d",t);
}
