#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next, *prev;
};

struct node * add(struct node *head, int data)
{
    struct node * newelem = (struct node *)malloc(sizeof(struct node));
    newelem->data = data;
    newelem->next = newelem->prev = NULL;
    if (!head)
    {
        head = newelem;
        head->next = head->prev = head;
    }
    else
    {
        head->prev->next = newelem;
        newelem->next = head;
        newelem->prev = head->prev;
        head->prev = newelem;
    }
    return head;
};

struct node * tweak(FILE * inp, struct node *head, struct node **mas)
{
    int p, q;
    struct node * first, *last;
    fscanf(inp, "%d%d", &p, &q);
    first = last = head;
    first = mas[p];
    last = mas[q];
    if (first != head)
    {
        first->prev->next = last->next;
        last->next->prev = first->prev;
        last->next = head;
        first->prev = head->prev;
        head->prev->next = first;
        head->prev = last;
        head = first;
    }
    return head;
};

void print(FILE * out, struct node * head)
{
    struct node * tmp;
    tmp = head;
    do
    {
        fprintf(out, "%d ", head->data);
        head = head->next;
    } while (tmp != head);
}

int main(void)
{
    FILE * inp = fopen("input.txt", "r");
    FILE * out = fopen("output.txt", "w");
    struct node *head = NULL;
    struct node **mas;
    int n, i, m;
    fscanf(inp, "%d%d", &n, &m);
    mas = (struct node **)malloc((n + 1) * sizeof(struct node *));
    for(i = 1; i <= n; i++)
        {
            head = add(head, i);
            mas[i] = head->prev;
        }
    for(i = 0; i < m; i++)
        head = tweak(inp, head, mas);
    print(out, head);
    fclose(inp);
    fclose(out);
    free(mas);
    return 0;
}
