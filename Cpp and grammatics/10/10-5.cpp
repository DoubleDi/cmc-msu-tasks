#include <iostream>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

class Node
{
public:
    string name;
    int is_end = 0;
    map<string, set<string>> m;
    Node (string n = "")  : name(n) {}

};

int max_cnt = 0, is_ok = 0, is_ok_cnt = 0;
map<string, Node> nodes;
string check;

void process(int cnt, string node)
{
    max_cnt = max(cnt, max_cnt);
    char curr = check[cnt];
    string cur = "";
    cur += curr;
    if (max_cnt == int(check.size()) && nodes[node].is_end) {
        is_ok = 1;
        is_ok_cnt = min(is_ok_cnt, cnt);
    } else if (nodes[node].m.find(cur) != nodes[node].m.end() ||
    nodes[node].m.find("eps") != nodes[node].m.end()) {
        for(auto nn : nodes[node].m) {
            if (nn.first == "eps") {
                for(auto ss : nn.second) {
                    process(cnt, ss);
                }
            } else if (nn.first == cur && nn.first != "eps") {
                for(auto ss : nn.second) {
                    process(cnt + 1, ss);
                }
            }
        }
    }

}


int
main(int argc, char const *argv[])
{
    string s, other_s, c;
    while(cin >> s) {
        if (s == "END")  {
            break;
        } else {
            cin >> c >> other_s;
            if (nodes.find(s) == nodes.end()) {
                nodes[s] = Node(s);
            }
            nodes[s].m[c].insert(other_s);
        }
    }
    while (cin >> s) {
        if (s == "END") {
            break;
        } else {
            if (nodes.find(s) == nodes.end()) {
                nodes[s] = Node(s);
            }
            nodes[s].is_end = 1;
        }
    }
    for (int i = 0; i < int(nodes.size()); i++) {
        for(auto gg = nodes.begin(); gg != nodes.end(); gg++) {
            if (gg->second.is_end) {
                for (auto ss = gg->second.m.begin(); ss != gg->second.m.end(); ss++) {
                    if (ss->first == "eps") {
                        for (auto sss : ss->second) {
                            nodes[sss].is_end = 1;
                        }
                    }
                }
            }
        }
    }

    cin >> s;
    cin >> check;
    process(0, s);
    if (((is_ok_cnt && is_ok_cnt >= int(check.size())) || !is_ok_cnt) && is_ok) {
        cout << 1 << endl;
    } else {
        cout << 0 << endl;
    }
    if (is_ok_cnt) {
        cout << is_ok_cnt << endl;
    } else {
        cout << max_cnt << endl;
    }
    return 0;
}
