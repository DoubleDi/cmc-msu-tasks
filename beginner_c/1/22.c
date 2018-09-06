#include <stdio.h>

int main(void)
{
    int t = 0,x,y;
    scanf("%d%d",&x,&y);
    if (x < 0) x = -x;
    if (y < 0) y = -y;
   if ((x + y)%2) t = x + y;
   else t = 2 * (x > y ? x : y);
   printf("%d",t);
    return 0;
}

