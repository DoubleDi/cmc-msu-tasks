#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int
main(int argc, char const *argv[]) {
    double item;
    int all = 0;
    double sum = 0;
    double sq_sum = 0;
    while (cin >> item) {
        all++;
        sq_sum += item * item;
        sum += item;
    }
    double average = sum / all;
    double n_average = sq_sum / all;
    cout << setprecision(10) << average << endl;
    cout << setprecision(10) <<  sqrt(n_average - average * average) << endl;
    return 0;
}
