#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <list>
#include <algorithm>
#include <string>

using namespace std;

int main(void)
{
    string s, rev_s;
    while (cin >> s) {
        while(s.size() > 0) {
            rev_s = s;
            reverse(rev_s.begin(), rev_s.end());
            if (s == rev_s) {
                cout << s << endl;
                break;
            } else {
                s.resize(s.size() - 1);
            }
        }
    }
    return 0;
}
