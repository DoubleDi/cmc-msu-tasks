#include <vector> 
#include <algorithm>
#include <cmath>
#include <cstdio>

using namespace std;

int main(int argc, const char **argv)
{
	long long m, n, mod;
	scanf("%lld %lld %lld", &n, &m, &mod);
	vector<long long> koefs;
	long long sum = 0;
	long long val;
	for (auto i = 0; i < n + 1; i++) {
		scanf("%lld", &val);
		koefs.push_back(val % mod);
		sum = (sum + val) % mod;
	}

	long long x, res = 0;
	for (auto i = 0; i < m; i++) {
		scanf("%lld", &x);
		if (x == 0) {
			printf("%lld\n", koefs[koefs.size() - 1]);	
			continue;
		}
		if (x == 1) {
			printf("%lld\n", sum);	
			continue;
		}
		x = x % mod;
		vector<long long> b(koefs.size());
		res = 0;
		b[0] = koefs[0];
		for (auto k = 1; k < b.size(); k++) {
			b[k] = (koefs[k] + x * b[k - 1]) % mod;
		}
		printf("%lld\n", b[b.size() - 1]);
	}
    return 0;
}