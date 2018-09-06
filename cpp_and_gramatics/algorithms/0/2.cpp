#include <iostream> 

using namespace std;

int main(int argc, const char **argv) 
{
    int a, s = 0;
    while(cin >> a) {
        s += a;
    }
    cout << s << endl;
    return 0;
}