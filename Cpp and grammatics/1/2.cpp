#include <iostream>
#include <string>

using namespace std;

void
f (int a, char b = 't')
{
    cout << "2" << endl;
}

void
f (int a, string b)
{
    cout << "2" << endl;
}

int
main(int argc, char const *argv[]) {
    f(1);
    f('+','+');
    f(2.3);
    f(3, "str");
    return 0;
}
