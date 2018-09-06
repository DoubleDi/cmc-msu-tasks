#include <stdio.h>
#include <stdlib.h>

int work(void)
{
    char s[11];
    scanf("%s", s);
    if (s[0] == '/') return work() / work();
    if (s[0] == '*') return work() * work();
    else return atoi(s);
}

int main(void)
{
   printf("%d", work());
   return 0;
}
