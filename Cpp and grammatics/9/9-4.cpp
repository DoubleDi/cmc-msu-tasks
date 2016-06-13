#include <iostream>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

int
main(int argc, char const *argv[])
{
    char c;
    string s;
    set<char> let_set;
    map<char, set<string>> gram{};
    while (cin >> c >> s) {
        gram[c].insert(s);
    }
    set<char> new_let_set;
    do {
        let_set = new_let_set;
        for (auto gg = gram.begin(); gg != gram.end(); gg++) {
            for (auto ss : gg->second) {
                int add_flag = 1;
                for (auto cc : ss) {
                    if (cc >= 'A' && cc <= 'Z' && let_set.find(cc) == let_set.end()) {
                        add_flag = 0;
                    }
                }
                if (add_flag) {
                    new_let_set.insert(gg->first);
                    break;
                }
            }
        }
    } while (let_set != new_let_set);

    for (auto ll = new_let_set.begin(); ll != new_let_set.end(); ll++) {
        for (auto ss = gram[*ll].begin(); ss != gram[*ll].end(); ss++) {
            int add_flag = 0;
            for (auto cc : *ss) {
                if (cc >= 'A' && cc <= 'Z' && new_let_set.find(cc) == new_let_set.end()) {
                    add_flag = 1;
                }
            }
            if (add_flag) {
                gram[*ll].erase(*ss);
            }
        }
    }
    for (auto ll = gram.begin(); ll != gram.end(); ll++) {
        if (new_let_set.find(ll->first) == new_let_set.end()) {
            gram.erase(ll);
        }
    }
    for (auto ll = new_let_set.begin(); ll != new_let_set.end(); ll++) {
        auto tmp_set = gram[*ll];
        for (auto ss = tmp_set.begin(); ss != tmp_set.end(); ss++) {
            cout << *ll << " " << *ss << endl;
        }
    }
    return 0;
}
