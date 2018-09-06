#include <iostream>

using namespace std;

class C {
    double x;
    double y;
public:
    C(double a = 0.0, double b = 0.0) { x = a; y = b; }
    C(const C &a, const C &b) { x = 0; y = 0; }
    C(const C *a) { x = 0; y = 0; }
    friend C operator + (int b, const C &a);
    int operator ~() const
    {
        return 0;
    }
    C &operator ++()
    {
        x = x + 1;
        y = y + 1;
        return *this;
    }
    int operator *(const C a[2])
    {
        return 0;
    }
};

C operator + (int b, const C &a)
{
    return C(1, 1);
}

C func1(const C &v1, int v2)
{
    return C(v2 + v1, ~v1);
}

void func2(const C *p1, double p2)
{
    C v1 = p2;
    C v2[2][2];
    C v3 = func1(func1(func1(&p1[3], p2), ~p1[2]), ++v1 * v2[1]);
}
