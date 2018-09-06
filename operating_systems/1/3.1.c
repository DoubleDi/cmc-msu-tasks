#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int
mysubstr(char * sample, char * text)
{
    char * key = text;
    char * key2 = NULL;
    char * text_start = text;
    char * sample_start = sample;
    int star = 0;
    if (!strlen(sample)) {
        return 0;
    }
    while (*sample != '\0') {
        if (*sample == '*') {
            star = 1;
            sample++;
            key2 = sample;
        } else if (*text == '\0') {
            return -1;
        }
        if (!star) {
            if (*sample == *text) {
                if (sample == sample_start) {
                    key = text;
                }
                sample++;
            } else {
                sample = sample_start;
                text = key++;
            }
            text++;
        } else {
            if (*sample != *text) {
                sample = key2;
            } else {
                sample++;
            }
            text++;
        }
    }
    return key - text_start;
}

#ifdef DEBUG
int
main(void)
{
    assert(mysubstr("aaaa", "baaaa") == 1);
    assert(mysubstr("aaaa", "aaaab") == 0);
    assert(mysubstr("aaaa", "aaaaaaaaaaaa") == 0);
    assert(mysubstr("ba", "bbaaaa") == 1);
    assert(mysubstr("a", "a") == 0);
    assert(mysubstr("ab", "aaabbb") == 2);
    assert(mysubstr("bab", "babababa") == 0);
    assert(mysubstr("aaaa", "bbbb") == -1);
    assert(mysubstr("abab", "b") == -1);
    assert(mysubstr("baba", "bab") == -1);
    assert(mysubstr("a*b", "aaaabbb") == 0);
    assert(mysubstr("a*b", "ab") == 0);
    assert(mysubstr("*b", "bb") == 0);
    assert(mysubstr("*b", "b") == 0);
    assert(mysubstr("a*", "a") == 0);
    assert(mysubstr("a*", "caab") == 1);
    assert(mysubstr("a*bb", "bbbbbbbb") == -1);
    assert(mysubstr("*abababa", "ssssssssabababasss") == 0);
    assert(mysubstr("abababa", "ssssssssabababasss") == 8);
    assert(mysubstr("a*zazaz", "aazazaz") == 0);
    assert(mysubstr("b*cccc", "abccccc") == 1);
    assert(mysubstr("", "") == 0);
    assert(mysubstr("", "abccccc") == 0);
    assert(mysubstr("abc", "") == -1);
    assert(mysubstr("abc*", "aaaaabc") == 4);
    assert(mysubstr("abc", "") == -1);
    assert(mysubstr("ab*ba", "aba") == -1);
    assert(mysubstr("a*", "bac") == 1);
    assert(mysubstr("*a", "bac") == 0);
    assert(mysubstr("as*das", "fsasdfdas98das5") == 2);
    assert(mysubstr("a*df", "ga54df9") == 1);
    assert(mysubstr("*", "") == 0);
    assert(mysubstr("", "") == 0);
    //printf("%d", mysubstr("abc*", "aaaaabc"));
    return 0;
}
#endif
