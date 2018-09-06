#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include <set>
#include <map>
#include <sstream>
#include <fstream>
#include <limits>
#include <algorithm>

using namespace std;

int
main(int argc, char const *argv[])
{
    int l;
    cin >> l;
    vector<int> v;
    v.resize(l, 1);
    int got_3 = 0;
    int got_4 = 0;
    int flag = 1;
    while (find(v.begin(), v.end(), 1) != v.end() ||
    find(v.begin(), v.end(), 2) != v.end() ||
    find(v.begin(), v.end(), 3) != v.end()) {
        got_3 = 0;
        got_4 = 0;
        flag = 1;
        for (auto i = v.begin(); i != v.end(); i++) {
            if ((*i) == 3) {
                got_3 = 1;
            }
            if ((*i) == 4) {
                got_4 = 1;
            }
            if (((*i) == 1 || (*i) == 2) && (got_3 || got_4)) {
                flag = 0;
            }

        }
        if (flag) {
            for (auto i = v.rbegin(); i != v.rend(); i++) {
                cout << *i;
            }
            cout << endl;
        }
        v[0]++;
        for (auto i = v.begin(); i != v.end(); i++) {
            if (*i > 4) {
                *i = 1;
                ++*(i + 1);
            }
        }
    }
    for (auto i = v.begin(); i != v.end(); i++) {
        if ((*i) == 3) {
            got_3 = 1;
        }
        if ((*i) == 4) {
            got_4 = 1;
        }
        if (((*i) == 1 || (*i) == 2) && (got_3 || got_4)) {
            flag = 0;
        }

    }
    if (flag) {
        for (auto i = v.rbegin(); i != v.rend(); i++) {
            cout << *i;
        }
        cout << endl;
    }

    return 0;
}
