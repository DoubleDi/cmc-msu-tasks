#include <stdio.h>
#include <stdlib.h>

enum { MAX_LENGTH = 1024 };

int
main(void)
{
    int length;
    double sorted[MAX_LENGTH] = {}, not_sorted[MAX_LENGTH] = {}, help_swap;
    scanf("%d", &length);
    for(int i = 0; i < length; i++) {
        scanf("%lf", &sorted[i]);
        not_sorted[i] = sorted[i];        
    }
    for(int i = 0; i < length; i++) {
        for(int k = 0; k < length - 1 - i;  k++) {
            if (sorted[k] < sorted[k + 1]) {
                help_swap = sorted[k];
                sorted[k] = sorted[k + 1];
                sorted[k + 1] = help_swap; 
            }
        }
    }
    for(int i = 0; i < length; i++){
        printf("%d %.10g %.10g\n", i + 1, not_sorted[i], sorted[i]);
    }
    return 0;
}
