#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "CFile.h"
//реализация для Linux

int comparecounter = 0; // счетчик сравнений
int swapcounter = 0; // счетчик перемещений
double a[100]; // исходный массив


void print(int n, double * a) // вывод массива, если нужно
{
    int i;
    for(i = 0; i < n; i++) printf("%lf ", a[i]);
    printf("\n");
}


void generatemas(int k, int n) // генерация массива
{
    int i;
    if (k == 1)
        for(i = 0; i < n; i++)
            a[i]=(double)(i * 1000000000000);// 64 битное число
    else if (k == 2)
        for(i = 0; i < n; i++)
            a[i]=(double)((n - i) * 1000000000000); // 64 битное число
    else
        for(i = 0; i < n; i++)
        {
            a[i]=(double)rand()/((double)RAND_MAX/100) * (double)rand()/((double)RAND_MAX/100) * rand() * rand() * rand();//64 битное число
            if (i % 2) a[i] = -a[i];
        }
}


void choicesort(int n, double * a) // сортировка простым выбором
{
    int p = 0, i, k;
    for(i = 0; i < n; i++)
    {
        p = i;
        for(k = i + 1; k < n; k++)
        {
            #ifdef HARD
            if (compare(fabs(a[p]), fabs(a[k]))) p = k;
            #else
            if (!compare(a[p], a[k])) p = k;
            #endif
        }
        swap(&a[i], &a[p]);
    }
}


void quicksort(int n, double * a)// быстрая сортировка
{
    int left = 0, right = n - 1;
    double x = a[(n - 1) / 2];
    do
    {
        #ifdef HARD
        while(compare(fabs(x), fabs(a[left]))) left++;
        while(compare(fabs(a[right]), fabs(x))) right--;
        #else
        while(compare(a[left], x)) left++;
        while(compare(x, a[right])) right--;
        #endif
        if (left <= right)
        {
            swap(&a[left], &a[right]);
            left++;
            right--;
        }
    }while(left <= right);
    if (right > 0) quicksort(right + 1, &a[0]);
    if (left < n - 1) quicksort(n - left, &a[left]);
}


int main(void)
{
    int i, k, n;
    double b[100];
    unsigned long long timer;
    scanf("%d", &n);
    srand(time(NULL));
    printf("n = %d\n", n);
    for(k = 1; k < 5; k++)
    {
        printf("\n\n");
        printf("mas %d\n", k);
        puts("choicesort:");
        comparecounter = 0;
        swapcounter = 0;
        generatemas(k, n);
        timer = 0;
        for(i = 0; i < n; i++)
            b[i] = a[i];
        //print(n, b);
        timer = timestamp();
        choicesort(n, b);
        timer = timestamp() - timer;
        //print(n, b);
        printf("compares = %d\nswaps = %d\n", comparecounter, swapcounter);
        printf("time = %llu\n", timer);
        printf("\n");
        puts("quicksort:");
        comparecounter = 0;
        swapcounter = 0;
        timer = 0;
        for(i = 0; i < n; i++)
            b[i] = a[i];
        //print(n, b);
        timer = timestamp();
        quicksort(n, b);
        timer = timestamp() - timer;
        //print(n, b);
        printf("compares = %d\nswaps = %d\n", comparecounter, swapcounter);
        printf("time = %llu\n", timer);
    }
    return 0;
}
