#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    long **matrix, max = 0, i, j, y, x;
    scanf("%ld%ld", &x, &y);
    //printf("%u %ld", x, y);
    matrix = malloc(x * sizeof(unsigned int *));
    for(i = 0; i < x; i++)
        matrix[i] = malloc(y * sizeof(unsigned int));
    for(i = 0; i < x; i++)
        for(j = 0; j < y; j++) scanf("%ld", &matrix[i][j]);
    for(j = y - 2; j >= 0; j--)
    {
        matrix[0][j] += matrix[0][j + 1] > matrix[1][j + 1] ? matrix[0][j + 1] : matrix[1][j + 1];
        matrix[x - 1][j] += matrix[x - 1][j + 1] > matrix[x - 2][j + 1] ? matrix[x - 1][j + 1] : matrix[x - 2][j + 1];
        for(i = 1; i < x - 1; i++)
        {
            matrix[i][j] += (matrix[i + 1][j + 1] > matrix [i][j + 1]) ?
            (matrix[i + 1][j + 1] > matrix[i - 1][j + 1] ? matrix[i + 1][j + 1] : matrix[i - 1][j + 1]) :
            (matrix[i][j + 1] > matrix[i - 1][j + 1] ? matrix[i][j + 1] : matrix[i - 1][j + 1]);
        }

    }
    for(i = 0; i < x; i++)
        if (matrix[i][0] > max) max = matrix[i][0];
    printf("%ld", max);
    for(i = 0; i < x; i++) free(matrix[i]);
    free(matrix);
    return 0;
}
