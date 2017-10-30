#include <stdio.h>
#include <string.h>

int main(void)
{
    int n;
    char s[80], tmp[80];
    scanf("%d", &n);
    scanf("%s", s);

    n %= strlen(s);

    strrev(s);
    strncpy(tmp, s, n);
    strrev(s);
    s[strlen(s) - n + 1] = '\0';
    strcat(tmp, s);
    puts(tmp);
}
