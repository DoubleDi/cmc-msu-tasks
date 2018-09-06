#include <stdio.h>
#include <string.h>
#define X  10001

int find_prefix(char *c1, char *c2)
{
    int k, i, flag, prefix = 0;
    int len_c2 = strlen(c2), len_c1 = strlen(c1);
    for(i = 0; i < len_c1; i++)
    {
        flag = 0;
        for(k = 0; k <= i; k++)
            if (c1[k] != c2[len_c2 - i + k - 1]) flag = 1;
        if (!flag) prefix = i + 1;
    }
    return prefix;
}

int main(void)
{
  char c1[X], c2[X];
  scanf("%s", c1);
  scanf("%s", c2);
  printf("%d %d", find_prefix(c1, c2), find_prefix(c2, c1));
  return 0;
}
