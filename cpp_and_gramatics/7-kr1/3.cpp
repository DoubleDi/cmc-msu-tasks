#include <iostream>
#include <string>
#include <vector>
using namespace std;

void process(vector<int> &v)
{
    auto b = v.begin();
    while(b != v.end()) {
        b = v.erase(b);
        if (b == v.end()) {
            break;
        }
        b++;
    }
    for(auto i = v.rbegin(); i != v.rend(); i++) {
        cout << *i << endl;
    }
}
