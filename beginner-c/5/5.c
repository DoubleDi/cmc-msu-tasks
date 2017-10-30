#include<stdio.h>
#include<stdlib.h>

int main(void)
{
    char **s;
    int n, i;
    scanf("%d\n", &n);
    s = malloc(3 * sizeof(char*));
    for(i = 0; i < 3; i++)
        s[i] = malloc((n+1) * sizeof(char));
    scanf("%s", s[0]);
    scanf("%s", s[1]);
    scanf("%s", s[2]);
    printf("%s%s%s", s[2], s[0], s[1]);
    for(i = 0; i < 3; i++)
        free(s[i]);
    free(s);
    return 0;
}
