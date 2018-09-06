#include <iostream>
#include <string>

using namespace std;

int
main(int argc, char const *argv[]) {
    string s;
    while (cin >> s) {
        int good_flag = 1;
        if (s.find('a') == string::npos || s.find('b') == string::npos
        || s.find('1') == string::npos || s.find('0') == string::npos) {
            good_flag = 0;
        }
        if (s.find_last_of('a') > s.find_first_of('b') || s.find_last_of('a') > s.find_first_of('0') ||
        s.find_last_of('a') > s.find_first_of('1') || s.find_last_of('0') > s.find_first_of('b') ||
        s.find_last_of('0') > s.find_first_of('1') || s.find_last_of('b') > s.find_first_of('1')) {
            good_flag = 0;
        }
        int count_a = 0, count_b = 0, count_1 = 0, count_0 = 0;
        for (auto ss : s) {
            if (ss != 'a' && ss != 'b' && ss != '0' && ss != '1') {
                good_flag = 0;
                break;
            }
            if (ss == 'a') {
                count_a++;
            }
            if (ss == 'b') {
                count_b++;
            }
            if (ss == '0') {
                count_0++;
            }
            if (ss == '1') {
                count_1++;
            }
        }
        if (count_a != count_b || count_1 != count_0) {
            good_flag = 0;
        }
        cout << good_flag << endl;
    }
    return 0;
}
