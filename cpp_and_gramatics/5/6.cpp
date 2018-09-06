#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>

using namespace std;


bool cmp (Figure *i, Figure *j)
{
    return (i->get_square() < j->get_square());
}


int
main(int argc, char const *argv[])
{
    vector<Figure *> v{};
    string s;
    while(getline(cin, s)) {
        char type;
        istringstream stream(s);
        stream >> type;
        getline(stream, s);
        if (type == 'S') {
            v.push_back(Square::make(s));
        }
        if (type == 'C') {
            v.push_back(Circle::make(s));
        }
        if (type == 'R') {
            v.push_back(Rectangle::make(s));
        }
    }
    stable_sort(v.begin(), v.end(), cmp);
    for (auto i = v.begin(); i != v.end(); i++) {
        cout << (*i)->to_string() << endl;
    }
    for( auto i = v.begin(); i != v.end(); i++) {
        delete *i;
    }
    return 0;
}
