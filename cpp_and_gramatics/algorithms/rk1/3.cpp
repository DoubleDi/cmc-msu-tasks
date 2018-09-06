#include <vector> 
#include <cmath>
#include <cstdio>

using namespace std;
long long find_pairs(vector<long long> coins, long long  val) {
	if (val == 0) {
		return 0;
	} else if (!coins.size()) {
		return -1;
	}
	
	vector<long long > newcoins;
	for (auto it = coins.begin(); it < coins.end(); it++) {
		if (*it <= val) {
			newcoins.push_back(*it);
		}
	}

	if (!newcoins.size()) {
		return -1;
	}
	auto fst = newcoins[0];
	newcoins.erase(newcoins.begin());
	auto res1 = find_pairs(newcoins, val - fst);
	if (res1 == -1) {
		return find_pairs(newcoins, val);
	} else {
		return res1 + 1;
	}
}

int main(int argc, const char **argv)
{
	long long k, n, mod;
	scanf("%lld %lld", &k, &n);
	vector<long long > coins;
	long long  sum = 0;
	coins.reserve(n);

	for (auto i = 0; i < n; i++) {
		long long coin;
		scanf("%lld", &coin);
		coins.insert(coins.begin(), coin);
		coins.insert(coins.begin(), coin);
		sum += coin;
		if (sum == k) {
			printf("%d\n", 2 * (i + 1) - 1);
			return 0;
		}
		sum += coin;
		if (sum == k) {
			printf("%d\n", 2 * (i + 1));
			return 0;
		}
	}

	if (sum < k) {
		printf("Impossible\n");
		return 0;
	} else if (sum == k) {
		printf("%lu\n", coins.size());
		return 0;
	} else {
		long long res = find_pairs(coins, k);
		if (res == -1) {
			printf("Change\n");
		} else {
			printf("%lld\n", res);
		}
	}

    return 0;
}