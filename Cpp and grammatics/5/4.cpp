#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;


class Figure
{
public:
    Figure(double a = 0.0) {}
    virtual double get_square() const { return 0.0; }
    virtual ~Figure() {}
};
