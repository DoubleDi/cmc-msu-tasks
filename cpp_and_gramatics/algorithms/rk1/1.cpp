#include <iostream>
#include <vector> 
#include <string>
#include <iterator>
#include <sstream>
#include <functional>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;

int main(int argc, const char **argv)
{
	int l, n;
	cin >> l >> n;

	vector<int> dots;
	int dot;
	for (auto i = 0; i < n; i++) {
		cin >> dot;
		dots.push_back(dot);
	}

	sort(dots.begin(), dots.end());
	vector<int> newdots{dots};
	reverse(newdots.begin(), newdots.end());

	bool flag = false; // false = left, true = right
	if (dots[0] + l >= dots[1]) {
		dots[0] = dots[1];
		flag = false;
	} else {
		dots[0] += l;
		flag = true;
	}		

	for (auto i = 1; i < dots.size(); i++) {
		if (!flag) {
			if (i < dots.size() - 1 && dots[i] + l >= dots[i + 1]) {
				dots[i] = dots[i + 1];
				flag = false;
			} else {
				dots[i] += l;
				flag = true;
			}		
		} else {
			if (dots[i] - l <= dots[i - 1]) {
				dots[i] = dots[i - 1];
				flag = true;
			} else {
				dots[i] += l;
				flag = false;
			}
		}
	}

	set<int> res;
	for (auto vv : dots) {
		res.insert(vv);
	}

	dots = newdots;
	flag = false; // false = left, true = right
	if (dots[0] - l <= dots[1]) {
		dots[0] = dots[1];
		flag = false;
	} else {
		dots[0] += l;
		flag = true;
	}		

	for (auto i = 1; i < dots.size(); i++) {
		if (!flag) {
			if (i < dots.size() - 1 && dots[i] - l <= dots[i + 1]) {
				dots[i] = dots[i + 1];
				flag = false;
			} else {
				dots[i] += l;
				flag = true;
			}		
		} else {
			if (dots[i] + l >= dots[i - 1]) {
				dots[i] = dots[i - 1];
				flag = true;
			} else {
				dots[i] += l;
				flag = false;
			}
		}
	}
	
	set<int> res2;
	for (auto vv : dots) {
		res2.insert(vv);
	}
	cout << min(res.size(), res2.size()) << endl;
    return 0;
}