//cписок
#include <stdio.h>
#include <stdlib.h>


struct node_list
{
    int data;
    struct node_list *next;
};


struct node_list *add(struct node_list *head, int data, int beforeelem)
{
    struct node_list *tmp;
    struct node_list *newelem = (struct node_list *)malloc(sizeof(struct node_list));
    newelem->data = data;
    newelem->next = NULL;
    tmp = head;
    if ((head == NULL) || (beforeelem == head->data))
    {
        newelem->next = head;
        head = newelem;
    }
    else
    {
        while ((tmp->next) && (tmp->next->data != beforeelem)) tmp = tmp->next;
        if (!tmp->next) tmp = tmp->next;
        if (tmp == NULL) printf("No element before which need to paste\n");
        else
        {
            newelem->next = tmp->next;
            tmp->next = newelem;
        }
    }
    return head;
};


struct node_list *del(struct node_list *head, int delitem)
{
    struct node_list *tmp, *del;
    tmp = head;
    if (head == NULL) printf("no elements at all\n");
    else if (head->data == delitem)
    {
        del = head;
        head = head->next;
        printf("%d\n", del->data);
        free(del);
    }
    else {
        while ((tmp->next) && (tmp->next->data != delitem)) tmp = tmp->next;
        if (!tmp->next) printf("no elements to delete\n");
        else
        {
            del = tmp->next;
            tmp->next = tmp->next->next;
            printf("%d\n", del->data);
            free(del);
        }
    }
    return head;
};

void print(struct node_list *head)
{
      while (head)
    {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}


void split(struct node_list *l, int val, struct node_list **small, struct node_list **large)
{
    *large = NULL;
    *small = NULL;
    struct node_list *tmp;
    struct node_list *end_small = NULL, *end_large = NULL;
    while(l)
    {
        if (l->data > val)
        {
            if (!(large))
            {
                 puts("1111asdasas");
                *large = l;
                puts("asdasas");
                (*large)->next = NULL;
                 puts("22222asdasas");
                end_large = *large;
                puts("22222asdasas");
                printf("-------%d\n", (*large)->data);
            }
            else
            {
                end_large->next = l;
                end_large = end_large->next;
                end_large->next = NULL;
            }

        }
        else
        {
            if (!(small))
            {
                *small = l;
                (*small)->next = NULL;
                end_small = *small;
                printf("-------%d\n", (*small)->data);
            }
            else
            {
                end_small->next = l;
                end_small = end_small->next;
                end_small->next = NULL;
            }
        }
        tmp = l;
        free(tmp);
        l = l->next;
    }
    while(*large)
    {
        printf("%d ", (*large)->data);
        (*large) = (*large)->next;
    }
    printf("\n");
    while(*small)
    {
        printf("%d ", (*small)->data);
        (*small) = (*small)->next;
    }
}




int main(void)
{
    struct node_list *head = NULL, **small, **large;
    char word[1000];
    int data, beforeelem, delitem;
    while(1)
    {
   //     puts("!!!");
        gets(word);
        if (word[0] == 'a')
        {
            scanf("%d", &data);
            scanf("%d", &beforeelem);
            //puts("LOL");
            head = add(head, data, beforeelem);
          //  puts("asdas");
        }
        if (word[0] == 'd')
        {
            scanf("%d", &delitem);
            head = del(head, delitem);
        }
         if (word[0] == 'p') print(head);
        if (word[0] == 'e') break;
    }
    split(head, 5, small, large);
}
