#include <iostream>

using namespace std;

template <typename IT, typename Compare = less<typename iterator_traits<IT>::value_type>>
void selection_sort(IT first, IT last, Compare comp = Compare())
{
    if (last == first) {
        return;
    }
    auto access = --last;
    auto max_elem = first;
    while(access != first){
        max_elem = access;
        for (auto it = first; it != access; it++) {
            if (comp(*max_elem,*it)) {
                max_elem = it;
            }
        }
        swap(*max_elem, *access);
        access--;
    }
}
