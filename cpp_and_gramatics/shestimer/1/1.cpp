#include <iostream>
using namespace std;

class C {
public:
    C(int a = 0) { cout << a; }

};

template <typename T>
class B {
public:
    int n;
    B<T> (T t) { n = 2; }
    B(int a) {n = 0;}
    B & operator *() {return *this;}
};

int main() {
    C c(5);
    B <C> b1(&c), b2(0);
    cout << (*b1).n << (*b2).n << endl;
    return 0;
}
