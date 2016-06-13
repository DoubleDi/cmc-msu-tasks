#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <list>
#include <algorithm>

using namespace std;

void process(const vector <int> &vec, list<int> &lst)
{
    vector<int> v{vec};
    sort(v.begin(), v.end());
    auto end = unique(v.begin(), v.end());
    v.erase(end, v.end());
    int prev = -1, index = 0, size = lst.size();
    auto list = lst.begin();
    for (auto it : v) {
        index = it;
        index--;
        if (index >= 0 && index < size) {
            for(int k = 0; k < index - prev - 1; k++) {
                list++;
            }
            list = lst.erase(list);
            prev = index;
        }
    }
}

int main()
{
    vector<int> v{6,6,6,6,6,6,1,11,1,8,0,9,9};
    list<int> l{1,2,3,4,5,6,7,8,9};
    process(v, l);
    for (auto i = l.begin(); i != l.end(); i++) {
        cout << *i << endl;
    }
    return 0;
}
