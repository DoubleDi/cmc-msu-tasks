#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <string>

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
    new_let_set.insert('S');
    do {
        let_set = new_let_set;
        for (auto gg = gram.begin(); gg != gram.end(); gg++) {
            if (new_let_set.find(gg->first) != new_let_set.end()) {
                for (auto ss : gg->second) {
                    for (auto cc : ss) {
                        if (cc >= 'A' && cc <= 'Z' && new_let_set.find(cc) == new_let_set.end()) {
                            new_let_set.insert(cc);
                        }
                    }
                }
            }
        }
    } while (let_set != new_let_set);

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
