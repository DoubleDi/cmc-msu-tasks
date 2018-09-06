//ÑÒÝÊ
#include <stdio.h>
#include <stdlib.h>

struct node_stack
{
    int data;
    struct node_stack *next;
};

struct node_stack *add(int data, struct node_stack *head)
{
    struct node_stack *newnode = (struct node_stack *)malloc(sizeof(struct node_stack));
    newnode->data = data;
    newnode->next = NULL;
    if (head == NULL)
    head = newnode;
    else
    {
        newnode->next = head;
        head = newnode;
    }
    return head;
};

struct node_stack *pop(struct node_stack *head)
{
    printf("%d", head->data);
    struct node_stack *tmp;
    tmp = head;
    head = head->next;
    free(tmp);
    return head;
};

void write(struct node_stack *head)
{
    while (head)
    {
        printf("%d ", head->data);
        head = head->next;
    }
}

int main(void)
{
    struct node_stack *head = NULL;
    char word[100];
    int data;
    while(1)
    {
        gets(word);
        if (word[0] == 'a')
        {
            scanf("%d", &data);
            head = add(data, head);
        }
        if (word[0] == 'p')
            if (head) head = pop(head);
            else puts("no elements in stack");
        if (word[0] == 'w') write(head);
        if (word[0] == 'e') break;
    }
}
