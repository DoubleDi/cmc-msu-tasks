#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s;
    while (cin >> s) {
        int n = 0;
        int m = 0;
        int fl = 1;
        int sm = 0;

        for (unsigned i = 0; i < s.length(); i++) {
            if (s[i] != '0' && s[i] != 'a' && s[i] != 'b' && s[i] != '1') {
                fl = 0;
            }
        }

        for (unsigned i = 0; i < s.length(); i++, sm++) {
            if (s[i] != 'a') {
                break;
            }
            n++;
        }
        if (n < 1) {
            fl = 0;
        }

        for (unsigned i = sm; i < s.length(); i++, sm++) {
            if (s[i] != '0') {
                break;
            }
            m++;
        }

        if (m < 1) {
            fl = 0;
        }

        int k = 0;
        for (unsigned i = sm; i < s.length(); i++, sm++) {
            if (s[i] != 'b') {
                break;
            }
            k++;
        }
        if (k != n) {
            fl = 0;
        }

        k = 0;
        for (unsigned i = sm; i < s.length(); i++, sm++) {
            if (s[i] != '1') {
                break;
            }
            k++;
        }
        if (k != m) {
            fl = 0;
        }

        if (unsigned(sm) != s.length()) {
            fl = 0;
        }

        if (!fl) {
            cout << 0 << endl;
        } else {
            cout << 1 << endl;
        }
    }
    return 0;
}
