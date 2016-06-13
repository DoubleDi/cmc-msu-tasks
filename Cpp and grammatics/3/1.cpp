#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <list>

using namespace std;

void process(const vector <int> v, list<int> &l, int step)
{
    auto i = v.begin();
    auto l_i = l.begin();
    while (i != v.end()) {
        if (l_i != l.end()) {
            *l_i = *i;
            l_i++;
        } else {
            break;
        }
        i += step;
        if (i >= v.end()) {
            break;
        }
    }
    for (auto j = l.rbegin(); j != l.rend(); j++) {
        cout << *j << endl;
    }
}

// int main()
//     {
//     vector<int> v{1,2,3,4,5,6};
//     list<int> l{9,9,9,9};
//     int step = 10;
//     process(v, l, step);
//     return 0;
// }
