#include <iostream>
#include <vector>
#include <string>

using namespace std;


double parse() 
{
    string val;
    cin >> val;
    if (val == "-") {
        return parse() - parse();
    } else if (val == "+") {
        return parse() + parse();
    } else if (val == "*") {
        return parse() * parse();
    } else if (val == "/") {
        return parse() / parse();
    } else {
        return atoi(val.c_str());
    }
}

int main(int argc, char ** argv) 
{
    cout << parse() << endl;
    return 0;
}
