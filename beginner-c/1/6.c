#include <stdio.h>

int main(void)
{
   unsigned n,k;
   scanf("%u%u",&n,&k);
   n = (n >> k) | (n << (32-k));
   printf("%u",n);
   return 0;
}
