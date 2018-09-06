#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <list>
#include <algorithm>

using namespace std;

class B {
    int a;
public:
    B(int b,int c = 3) :
        a(b + c) {}
    double get() const
    {
        return a;
    }
    B operator += (const B &other)
    {
        a += other.a;
        return *this;
    }
};
