#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct node
{
    long long data;
    char c[101];
    struct node *next, *prev;
};


long long hashf(char *x)
{
    long long i, sum = 0, len = strlen(x);
    long long p = 237, mod = 1000;
    for(i = 0; i < len; i++)
        sum = ((sum * p) % mod + x[i] % mod) % mod;
    return sum;
}


struct node * add(struct node * head, long long data, char *c)
{
    struct node * newelem = (struct node *)malloc(sizeof(struct node));
    newelem->data = data;
    strcpy(newelem->c, c);
    newelem->next = newelem->prev = NULL;
    if (!head) head = newelem;
    else
    {
        struct node * tmp;
        tmp = head;
        while(tmp->next) tmp = tmp->next;
        tmp->next = newelem;
        newelem->prev = tmp;
    }
    return head;
};


long long search(struct node * head, char *c)
{
    while(head)
    {
        if (!strcmp(c, head->c)) return head->data;
        head = head->next;
    }
    return -1;
}


int main(void)
{
    FILE * inp = fopen("input.txt", "r");
    FILE * out = fopen("output.txt", "w");
    char c[101];
    struct node *index[1000];
    long long ip, n, m, hashrez, i;
    fscanf(inp, "%lld", &n);
    for(i = 0; i < 1000; i++)
    {
        index[i] = (struct node *)malloc(sizeof(struct node));
        index[i] = NULL;
    }
    for(i = 0; i < n; i++)
    {
        fscanf(inp, "%s %lld", c, &ip);
        hashrez = hashf(c);
        index[hashrez] = add(index[hashrez], ip, c);
    }
    fscanf(inp, "%lld" , &m);
    for(i = 0; i < m; i++)
    {
        fscanf(inp, "%s", c);
        hashrez = hashf(c);
        fprintf(out, "%lld\n", search(index[hashrez], c));
    }
    fclose(inp);
    fclose(out);
}
