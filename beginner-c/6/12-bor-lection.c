#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {word, node} tag_t;

long long kol = 0;

struct record
{
    char *key;
};


struct tree
{
    tag_t tag;
    union {
    struct record *r;
    struct tree *nodes[27];
    };
};


int ord (char c) {
    return c ? c - 'a' + 1 : 0;
}

char chr(int x)
{
    return x - 1 + 'a';
}

struct record *make_record (char *key)
{
    struct record *r = malloc (sizeof (struct record));
    r->key = strdup (key);
    return r;
}


struct tree *make_word (char *key)
{
    struct tree *t = malloc (sizeof (struct tree));
    t->tag = word;
    t->r = make_record (key);
    return t;
}


struct tree *make_node (void)
{
    struct tree *t = calloc (1, sizeof (struct tree));
    t->tag = node;
    return t;
}


struct tree *make_from_record (struct record *r)
 {
    struct tree *t = malloc (sizeof (struct tree));
    t->tag = word;
    t->r = r;
    return t;
}


struct tree *insert (struct tree *t, char *key)
 {
    if (!t)
        return make_word (key);
    int i = 0;
    struct tree *root = t;
    while (t->tag == node)
    {
        struct tree **p = &t->nodes[ord(key[i++])];
        if (!*p)
        {
            *p = make_word (key);
            kol++;
            return root;
        }
        t = *p;
    }
    if (i && !key[i - 1])
    {
    return root;
    }
    int j = i;
    for (; key[i]; i++)
        if (key[i] != t->r->key[i]) break;
    if (!key[i] && !t->r->key[i])
    {
        return root;
    }
    struct record *other = t->r;
    t->tag = node;
    memset (t->nodes, 0, sizeof (t->nodes));
    for (; j < i; j++)
    {
        struct tree *p = make_node ();
        t->nodes[ord(key[j])] = p;
        t = p;
    }
    t->nodes[ord(other->key[i])] = make_from_record (other);
    t->nodes[ord(key[i])] = make_word (key);
    kol++;
    return root;
}


int main(void)
{
    char s[2001], news[2001];
    int i, j, t, len;
    struct tree* head = NULL;
    scanf("%s", s);
    len = strlen(s);
    for(i = 0; i < len; i++)
        for(j = len - 1; j >= i; j--)
        {
            for(t = i; t <= j; t++)
                news[t - i] = s[t];
            news[j - i + 1] = '\0';
            head = insert(head, news);
        }

    printf("%lld", kol + 2);
    return 0;
}

