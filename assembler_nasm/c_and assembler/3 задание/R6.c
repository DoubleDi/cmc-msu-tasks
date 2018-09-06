#include <stdio.h>

unsigned F(unsigned a)
{
    unsigned count = 0;
    int i;
    for(i = 0;i < 32; i++)
    {
        if (!(a & 1)) count++;
        a >>= 1;
    }
    return count;
}


int main(void)
{
    unsigned a;
    scanf("%u", &a);
    printf("%u", F(a));
    return 0;
}
