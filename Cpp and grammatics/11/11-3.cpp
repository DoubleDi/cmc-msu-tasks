#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

map<char, set<string>> gram{};


int
nullable(char let)
{
    int is_nullable = 0;
    int result = 0;
    // cout << let << endl;
    for (auto ggg = gram.begin(); ggg != gram.end(); ggg++) {
        if (let == ggg->first) {
            for (auto ss : ggg->second) {
                if (ss == "") {
                    is_nullable = 1;
                    cout << "lalka" << endl;
                    break;
                } else if (ss[0] >= 'A' && ss[0] <= 'Z') {
                    auto str = ss;
                    str.erase(str.begin());
                    int res = 0;
                    if (ss[0] != let) {
                        res = nullable(ss[0]);
                    }
                    for (auto cc : str) {
                        if (cc != let) {
                            res &= nullable(cc);
                        }
                    }
                    result |= res;
                } else {
                    is_nullable = 0;
                    result = 0;
                }
            }
        }
    }
    if (is_nullable) {
        return 1;
    }
    return result;
}

string
prepare_res(string res)
{
    sort(res.begin(), res.end());
    auto end = unique(res.begin(), res.end());
    if (end - res.begin() > 0) {
        res.resize(end - res.begin());
    }
    return res;
}

string
first(string s, string from)
{
    string res = "";
    if (s == "") {
        return "";
    }
    if (s.size() == 1 && gram.find(s[0]) != gram.end()) {
        for (auto ss : gram[s[0]]) {
            if (ss != "" && from != ss) {
                    res += first(ss, s);
            }
        }
        return prepare_res(res);
    } else if (!(s[0] >= 'A' && s[0] <= 'Z') && s[0] >= 33 && s[0] <= 126) {
        return prepare_res(string{s[0]});
    } else {
        string new_res = "";
        int is_null = -1;
        for (auto cc : s) {
            if (cc >= 'A' && cc <= 'Z') {
                if (is_null == -1) {
                    is_null = 1;
                }
                if (from != string{cc}) {
                    new_res = first(string{cc}, s);
                }
                is_null &= nullable(cc);
                if (res.find(new_res) == string::npos) {
                    res += new_res;
                }
            } else {
                if (is_null == 1) {
                    if (res.find(cc) == string::npos) {
                        res += cc;
                    }
                }
                break;
            }
        }
    }
    return prepare_res(res);
}

string
follow(char let, char from)
{
    string res = "";
    for (auto gg = gram.begin(); gg != gram.end(); gg++) {
        for (auto ss : gg->second) {
            if (ss.find(let) != string::npos) {
                int index = ss.find(let);
                int is_null = -1;
                index++;
                for (;index < int(ss.size()); index++) {
                    if (!(ss[index] >= 'A' && ss[index] <= 'Z') && ss[index] >= 33 && ss[index] <= 126) {
                        res += ss[index];
                        break;
                    } else if (ss[index] >= 'A' && ss[index] <= 'Z') {
                        if (is_null == -1) {
                            is_null = 1;
                        }
                        is_null &= nullable(ss[index]);
                        res += first(string{ss[index]}, string{let});
                        if (!nullable(ss[index])) {
                            break;
                        }
                    } else {
                        if (is_null == 1) {
                            res += ss[index];
                        }
                        break;
                    }
                }
                if (ss[ss.size() - 1] == let && gram.find(ss[ss.size() - 1]) != gram.end() && gg->first != from) {
                    res += follow(gg->first, let);
                }
            }
        }
    }
    return prepare_res(res);
}


int
main(int argc, char const *argv[])
{
    char c;
    string s;
    while (getline(cin, s)) {
        istringstream iss(s);
        s = "";
        c = ' ';
        iss >> c;
        iss >> s;
        gram[c].insert(s);
    }
    if (gram.find(' ') != gram.end()) {
        gram.erase(' ');
    }
    for (auto gg = gram.begin(); gg != gram.end(); gg++) {
        cout << gg->first << " " << nullable(gg->first) << endl;
    }
    for (auto gg = gram.begin(); gg != gram.end(); gg++) {
        cout << gg->first << " " << first(string{gg->first}, "_") << endl;
    }
    for (auto gg = gram.begin(); gg != gram.end(); gg++) {
        cout << gg->first << " " << follow(gg->first, ' ') << endl;
    }
    return 0;
}
