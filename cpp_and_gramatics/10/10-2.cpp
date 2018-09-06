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

int k;

void make_T(int n)
{
    if (n > 0) {
        cout << 'b';
        make_T(n - 1);
        cout << 'c';
    }
}

void make_S(int n)
{
    if (n > 0) {
        cout << 'a';
        make_S(n - 1);
        cout << 'd';
    } else {
        make_T(k);
    }
}

void
make(int p)
{
    if(p > 0) {
        k = k / 2 - p;
        make_S(p);
        cout << endl;
        k = (k + p) * 2;
        make(p - 1);
    }
}

int
main(int argc, char const *argv[])
{
    cin >> k;
    if (!(k % 2) && k >= 4) {
        make(k / 2 - 1);
    }
    return 0;
}
