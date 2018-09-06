#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

class Sum {
    double sm;
public:
    Sum() { sm = 0; }
    void operator()(double n) { sm += n; }
    double get() { return sm; }
};

int main()
{
    vector<double> v;
    double tmp;
    while (cin >> tmp) {
        v.push_back(tmp);
    }

    int cnt;

    cnt = (int) (v.size() / 10);
    v.erase(v.begin(), v.begin() + cnt);
    v.erase(v.end() - cnt, v.end());
    sort(v.begin(), v.end());
    cnt = (int) (v.size() / 10);
    v.erase(v.begin(), v.begin() + cnt);
    v.erase(v.end() - cnt, v.end());


    Sum s = for_each(v.begin(), v.end(), Sum());

    cout << fixed << setprecision(10) << s.get() / v.size() << endl;
    return 0;
}
