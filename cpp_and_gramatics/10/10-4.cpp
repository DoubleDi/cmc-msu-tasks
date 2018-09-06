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
    map<char, string> m;
    Node (string n = "")  : name(n) {}

};

int
main(int argc, char const *argv[])
{
    string s, other_s;
    char c;
    map<string, Node> nodes;
    while(cin >> s) {
        if (s == "END")  {
            break;
        } else {
            cin >> c >> other_s;
            if (nodes.find(s) == nodes.end()) {
                nodes[s] = Node(s);
            }
            nodes[s].m.insert(pair<char, string>(c, other_s));
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
    cin >> s;
    string check;
    cin >> check;
    int count = 0;
    for (auto c : check) {
        if (nodes[s].m.find(c) == nodes[s].m.end()) {
            break;
        } else {
            s = nodes[s].m[c];
            count++;
        }
    }
    if (count != int(check.size()) || !nodes[s].is_end) {
        cout << 0 << endl;
    } else {
        cout << 1 << endl;
    }
    cout << count << endl;
    cout << s << endl;
    return 0;
}
