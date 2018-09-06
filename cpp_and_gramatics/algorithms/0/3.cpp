#include <iostream> 

using namespace std;
#include <stack>

int main(int argc, const char **argv) 
{
    string str;
    stack<char> s;
    cin >> str;
    for (auto c : str) {
        if (!s.size()) {
            s.push(c);
        } else {
            if (c != s.top()) {
                s.pop();
            }
        }
    }
    if (s.size()) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
    }

    return 0;
}