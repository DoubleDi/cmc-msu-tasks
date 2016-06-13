#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int
main(int argc, char const *argv[])
{
    string s;
    int is_KS = 1;
    int has_A = 0;
    int find_S = 0;
    int right_S = 0;
    int is_NSH = 1;
    int warn = 0;
    string left;
    string right;
    while (cin >> left >> right) {
        if (left == "S") {
            find_S = 1;
        }
        has_A = 0;
        for (auto i = left.begin(); i != left.end(); i++) {
            if (*i >= 'A' && *i <= 'Z') {
                has_A = 1;
            }
        }
        if (!has_A) {
            cout << -1 << endl;
            return 0;
        }
        if (left.find('_') != string::npos) {
            cout << -1 << endl;
            return 0;
        }
        if (right.find('_') != string::npos && right.size() > 1) {
            cout << -1 << endl;
            return 0;
        }
        if (right.find('S') != string::npos) {
            right_S = 1;
        }
        if (left.size() > right.size()) {
            is_NSH = 0;
        }
        if (right == "_" && left != "S") {
            is_NSH = 0;
        }
        if (left.size() > 1) {
            is_KS = 0;
        }
        if (right == "_" && left == "S") {
        }
        if (right_S && warn) {
            is_NSH = 0;
            warn = 1;
        }
    }
    if (!find_S) {
        cout << -1 << endl;
    } else if (!is_KS) {
        cout << 10 << endl;
    } else if (is_KS) {
        cout << 2;
        if (is_NSH) {
            cout << 3 << endl;
        } else {
            cout << endl;
        }
    }

    return 0;
}
