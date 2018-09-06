#include <iostream>

using namespace std;

class A
{
public:
    static int a;
};
int A::a = 0;

int main(int argc, char const *argv[]) {
    A ob1;
    A ob2;
    ob1.a = 1;
    ob2.a = 2;
    cout << ob1.a << " " << ob2.a << endl;
    return 0;
}
