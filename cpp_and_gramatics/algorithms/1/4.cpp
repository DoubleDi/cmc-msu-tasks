#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

int main(int argc, char ** argv) 
{
    string line = "a";
    int n, k, l;
    int letter = 'a';

    cin >> n >> k >> l;
    if (k == l == 1) {
        cout << char(letter + n - 1) << endl;
        return 0;
    }

    k--;
    l--;
    bool changed = true;
    while (changed) {
        changed = false;
        int num = pow(2, n) - 1;
        if (k == 0) {
            break;
        }

        if (k <= num / 2 && l <= num / 2) {
            n--;
            k--;
            l--;
            changed = true;
        } else if (k > num / 2 && l > num / 2) {
            k = k - pow(2, n - 1);
            l = l - pow(2, n - 1);
            n--;
            changed = true;
        }
    }
    
    n--;
    while (n > 0) {
        letter++;
        line = char(letter) + line + line;
        n--;
    }

    cout << line.substr(k, l - k + 1) << endl;
    return 0;
}