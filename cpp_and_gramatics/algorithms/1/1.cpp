#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char ** argv) 
{
    vector<int> vals;
    int val, cnt, coins = 0, needCoins = 0; 

    cin >> cnt;
    for (auto i = 0; i < cnt; i++) {
        cin >> val;
        if (val == 5) {
            coins++;
        } else if (val == 10) {
            coins--;
        } else if (val == 50) {
            coins -= 9;
        } else if (val == 100) {
            coins -= 19;
        }
        needCoins = min(coins, needCoins);
    }

    cout << -needCoins << endl;
    return 0;
}