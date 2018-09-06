#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <list>
#include <algorithm>

using namespace std;

class C {
    int a;
public:
    C(int i = 0) :
        a(i * 2) {}
    double get() const {
        return a;
    }
    friend C operator + (C &first, const C &other) {
        C res(first.get() + other.get());
        return res;
    }
    C &operator = (C &b) {
        a = b.a;
        return *this;
    }
};
int main(int argc, char const *argv[]) {
    C c1(7), c2 = 5, c3(c1 + c2);
    cout << c1.get() << ' ' << c2.get() << ' ' << c3.get() << endl;
    return 0;
}
