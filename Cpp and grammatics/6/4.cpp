#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

class Result
{
public:
    int a;
    Result(int aa) : a(aa) {}
};

void AA(int m, int n)
{
    if(m == 0) {
        throw Result(n + 1);
    } else if (m > 0 && n == 0) {
        try {
            AA(m - 1, 1);
        } catch (Result &x) {
            throw;
        }
    } else {
        try {
            AA(m, n - 1);
        } catch (Result &val) {
            try {
                AA(m - 1, val.a);
            } catch(Result &x) {
                throw;
            }
        }
    }
}



int
main(int argc, char const *argv[])
{
    int m, n;
    cin >> m >> n;
    try {
        AA(m,n);
    } catch (Result(&x)) {
        cout << x.a << endl;
    }
    return 0;
}
