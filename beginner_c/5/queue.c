//Очередь
#include <stdio.h>
#include <stdlib.h>

struct node_queue
{
    int data;
    struct node_queue *next;
};

struct node_queue *add(struct node_queue *tail)
{
    int data;
    scanf("%d", &data);
    struct node_queue *newnode = (struct node_queue*)malloc(sizeof(struct node_queue));
    newnode->data = data;
    newnode->next = NULL;
    if (tail == NULL) tail = newnode;
    else
    {
        tail->next = newnode;
        tail = newnode;
    }
    return tail;
};

struct node_queue *pop(struct node_queue *head)
{
    struct node_queue *tmp;
    tmp = head;
    head = head->next;
    printf("%d\n", tmp->data);
    free(tmp);
    return head;
};

void write(struct node_queue *head)
{
    while(head)
    {
        printf("%d ", head->data);
        head = head->next;
    }
}

int main(void)
{
    struct node_queue *head = NULL, *tail = NULL;
    char word[1000];
    while(1)
    {
        gets(word);
        if (word[0] == 'a')
        {
            tail = add(tail);
            if (!head) head = tail;
        }
        if (word[0] == 'p')
            if (head) head = pop(head);
            else puts("no elements in queue");
        if (word[0] == 'w') write(head);
    }
}
