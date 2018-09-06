#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <list>
#include <algorithm>
#include <iomanip>


using namespace std;

struct Sum
{
    double s = 0;
    void operator() (double n)
    {
        s += n;
    }
};

int
main(void)
{
    double n;
    vector<double> v;
    while (cin >> n) {
        v.push_back(n);
    }
    int count = int(v.size());
    int del_size = count / 10;
    auto begin = v.begin() + del_size;Do
    auto end = v.end() - del_size;
    count -= 2 * del_size;
    sort(begin, end);
    del_size = count / 10;
    begin += del_size;
    end -= del_size;
    count -= 2 * del_size;
    Sum res = for_each(begin, end, Sum());
    cout << fixed << setprecision(10) << res.s / count << endl;
    return 0;
}
