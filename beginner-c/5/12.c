#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define X 0.0000001


int main(void)
{
    int i, k, n, key = -1, t;
    float **matrix, *mas_b, tmp, *swp;
    scanf("%d", &n);
    matrix = malloc(n * sizeof(float*));
    mas_b = malloc(n * sizeof(float));
    for(i = 0; i < n; i++)
        matrix[i] = malloc(2 * n * sizeof(float));
    for(i = 0; i < n; i++)
    {
        for(k = 0; k < n; k++) scanf("%f", &matrix[i][k]);
        scanf("%f", &mas_b[i]);
    }
    for(i = 0; i < n; i++)
    {
        for(k = n; k < 2 * n; k++)
            if (k - i == n) matrix[i][k] = 1;
            else matrix[i][k] = 0;
    }
    for(k = 0; k < n; k++)
    {
        key = -1;
        for(i = k; i < n; i++)
        {
            if ((matrix[i][k] > X) || (matrix[i][k] < -X))
            {
                key = i;
                break;
            }
        }
        if (key >= 0)
        {
            if (key != k)
            {
                swp = matrix[k];
                matrix[k] = matrix[key];
                matrix[key] = swp;
                key = k;
            }
           tmp = matrix[key][k];
             for(t = 0; t < 2 * n; t++)
                 matrix[key][t] = matrix[key][t] / tmp;


            for(i = 0; i < n; i++)
            {
                if (((matrix[i][k] > X) || (matrix[i][k] < -X)) && (i != key))
                {
                    tmp = matrix[i][k];
                    for(t = 0; t < 2 * n; t++)
                        matrix[i][t] -= matrix[key][t] * tmp;
                }
            }
        }
    }
    for(i = 0; i < n; i++)
    {
        tmp = 0;
        for(k = 0; k < n; k++)
           tmp = tmp + matrix[i][k + n] * mas_b[k];
        if (tmp > 0) printf("%d\n", (int)(tmp + 0.5));
        else printf("%d\n", (int)(tmp - 0.5));
    }
    /* for(q = 0; q < n; q++)
        for(p = 0; p < 2 * n; p++)
            if (p == 2 * n - 1) printf("%f\n", matrix[q][p]);
            else printf("%f ", matrix[q][p]);
            printf("\n");*/

    return 0;
}
