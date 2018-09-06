#include <iostream>
#include <vector> 
#include <string>
#include <iterator>
#include <sstream>
#include <functional>
#include <algorithm>

using namespace std;

int spread(vector<int> numbers, int first, int second)
{
	if (numbers.size() == 0) {
		return abs(first - second);
	}

	auto number = numbers[0]; 
	numbers.erase(numbers.begin());

	return min(spread(numbers, first + number, second), spread(numbers, first, second + number));
}

int main(int argc, const char **argv)
{
	int a, n;
	vector<int> numbers;
	cin >> n;
	for (auto i = 0; i < n; i++) {
		cin >> a;
		numbers.push_back(a);
	}

	cout << spread(numbers, 0, 0) << endl;
    return 0;
}