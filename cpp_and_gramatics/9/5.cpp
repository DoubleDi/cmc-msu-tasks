#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iomanip>

using namespace std;

class Date
{
    string date;
public:
    Date(string d = "")
    {
        int year, day, mon;
        char tmp;
        istringstream iss(d);
        iss >> year >> tmp >> mon >> tmp >> day;
        ostringstream oss;
        oss << year;
        oss << "/";
        oss << setfill('0') << setw(2) << mon;
        oss << "/";
        oss << setfill('0') << setw(2) << day;
        date = oss.str();
    }
    string get_date() const
    {
        return date;
    }
    int operator == (const Date &other) const
    {
        return (date == other.get_date());
    }
    int operator < (const Date &other) const
    {
        return (date < other.get_date());
    }
};


class Data
{
public:
    string name;
    map<Date, int> m;
    Data(Date date, string n, int mrk)
    {
        name = n;
        m.insert(pair<Date, int>(date, mrk));
    }

};
bool cmp(Data &a, Data &b)
{
    return a.name <= b.name;
}

int
main(int argc, char const *argv[])
{
    string name;
    string dd;
    vector<Data> v;
    vector<Date> dates;
    int mark;
    while (cin >> name >> dd >> mark) {
        Date date(dd);
        int flag = 0;
        for (auto vv = v.begin(); vv != v.end(); vv++) {
            if (vv->name == name) {
                auto a = vv->m.find(date);
                if (a != vv->m.end()) {
                    a->second = mark;
                } else {
                    vv->m.insert(pair<Date, int>(date, mark));
                }
                flag = 1;
                break;
            }
        }
        if (!flag) {
            v.push_back(Data(date, name, mark));
        }
        if (find(dates.begin(), dates.end(), date) == dates.end()) {
            dates.push_back(date);
        }
    }
    cout << ". ";
    sort(dates.begin(), dates.end());
    for (auto dd = dates.begin(); dd != dates.end(); dd++) {
        cout << dd->get_date() << " ";
    }
    cout << endl;

    sort(v.begin(), v.end(), cmp);
    for (auto vv = v.begin(); vv != v.end(); vv++) {
        cout << vv->name << " ";
        for (auto dd = dates.begin(); dd != dates.end(); dd++) {
            if (vv->m.find(*dd) != vv->m.end()) {
                cout << vv->m[*dd] << " ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
    return 0;
}
