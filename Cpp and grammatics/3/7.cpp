#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <list>
#include <algorithm>

using namespace std;

class C {
    int x;
    int y;
public:
    C(int a = 0, int b = 0) : x(a), y(b) {}
    C(C &a, C &b) {}
    C(const C *a) {}
    int operator ~ (void) const
    {
        return 0;
    }
    C &operator ++ (void)
    {
        return *this;
    }
    int operator * (C *obj)
    {
        return 0;
    }
    friend int operator + (const C curr, const C obj)
    {
        return 0;
    }
};
