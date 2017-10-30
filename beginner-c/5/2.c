#include<stdio.h>
#include<stdlib.h>

void newfree(long long **matrix, long long m)
{
    int i;
    for(i = 0; i < m; i++)
        free(matrix[i]);
    free(matrix);
    return;
}


int main(void)
{
    long long sum, maxsum = 0, j, m, m1 = 0, t, i, n, **matrix = NULL, **neededmatrix = NULL, p = 0;
    scanf("%lld", &n);
    if (n != 0)
    {
        for(t = 0; t < n; t++)
        {
            sum = 0;
            if (matrix) newfree(matrix, m);
            scanf("%lld", &m);
            matrix = (long long**)malloc(m * sizeof(long long*));
            for(i = 0; i < m; i++)
                matrix[i] = (long long*)malloc(m * sizeof(long long));
            for(i = 0; i < m; i++)
                for(j = 0; j < m; j++)
                {
                    scanf("%lld", &matrix[i][j]);
                    if (i == j) sum += matrix[i][j];
                }
            if ((sum > maxsum) || (!p))
            {
                p = 1;
                maxsum = sum;
                m1 = m;
                neededmatrix = matrix;
                matrix = NULL;
            }
        }
        for(i = 0; i < m1; i++)
            for(j = 0; j < m1; j++)
                if (j ==  m1 - 1) printf("%lld\n", neededmatrix[i][j]);
                else printf("%lld ", neededmatrix[i][j]);
        if (matrix) newfree(matrix, m);
        newfree(neededmatrix, m1);
    }
    return 0;
}
