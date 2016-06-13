#include <iostream>
#include <set>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    string left, right;

    /* Остальное инициализировать будет длинно и некрасиво */
    set<char> symbols{'_'};
    for (char c = 'a'; c <= 'z'; c++) {
        symbols.insert(c);
    }
    for (char c = '0'; c <= '9'; c++) {
        symbols.insert(c);
    }

    vector<pair<string, string>> gram;
    set<char> prev, cur;
    prev.clear();
    cur.clear();

    while (cin >> left >> right) {
        gram.push_back(pair<string, string>(left, right));
        int fl = 1;
        for (unsigned i = 0; i < right.size(); i++) {
            if (symbols.find(right[i]) == symbols.end()) {
                fl = 0;
                break;
            }
        }
        if (fl) {
            cur.insert(left[0]);
        }
    }

    for (auto p = cur.begin(); p != cur.end(); p++) {
        symbols.insert(*p);
    }

    do {
        prev = cur;
        cur.clear();
        for (auto p = gram.begin(); p != gram.end(); p++) {
            int fl = 1;
            for (unsigned i = 0; i < p->second.size(); i++) {
                if (symbols.find(p->second[i]) == symbols.end()) {
                    fl = 0;
                    break;
                }
            }
            if (fl) {
                cur.insert(p->first[0]);
            }
        }
        for (auto p = cur.begin(); p != cur.end(); p++) {
            symbols.insert(*p);
        }
    } while (prev != cur);

    for (auto p = gram.begin(); p != gram.end();) {
        if (symbols.find(p->first[0]) == symbols.end()) {
            p = gram.erase(p);
        } else {
            int fl = 1;
            for (unsigned i = 0; i < p->second.size(); i++) {
                if (symbols.find(p->second[i]) == symbols.end()) {
                    fl = 0;
                    break;
                }
            }
            if (!fl) {
                p = gram.erase(p);
            } else {
                p++;
            }
        }
    }

    for (auto p = gram.begin(); p != gram.end(); p++) {
        cout << p->first << " " << p->second << endl;
    }
    return 0;
}
