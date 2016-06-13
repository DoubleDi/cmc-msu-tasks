#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

int
main(int argc, char const *argv[]) {
    int r1, c1, r2, c2;
    int m, n;
    cin >> m >> n;
    while (cin >> r1 >> c1 >> r2 >> c2) {
        int dr, dc, newdr, newdc;
        dr = r1 - r2;
        if (dr < 0) {
            dr += m;
        }
        newdr = r2 - r1;
        if (newdr < 0) {
            newdr += m;
        }
        if (newdr < dr) {
            dr = newdr;
        }
        dc = c1 - c2;
        if (dc < 0) {
            dc += n;
        }
        newdc = c2 - c1;
        if (newdc < 0) {
            newdc += n;
        }
        if (newdc < dc) {
            dc = newdc;
        }
        cout << dr + dc << endl;
    }
    return 0;
}
