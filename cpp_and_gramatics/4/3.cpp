#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

template<typename T>
typename T::value_type process(T container) {
        int num = 0;
        typename T::value_type a = typename T::value_type();
        for(auto it = container.rbegin(); it != container.rend() && num++ < 3; it++) {
            a += *it;
        }
        return a;
}

// int main()
// {
//     vector<int> v2{1};
//     int a = process(v2);
//     cout << a << endl;
//     return 0;
// }
