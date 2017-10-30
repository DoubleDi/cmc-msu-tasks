#include <stdio.h>
#include <stdlib.h>


struct node_char
{
    char data;
    int prio;
    struct node_char * next;
};

struct node_int
{
    long long data;
    struct node_int * next;
};

struct node_char * headop = NULL;
struct node_int * headnum = NULL;


void addnum(long long num)
{
    struct node_int * newelem = (struct node_int *)malloc(sizeof(struct node_int));
    newelem->data = num;
    newelem->next = NULL;
    if (headnum) newelem->next = headnum;
    headnum = newelem;
};


long long popnum(void)
{
    struct node_int * tmp;
    tmp = headnum;
    long long x = headnum->data;
    headnum = headnum->next;
    free(tmp);
    return x;
}


long long popc(void)
{
    struct node_char * tmp;
    tmp = headop;
    char x = headop->data;
    headop = headop->next;
    free(tmp);
    return x;
}



void addc(char c, int prio)
{
    long long num1, num2;
    char op;
    struct node_char * newelem = (struct node_char *)malloc(sizeof(struct node_char));
    if ((c != EOF) && (c != ')') && (c != '\n'))
    {
        newelem->data = c;
        newelem->next = NULL;
        newelem->prio = prio;
    }
    if (headop)
    {
        while ((headop) && (prio <= headop->prio) && (c != '('))
        {
            op = popc();
            if ((c == ')') && (op == '(')) break;
            num2 = popnum();
            num1 = popnum();
            switch(op)
            {
            case '-':
                addnum(num1 - num2);
                break;
            case '+':
                addnum(num1 + num2);
                break;
            case '*':
                addnum(num1 * num2);
                break;
            case '/':
                addnum(num1 / num2);
                break;
            default: break;
            }
        }
       if ((c != EOF) && (c != ')') && (c != '\n')) newelem->next = headop;
    }
    if ((c != EOF) && (c != ')') && (c != '\n')) headop = newelem;
};

void printc(struct node_char *head)
{
    while (head)
      {

           printf("%c ", head->data);
           head = head->next;
           printf("\n");
      }

}


void printd(struct node_int *head)
{
    while (head)
      {

           printf("%lld ", head->data);
           head = head->next;
           printf("\n");
      }

}


int main(void)
{
    FILE * inp = fopen("input.txt", "r");
    FILE * out = fopen("output.txt", "w");
    int index = 0;
    char num[25], c;
    while(1)
    {

        c = getc(inp);
        if (c == EOF) c = '\n';
        if ((c == '*') || (c == '/') || (c == '+') || (c == '-') || (c == '(') || (c == ')') || (c == ' ') || (c == '\n') || (c == EOF))
        {
            if (num[0] != '\0') addnum(atoi(num));
            index = 0;
            num[0] = '\0';
          //  printd(headnum);
            switch(c)
            {
            case '-':
            case '+':
                addc(c, 1);
                break;
            case '*':
            case '/':
                addc(c, 2);
                break;
            case '(':
                addc(c, 0);
                break;
            case EOF:
                c = '\n';
            case ')':
            case '\n':
                addc(c, -1);
            default: break;
            }
          // printc(headop);
            if (c == '\n') break;
        }
        else
        {
            num[index] = c;
            index++;
            num[index] = '\0';
        }
    }
    fprintf(out, "%lld", headnum->data);
    fclose(inp);
    fclose(out);
    return 0;
}
