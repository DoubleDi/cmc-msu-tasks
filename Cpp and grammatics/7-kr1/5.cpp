#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

class person
{
public:
    string name;
    double sum;
    int num;
    person(string nm, double s, int n) : name(nm), sum(s), num(n) {}
};

bool cmp(person a, person b) { return (a.name < b.name); }

int main(int argc, char const *argv[]) {
    string name;
    vector<person> v;
    double mark;
    int flag = 0;
    while (cin >> name >> mark) {
        flag = 0;
        for (auto i = v.rbegin(); i != v.rend(); i++) {
            if (i->name == name) {
                i->sum += mark;
                i->num++;
                flag = 1;
                break;
            }
        }
        if (!flag) {
            v.push_back(person(name, mark, 1));
        }
    }
    sort(v.begin(), v.end(), cmp);
    for (auto i : v) {
        cout << i.name << " " << i.sum / i.num << endl;
    }

    return 0;
}
