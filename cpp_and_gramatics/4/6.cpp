#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

template<typename T>
void myreverse(T it1, T it2) {
        int count = 0;
        for(auto it = it1; it != it2; it++) {
            count++;
        }
        count /= 2;
        int curr = 0;
        auto b_it = it1;
        auto e_it = it2;
        e_it--;
        while (curr++ < count) {
            swap(*b_it, *e_it);
            b_it++;
            e_it--;
        }
}

// int main()
// {
//     vector<int> vec{};
//     myreverse(vec.begin(), vec.end());
//     for( auto it = vec.begin(); it != vec.end(); it++) {
//         cout << *it << endl;
//     }
//     return 0;
// }
