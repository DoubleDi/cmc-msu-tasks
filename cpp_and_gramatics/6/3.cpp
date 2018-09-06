#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
class A
{
public:
    int a;
    ~A()
    {
        cout << a << endl;
    }
};

void rec(void)
{
    int x;
    try{
        if (cin >> x) {
            A b;
            b.a = x;
            rec();
        } else {
            throw 1;
        }
    } catch (...) {
    }

}

int main(int argc, char const *argv[]) {

    rec();
    return 0;
}
