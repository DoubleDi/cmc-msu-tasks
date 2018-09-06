#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

void process(const vector <int> v1, vector<int> &v2)
{
    vector<int> v3{v2};
    size_t minsize = v1.size() < v2.size() ? v1.size() : v2.size();
    auto v3_b = v3.begin();
    auto v1_b = v1.begin();
    size_t curr = 0;
    while (curr++ < minsize) {
        if(*v1_b > *v3_b) {
            v2.push_back(*v1_b);
        }
        v1_b++;
        v3_b++;
    }
    for(auto it = v2.begin(); it != v2.end(); it++) {
        cout << *it << endl;
    }
}

// int main()
// {
//     vector<int> v1{1,3,4};
//     vector<int> v2{2,1,2,2};
//     process(v1, v2);
//     return 0;
// }
