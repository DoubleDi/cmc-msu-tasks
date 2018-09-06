#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main (void)
{
    double input = 0.0;
    long double total = 0L, total2 = 0, amount = 0L;

    while (cin >> input) {
        total += input;
        total2 += input*input;
        amount++;
    }
    double average = total/amount;
    double average2 = total2/amount;

    cout << setprecision(10)<<average << endl;
    cout << setprecision(10)<<sqrt(average2-average*average) << endl;
    return 0;
}
