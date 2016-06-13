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
// S -> 1S0 | 0X1
// X -> 0X1 | _

using namespace std;

string s;
int
parse_X(int index)
{
    if(index >= int(s.size())) {
        cout << 1;
        cout << 0;
        return -2;
    } else if (s[index] == '0'){
        cout << 1;
        index = parse_X(index + 1);
        cout << 0;
        return index;
    }
    return -1;
}

int
parse_S(int index)
{
    if (s[index] == '1') {
        index = parse_S(index + 1);
        cout << 0;
        if (s[index] == '0') {
            return index;
        }
    } else if (s[index] == '0') {
        cout << 1;
        index = parse_X(index + 1);
        cout << 0;
        if (s[index] == '1') {
            return index;
        }
    }
        return -1;
}

int
main(int argc, char const *argv[])
{
    while (cin >> s) {
        parse_S(0);
        cout << endl;
    }
    return 0;
}
