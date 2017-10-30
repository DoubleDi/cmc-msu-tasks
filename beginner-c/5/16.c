#include <stdio.h>
#include <stdlib.h>


long long k, p;

long long ** multiply(long long **one, long long **two)
{
    //int pp, q;
    long long **rez, i, t, j;
    rez = malloc(k * sizeof(long long*));
    for(i = 0; i < k; i++)
        rez[i] = malloc(k * sizeof(long long));

    for(i = 0; i < k; i++)
        for(j = 0; j < k; j++) rez[i][j] = 0;
   // printf("%d\n", p);
    for(t = 0; t < k; t++)
    {
      for(i = 0; i < k; i++)
    {
        for(j = 0; j < k; j++)
        {
          //  printf("%d\n", p);
            //printf("%d\n", rez[t][i]);
            //rez[t][i] += ((one[t][j] % p) * (two[j][i] % p)) % p;
            rez[t][i] = (rez[t][i] % p  + ((one[t][j] % p) * (two[j][i] % p)) % p) % p;

        }
    }
    }
    return rez;
}



int main(void)
{
    long long **matrix, **tmp, *mas_k;
    long long n, pow = 0, sum = 0;
    long long i, j;
    scanf("%lld%lld%lld", &k, &n, &p);
    matrix = malloc(k * sizeof(long long *));
    mas_k = malloc(k * sizeof(long long));
    for(i = 0; i < k; i++)
    {
        scanf("%lld", &mas_k[i]);
        matrix[i] = malloc(k * sizeof(long long));
    }
    for(i = 0; i < k; i++) scanf("%lld", &matrix[0][i]);
    for(i = 1; i < k; i++)
        for(j = 0; j < k; j++)
            if ((i - j) == 1) matrix[i][j] = 1;
            else matrix[i][j] = 0;
    pow = n - k;
    tmp = malloc(k * sizeof(long long*));
    for(i = 0; i < k; i++)
        tmp[i] = malloc(k * sizeof(long long));
    for (i = 0; i < k; i++)
        for(j = 0; j < k; j++)
            if (i == j) tmp[i][j] = 1;
            else tmp[i][j] = 0;


  /*  for(i = 0; i < k; i++)
        for(j = 0; j < k; j++)
            if (j == k - 1) printf("%d\n", tmp[i][j]);
            else printf("%d ", tmp[i][j]);*/

 /*   for(i = 0; i < k; i++)
        for(j = 0; j < k; j++)
            if (j == k - 1) printf("%d\n", matrix[i][j]);
            else printf("%d ", matrix[i][j]);
            puts("umnojenie");*/
    while(pow > 1)
    {
        if (pow % 2)
        {
            pow--;
            tmp = multiply(matrix, tmp);
/*printf("%lld\n", pow);
    for(i = 0; i < k; i++)
        for(j = 0; j < k; j++)
            if (j == k - 1) printf("%d\n", tmp[i][j]);
            else printf("%d ", tmp[i][j]);*/

        }
        else
        {
     /*       for(i = 0; i < k; i++)
        for(j = 0; j < k; j++)
            if (j == k - 1) printf("%d\n", matrix[i][j]);
            else printf("%d ", matrix[i][j]);
             printf("\n");*/
            pow /= 2;
            matrix =  multiply(matrix, matrix);
            /*  for(i = 0; i < k; i++)
        for(j = 0; j < k; j++)
            if (j == k - 1) printf("%d\n", matrix[i][j]);
            else printf("%d ", matrix[i][j]);*/

        }
    }
    matrix = multiply(matrix, tmp);
     /*for(i = 0; i < k; i++)
        for(j = 0; j < k; j++)
            if (j == k - 1) printf("%d\n", matrix[i][j]);
            else printf("%d ", matrix[i][j]);*/
    /*for(i = 0; i < k; i++)
        for(j = 0; j < k; j++)
            if (j == k - 1) printf("%d\n", matrix[i][j]);
            else printf("%d ", matrix[i][j]);
*/
for(i = 0; i < k; i++) sum = (sum % p + ((mas_k[k - i - 1] % p) * (matrix[0][i] % p)) % p ) % p;
if (n > k) printf("%lld", sum);
else printf("%lld", mas_k[n - 1] % p);
    return 0;
}
