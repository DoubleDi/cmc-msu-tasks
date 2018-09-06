#include <stdio.h>
#include <stdlib.h>

struct node
{
    long data, key;
    struct node *left, *right, *parent;
};


void print(struct node *head)
{
    if (head)
   {
        printf("%ld\n", head->key);
        print(head->left);
        print(head->right);
   }
}


struct node * add(struct node * head, long data, long key)
{
    struct node *p, *q;
    p = head;
    q = NULL;
    while(p)
    {
        q = p;
        if (key > p->key) p = p->right;
        else if (key < p->key) p = p->left;
        else
        {
            p->data = data;
            return head;
        }
    }
    p = (struct node *)malloc(sizeof(struct node));
    if (head == NULL) head = p;
    else if (key > q->key) q->right = p;
    else q->left = p;
    p->parent = q;
    p->left = p->right = NULL;
    p->key = key;
    p->data = data;
    return head;
};


struct node * search_key(struct node * head, long key)
{
    while ((head) && (head->key != key))
    {
        if (head->key < key) head = head->right;
        else head = head->left;
    }
    return head;
};

struct node * delete_key(struct node *head, struct node * elem)
{
    if (elem->left)
    {
        if (!elem->parent)
        {
            head = elem->left;
            head->parent = NULL;
        }
        else
        {
            if(elem->parent->left == elem) elem->parent->left = elem->left;
            else elem->parent->right = elem->left;
            elem->left->parent = elem->parent;
        }
    }
    else if (elem->right)
    {
        if (!elem->parent)
        {
            head = elem->right;
            head->parent = NULL;
        }
        else
        {
            if(elem->parent->left == elem) elem->parent->left = elem->right;
            else elem->parent->right = elem->right;
            elem->right->parent = elem->parent;
        }
    }
    else if (elem)
    {
        if (!elem->parent) head = NULL;
        else if(elem->parent->left == elem) elem->parent->left = NULL;
        else elem->parent->right = NULL;
    }
    free(elem);
    return head;
};


struct node * succ(struct node * node)
{
        node = node->right;
        while (node->left) node = node->left;
        return node;
};


int main(void)
{
    char c;
    long data, key;
    struct node *head = NULL, *tmp, *nexttmp;
    while(1)
    {
        c = getchar();
            if (c == 'A')
            {
                scanf("%ld %ld", &key, &data);
                head = add(head, data, key);
                //print(head);
            }
            if (c == 'S')
            {
                scanf("%ld", &key);
                tmp = search_key(head, key);
                if (tmp) printf("%ld %ld\n", tmp->key, tmp->data);
            }
            if (c == 'D')
            {
                scanf("%ld", &key);
                tmp = search_key(head, key);
                if (tmp)
                {
                    if ((tmp->left) && (tmp->right))
                    {
                        nexttmp = succ(tmp);
                        tmp->data = nexttmp->data;
                        tmp->key = nexttmp->key;
                        head = delete_key(head, nexttmp);
                    }
                    else head = delete_key(head, tmp);
                }
                //print(head);
            }
            if (c == 'F') break;
    }
    return 0;
}
