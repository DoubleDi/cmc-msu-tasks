#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct bor
{
    int flag;
    char *s;
    struct bor *next[27];
};


long long  kol = 0;

struct bor *make_word (char *s)
{
    struct bor *tmp = malloc (sizeof (struct bor));
    tmp->flag = 0;
    tmp->s = strdup(s);
    return tmp;
}


struct bor *add(struct bor *head, char *s)
 {
    int i = 0, k, j;
    char *save_s;
    struct bor *tmp = head;
    struct bor *q;
    if (!head)
     {
         head = (struct bor *)malloc(sizeof(struct bor));
         head->flag = 0;
         head->s = strdup(s);
         kol++;
         return head;
     }
      puts("Aaaa11a");
 /* skip all nodes */
    while ((tmp) && (tmp->flag == 0))
    {puts("QQQQ");
/* !*/  struct bor **p = &tmp->next[s[i] - 'a'];
        if (!*p)
        {

            *p = make_word (s);
            kol++;
            return head;
        }
        tmp = *p;
        i++;puts("1111");
    }
    puts("Aaaa11a");
/* all word skipped -- key exists, update value */
    if ((i) && (!s[i]))
    {
    return head;
    }
 //Цифровой поиск: вставка элемента
 /* compare the remaining part */
    for (k = i; s[k]; k++)
        if (s[k] != tmp->s[k]) break;
 /* key already exists -- update value */
    if ((!s[k]) && (!tmp->s[k]))
    {
        return head;
    }
 /* turn t into a node */
  puts("Aaa22aa");
    save_s = strdup(tmp->s);
    tmp->flag = 1;
    memset (tmp->next, 0, sizeof (tmp->next));
// Цифровой поиск: вставка элемента
/* make new nodes for remaining common prefix */
    for(i = j; i < k; i++)
    {
        q = calloc (1, sizeof (struct bor));
        q->flag = 1;
        tmp->next[s[i] - 'a'] = q;
        tmp = q;
    }
 /* accommodate both other and new record */
    tmp->next[save_s[k] - 'a'] = (struct bor *) malloc (sizeof (struct bor));
    tmp->next[save_s[k] - 'a']->flag = 0;
    tmp->next[save_s[k] - 'a']->s = strdup(s);
    tmp->next[s[k] - 'a'] = malloc (sizeof (struct bor));
    tmp->next[s[k] - 'a']->flag = 0;
    tmp->next[s[k] - 'a']->s = strdup(s);
    kol++;
    return head;
}



int main(void)
{
    char s[2001], news[2001];
    int i, j, t, len;
    struct bor * head = NULL;
    scanf("%s", s);
    len = strlen(s);
    for(i = 0; i < len; i++)
        for(j = len - 1; j >= i; j--)
        {
            for(t = i; t <= j; t++)
                news[t - i] = s[t];
            news[j - i + 1] = '\0';
            head = add(head, news);
        }

    printf("%lld", kol);
    return 0;
}
