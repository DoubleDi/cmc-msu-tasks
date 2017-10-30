#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct node
{
    long long data;
    char * key;
    struct node *left, *right, *parent;
};


void print(struct node *head)
{
    if (head)
   {
        printf("%s\n", head->key);
        print(head->left);
        print(head->right);
   }
}


struct node * add(struct node * head, char * key, long long data)
{
    struct node *p, *q;
    p = head;
    q = NULL;
    while(p)
    {
        q = p;
        if (strcmp(p->key, key) < 0) p = p->right;
        else p = p->left;
    }
    p = (struct node *)malloc(sizeof(struct node));
    p->parent = q;
    p->left = p->right = NULL;
    p->key = strdup(key);
    p->data = data;
    if (!head) head = p;
    else if (strcmp(q->key, p->key) < 0) q->right = p;
    else q->left = p;
    return head;
};


struct node * search_key(struct node * head, char * key)
{
    if (head)
    {
        if (strcmp(head->key, key) < 0) return search_key(head->right, key);
        else if  (strcmp(head->key, key) > 0) return search_key(head->left, key);
        else return head;
    }
    return NULL;
};


int main(void)
{
    FILE * inp = fopen("input.txt", "r");
    FILE * out = fopen("output.txt", "w");
    struct node * head = NULL, *tmp = NULL;
    char key[101];
    long long n, i, m, data;
    fscanf(inp, "%lld",&n);
    for(i = 0; i < n; i++)
    {
        fscanf(inp, "%s %lld", key, &data);
        head = add(head, key, data);
        //print(head);
    }
    fscanf(inp, "%lld",&m);
    for(i = 0; i < m; i++)
    {
        fscanf(inp, "%s", key);
        tmp = search_key(head, key);
        if (tmp) fprintf(out, "%lld\n", tmp->data);
        else fprintf(out, "-1\n");
    }
    fclose(inp);
    fclose(out);
    return 0;
}
