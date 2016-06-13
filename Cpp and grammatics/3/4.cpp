#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <list>
#include <algorithm>
#include <iomanip>


using namespace std;

struct Sum {
    double s = 0;
    void operator()(double n)
    {
        s += n;
    }
};

int
main(int argc, char const *argv[]) {
    double n;
    vector<double> v;
    while (cin >> n) {
        v.push_back(n);
    }
    int del_size = int(v.size() / 10);
    v.erase(v.end() - del_size, v.end());
    v.erase(v.begin(), v.begin() + del_size);
    sort(v. begin(), v.end());
    del_size = int(v.size() / 10);
    v.erase(v.end() - del_size, v.end());
    v.erase(v.begin(), v.begin() + del_size);
    Sum res = for_each(v.begin(), v.end(), Sum());
    cout << fixed << setprecision(10) << res.s / v.size() << endl;
    return 0;
}
