#include <iostream>

namespace N
{
    std::ostream & func1(int a, int b)
    {
        return std::cout << (a + b);
    }
}

class A
{
public:
    A(int a = 0, int b = 10, int c = 20)
    {
        N::func1(a, b) << c << std::endl;
    }
};

int main()
{
    A a(30, 40);
}
