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
// a = {3,4}
// b = {1,2}
// S -> aSa | _
// T -> bTb | _

int k;

string
other_make_s(string s, char c, char prev)
{

    s += prev;
    if (int(s.size()) == k) {
        cout << s << endl;
    } else {
        s += '0';
        *(--s.end()) = '1';
        other_make_s(s, '1', '1');
        *(--s.end()) = '2';
        other_make_s(s, '2', '2');
        s += prev;
    }
    return s;
}


string
make_s(string s, char c, char prev)
{
    if (int(s.size()) == k) {
        cout << s << endl;
    } else {
        s += '0';
        *(--s.end()) = '1';
        other_make_s(s, '1', '1');
        *(--s.end()) = '2';
        other_make_s(s, '2', '2');
        *(--s.end()) = '3';
        make_s(s, '3', '3');
        *(--s.end()) = '4';
        make_s(s, '4', '4');
        s += c;
    }
    return s;
}

int
main(int argc, char const *argv[])
{
    string s;
    cin >> k;
    make_s("", '3', '3');
    make_s("", '4', '4');
    return 0;
}
