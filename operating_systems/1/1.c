#include <stdio.h>
#include <stdlib.h>
#ifdef DEBUG
struct Info
{
    char name[16];
    int value;
};
struct Info arr[100];
int arr_size = 100;
#endif

struct Item
{
    struct Info info;
    struct Item *next;
};

struct Item *list = 0;

void solve(void)
{
    if (arr_size > 0) {
        list = calloc(1, sizeof(*list));
        list->next = NULL;
        list->info = arr[0];
        for(int i = 1; i < arr_size; i++) {
            struct Item *new_item = calloc(1, sizeof(*new_item));
            new_item->next = list;
            new_item->info = arr[i];
            list = new_item;
        }
    }
}
