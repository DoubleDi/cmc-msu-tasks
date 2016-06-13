#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>

using namespace std;

class Rectangle : public Figure
{
    double a, b;
public:
    static Rectangle * make(string s)
    {
        double aa, bb;
        sscanf(s.c_str(), "%lf %lf", &aa, &bb);
        Rectangle *r = new Rectangle();
        r->a = aa;
        r->b = bb;
        return r;
    }
    double get_square() const { return this->a * this->b;}
};

class Square : public Figure
{
    double a;
public:
    static Square * make(string s)
    {
        double aa;
        Square *q = new Square();
        sscanf(s.c_str(), "%lf", &aa);
        q->a = aa;
        return q;
    }
    double get_square() const { return this->a * this->a; }
};

class Circle : public Figure
{
    double R;
public:
    static Circle * make(string s)
    {
        double RR;
        Circle *c = new Circle();
        sscanf(s.c_str(), "%lf", &RR);
        c->R = RR;
        return c;
    }
    double get_square() const { return M_PI * this->R * this->R; }
};
