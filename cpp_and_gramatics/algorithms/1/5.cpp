#include <iostream>
#include <vector> 
#include <string>
#include <iterator>
#include <sstream>
#include <functional>
#include <algorithm>

using namespace std;

string longOp(char op, string s1, string s2)
{
    vector<int> a, b, c{};
    bool addMin = false;

    if (op == '+') {
        if (s1[0] == '-' && s2[0] == '-') {
            addMin = !addMin;
            s1.erase(s1.begin());
            s2.erase(s2.begin());
        } else if (s1[0] == '-') {
            addMin = !addMin;
            s1.erase(s1.begin());
            op = '-';
        } else if (s2[0] == '-') {
            s2.erase(s2.begin());
            op = '-';
        }
    } else if (op == '-') {
        if (s1[0] == '-' && s2[0] == '-') {
            addMin = !addMin;
            s1.erase(s1.begin());
            s2.erase(s2.begin());
        } else if (s1[0] == '-') {
            addMin = !addMin;
            op = '+';
            s1.erase(s1.begin());
        } else if (s2[0] == '-') {
            s2.erase(s2.begin());
            op = '+';
        }
    } else if (op == '*') {
        if (s1[0] == '-' && s2[0] == '-') {
            s1.erase(s1.begin());
            s2.erase(s2.begin());
        } else if (s1[0] == '-') {
            addMin = !addMin;
            s1.erase(s1.begin());
        } else if (s2[0] == '-') {
            addMin = !addMin;
            s2.erase(s2.begin());
        }
    }

    if (s1.size() < s2.size() || (s1.size() == s2.size() && s1.compare(s2) < 0)) {
        swap(s1, s2);
        if (op == '-') {
            addMin = !addMin;
        }
    }
    auto size = s1.size() + s2.size();
    a.resize(size);
    b.resize(size);
    c.resize(size);

    transform(s1.begin(), s1.end(), a.begin() + (size - s1.size()), [](char c) { return int(c - '0'); });
    transform(s2.begin(), s2.end(), b.begin() + (size - s2.size()), [](char c) { return int(c - '0'); });

    int delta = 0;
    if (op == '+') {
        for (int i = size - 1; i >= 0; i--) {
            c[i] = a[i] + b[i] + delta;
            if (c[i] >= 10) {
                delta = c[i] / 10;
                c[i] = c[i] % 10;
            } else {
                delta = 0;
            }
        }
    } else if (op == '-') {
        for (int i = size - 1; i >= 0; i--) {
            c[i] = a[i] - b[i] + delta;
            if (c[i] < 0) {
                delta = -1;
                c[i] = 10+c[i];
            } else {
                delta = 0;
            }
        }
    } else if (op == '*') {
        for (int j = size - 1; j >= 0; j--) {
            for (int i = size - 1; i >= 0; i--) {
                int move = size - 1 - j;
                if (i - move < 0) {
                    continue;
                }
                c[i - move] += a[i] * b[j] + delta;
                if (c[i - move] >= 10) {
                    delta = c[i - move] / 10;
                    c[i - move] = c[i - move] % 10;
                } else {
                    delta = 0;
                }
            }
        }
    }

    stringstream res; 
    for (auto cc : c) {
        if (res.str().size() || cc != 0) {
            res << cc;
        } 
    }

    auto res_str = res.str();
    if (addMin && res_str.size()) {
        res_str = "-" + res_str;
    } else if (!res_str.size()) {
        res_str = "0";
    }
    return res_str;
}

int main(int argc, const char **argv)
{
    string s1, s2;
    char op;

    cin >> s1 >> op >> s2;
    cout << longOp(op, s1, s2) << endl;

    return 0;
}