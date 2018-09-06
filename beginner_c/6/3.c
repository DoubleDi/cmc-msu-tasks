#include <stdio.h>
#include <stdlib.h>

struct node
{
    long data;
    struct node *next;
};


struct node *add(struct node *head, long data)
{
    struct node *newelem = (struct node *)malloc(sizeof(struct node));
    newelem->data = data;
    newelem->next = NULL;
    if (!head) head = newelem;
    else
    {
        struct node *tmp;
        tmp = head;
        if (data < tmp->data)
        {
            newelem->next = tmp;
            head = newelem;
        }
        else
        {
            while ((tmp->next) && (tmp->next->data <= data)) tmp = tmp->next;
            newelem->next = tmp->next;
            tmp->next = newelem;
        }

    }
    return head;
};

void print(FILE * out, struct node *head)
{
    while(head)
    {
        fprintf(out, "%ld ", head->data);
        head = head->next;
    }
    return;
}

int main(void)
{
    long int x;
    struct node *head = NULL;
    FILE *inp = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    while(fscanf(inp, "%ld", &x) != EOF)
        head = add(head, x);
    print(out, head);
    fclose(out);
    fclose(inp);
    return 0;
}
