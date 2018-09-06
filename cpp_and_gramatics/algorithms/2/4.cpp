#include <iostream>
#include <vector> 
#include <string>
#include <iterator>
#include <sstream>
#include <functional>
#include <algorithm>
#include <cmath>

using namespace std;

int main(int argc, const char **argv)
{
	int m, n;
	cin >> m >> n;
	int cnt = 0; 
	vector<bool> primes;
	primes.resize(20000000 + 5);
	if (m >= n / 2) {
		cout << -1 << endl;
		return 0;
	}

	std::fill(primes.begin(), primes.end(), true);
	primes[0] = false;
	primes[1] = false;
	for (long long i = 2; i <= 20000000; ++i) {
		if (primes[i]) {
			if (i * i <= 20000000) {
				for (int j=i*i; j <= 20000000; j+=i) {
					primes[j] = false;
				}
			}
		}
	}
	int curDel = 2;
	int curAdd = n + 2;

	for (auto i = curDel; i < curAdd; i++) {
		if (primes[i]) {
			cnt++;
		}
	}
	if (cnt == m) {
		cout << 2 << endl;
		return 0;
	}

	while (curAdd <= 20000000) {
		if (primes[curAdd]) {
			cnt++;
		}

		if (primes[curDel]) {
			cnt--;
		}

		curDel++;
		curAdd++;
		if (cnt == m) {
			cout << curDel << endl;
			return 0;
		}
	}
	cout << -1 << endl;
    return 0;
}