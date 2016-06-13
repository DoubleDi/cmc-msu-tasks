#include <iostream>
#include <string>

using namespace std;

int main(int argc, char const *argv[]) {
    string s;
    while (cin >> s) {
        int maxx;
        int flag = 0;
        for (unsigned int i = 0; i < s.size(); i++) {
            if (s[i] != '2' && s[i] != '1' && s[i] != '3' && s[i] != '4') {
                cout << 0 << endl;
                flag = 1;
                break;
            }
        }
        if (flag) {
            continue;
        }
        int max_3 = s.find_last_of('3');
        int max_4 = s.find_last_of('4');
        if (max_3 == (int)string::npos) {
            maxx = max_4;
        } else if (max_4 == (int)string::npos) {
            maxx = max_3;
        } else {
            maxx = max(max_3, max_4);
        }
        if ((s.find('1') == string::npos || (int)s.find('1') > maxx) && ((int)s.find('2') > maxx
    || s.find('2') == string::npos)) {
            cout << 1 << endl;
        } else {
            if (s.find('1') == string::npos && s.find('2') == string::npos) {
                cout << 1 << endl;
            }
            cout << 0 << endl;
        }
    }
    return 0;
}
