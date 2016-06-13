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

using namespace std;

// Grammatick
// S -> aSd | aTd
// T -> bTc | bc


void make_T(int n)
{
    if (n > 0) {
        cout << 'b';
        make_T(n - 1);
        cout << 'c';
    }
}

void make_S(int n, int m)
{
    if (n > 0) {
        cout << 'a';
        make_S(n - 1, m);
        cout << 'd';
    } else {
        make_T(m);
    }
}

void
make(int t, int p)
{
    if(p > 0) {
        make_S(p, t - p);
        cout << endl;
        make(t, p - 1);
    }
}

int
main(int argc, char const *argv[])
{
    int k;
    cin >> k;
    if (!(k % 2) && k >= 4) {
        make(k / 2, k / 2 - 1);
    }
    return 0;
}
