#include <iostream>
#include <vector> 
#include <string>
#include <iterator>
#include <sstream>
#include <functional>
#include <algorithm>

using namespace std;

int gcd (int a, int b, int &x, int &y) {
	if (a == 0) {
		x = 0; y = 1;
		return b;
	}
	int x1, y1;
	int d = gcd (b % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}
 
bool find_any_solution (int a, int b, int c, int &x, int &y, int &g) {
	g = gcd (abs(a), abs(b), x, y);
	if (c % g != 0) {
		return false;
    }

	x *= c / g;
	y *= c / g;
	
    if (a < 0) {
        x *= -1;
    } 
	if (b < 0) {
        y *= -1;
    }  
	return true;
}

int main(int argc, const char **argv)
{
    int a, b, n;
    cin >> a >> b >> n;
    int x, y, g;

    if (a == 0 && b == 0) {
        cout << "No" << endl;
        return 0;
    }
    if (a == 0) {
        cout << 1 << " " << n / b << endl;
        return 0;
    }
    if (b == 0) {
        cout << n / a << " " << 1 << endl;
        return 0;
    }
    if (find_any_solution(a, b, n, x, y, g)) {
        while (b > 0 && x <= 0) {
            x += b / g;
            y -= a / g;
        }
        while (b < 0 && x <= 0) {
            x -= b / g;
            y += a / g;
        }
        while (b > 0 && x - b / g > 0) {
            x -= b / g;
            y += a / g;
        }
        while (b < 0 && x + b / g > 0) {
            x += b / g;
            y -= a / g;
        }
        cout << x << " " << y << endl;
    } else {
        cout << "No" << endl;
    }

    return 0;
}