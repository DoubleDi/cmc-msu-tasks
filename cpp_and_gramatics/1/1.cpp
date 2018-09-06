#include <iostream>
#include <vector>

using namespace std;
class A {
public:
    A(char z = 'x') { cout << "char" << endl;}
    A(int a, double b=1.0) { cout << "int, double" << endl;}
    A(double z, int a=2, int c=3) { cout << "double,int,int";}
};

int
main(int argc, char const *argv[]) {
    A v1;
    unsigned char z1 = 'a'; A v2(z1);
    float z2 = 0.1f; A v3(z2); A v4=A();
    A v5(z2,1.0,1.0); A v6(z1,z2);
    return 0;
}
