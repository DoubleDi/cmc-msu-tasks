#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <sstream>
#include <functional>
#include<set>

using namespace std;

int main(int argc, const char **argv)
{
    set<int> a{1,2,3};
    set<int> b{1,2,4};
    auto c = a + b;
    
    return 0;
}