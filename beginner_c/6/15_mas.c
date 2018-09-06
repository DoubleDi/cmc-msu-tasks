#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct node
{
    long long data;
    char c[101];
};


long long hashf(char *x)
{
    long long i, sum = 0, len = strlen(x);
    long long p = 237, mod = 10000;
    for(i = 0; i < len; i++)
        sum = ((sum * p) % mod + x[i] % mod) % mod;
    return sum;
}


int main(void)
{
    FILE * inp = fopen("input.txt", "r");
    FILE * out = fopen("output.txt", "w");
    char c[101];
    struct node index[100000];
    long long ip, n, m, hashrez, i;
    fscanf(inp, "%lld", &n);
    for(i = 0; i < 100000; i++)
    {
        index[i].data = 0;
    }
    for(i = 0; i < n; i++)
    {
        fscanf(inp, "%s %lld", c, &ip);
        hashrez = hashf(c);
        while(index[hashrez].c[0] != '\0') hashrez = (hashrez + 1001) % 100000;
        index[hashrez].data = ip;
        strcpy(index[hashrez].c, c);
    }
    fscanf(inp, "%lld" , &m);
    for(i = 0; i < m; i++)
    {
        fscanf(inp, "%s", c);
        hashrez = hashf(c);
        while ((hashrez < 100000) && (strcmp(index[hashrez].c, c) != 0)) hashrez = hashrez + 1001;
        if (hashrez >= 100000) fprintf(out, "-1\n");
        else fprintf(out, "%lld\n", index[hashrez].data);
        //fprintf(out, "%lld\n", search(index[hashrez], c));
    }
    fclose(inp);
    fclose(out);
}
