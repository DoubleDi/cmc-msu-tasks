#include <stdio.h>
#include <stdlib.h>

struct node
{
    long data, key;
    struct node *left, *right, *parent;
};


struct node *add(struct node * head, long data, long key)
{
    struct node *newelem  = (struct node*)malloc(sizeof(struct node));
    newelem->data = data;
    newelem->key = key;
    newelem->left = NULL;
    newelem->right = NULL;
    newelem->parent = NULL;
    if (!head) head = newelem;
    else
    {
        struct node *tmp;
        tmp = head;
        while ((tmp->left) || (tmp->right))
        {
            if (tmp->key > key)
            {
                if (tmp->left) tmp = tmp->left;
                else break;
            }
            else if (tmp->key < key)
            {
                if (tmp->right) tmp = tmp->right;
                else break;
            }
            else break;
        }
        if (tmp->key == key) tmp->data = data;
        else if (tmp->key < key)
        {
            tmp->right = newelem;
            newelem->parent = tmp;
        }
        else
        {
            tmp->left = newelem;
            newelem->parent = tmp;
        }
    }
    return head;
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


struct node *search_key(struct node *head, long key)
{
    while(head)
    {
        if (head->key == key) return head;
        else if (key < head->key) head = head->left;
        else head = head->right;
    }
    return NULL;
};


struct node *delete_key(struct node *node, long key)
{
    struct node *tmp;
    tmp = node;
    if (node->left)
    {
        tmp = tmp->left;
        while(tmp->right) tmp = tmp->right;
        if (tmp->left) tmp->parent->right = tmp->left;

        node->data = tmp->data;
        node->key = tmp->key;
        if (tmp->parent->right == tmp) tmp->parent->right = NULL;
        else tmp->parent->left = NULL;
        free(tmp);
    }
    else if (node->right)
    {
        if (!tmp->parent)
        {
            node = node->right;
            node->parent = NULL;
        }
        else
        {
            if (tmp->parent->right == tmp) tmp->parent->right = tmp->right;
            else tmp->parent->left = tmp->right;
            tmp->right->parent = tmp->parent;
        }
        free(tmp);
    }
    else
    {
        if (!node->parent)
        {
            node = NULL;
            free(tmp);
            return node;
        }
        else
        {
            if (node->parent->right == node)
            {
                node = node->parent;
                if (node) node->right = NULL;
            }
            else
            {
                node = node->parent;
                if (node) node->left = NULL;
            }
            free(tmp);
        }

    }
    while (node->parent) node = node->parent;
    return node;
};

void free_tree(struct node * head)
{
    if (head)
    {
        free_tree(head->left);
        free_tree(head->right);
        free(head);
    }
}

int main(void)
{
    char c;
    long data, key;
    struct node *head = NULL, *tmp;
    while(1)
    {
        c = getchar();
            if (c == 'A')
            {
                scanf("%ld %ld", &key, &data);
                head = add(head, data, key);
              //  print(head);
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
                if (tmp) head = delete_key(tmp, key);
              //  print(head);
            }
            if (c == 'F')
            {
                free_tree(head);
                break;
            }
    }
    return 0;
}
