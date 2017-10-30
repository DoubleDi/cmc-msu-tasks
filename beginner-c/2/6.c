#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int k, i, n, *mas , *help;
    scanf("%d", &n);
    mas = malloc(n * sizeof(int));
    help = malloc(n * sizeof(int));
    for(i = 0; i < n; i++) scanf("%d", &mas[i]);
    for(i = 0; i < n; i++) help[i] = mas[i];
    for(k = 0; k < 2; k++)
        for(i = 0; i < n; i++) mas[i] = help[mas[i] - 1];
    for(i = 0; i < n; i++) printf("%d ", mas[i]);
    free(mas);
    free(help);
    return 0;
}
