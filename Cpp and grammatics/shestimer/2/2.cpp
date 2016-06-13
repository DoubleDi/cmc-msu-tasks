#include <iostream>

using namespace std;

int
main(int argc, char const *argv[])
{
    int n, m;
    cin >> n >> m;
    // n + 1 new;
    int ** matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[m];
    }
    // 2 new
    int ** a = new int*[n];
    a[0] = new int[n*m];
    for (int i = 1; i != n; i++) {
        a[i] = a[0] + i*m;
    }
    return 0;
}
