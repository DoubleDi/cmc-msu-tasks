#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class BinaryNumber
{
    vector<int> bn;
public:
    BinaryNumber(const string &s)
    {
        for(auto c : s) {
            bn.push_back(c - '0');
        }
    }
    operator string () const
    {
        string out;
        for (auto i : bn) {
            out.push_back(i + '0');
        }

        return out;
    }
    const BinaryNumber &operator++()
    {
        if (find(bn.begin(), bn.end(), 0) == bn.end()) {
            bn.insert(bn.begin(), 0);
        }
        auto end = bn.rbegin();
        (*end)++;
        while (bn.rend() != end) {
            if (*end > 1) {
                *end = 0;
                (*++end)++;
            } else {
                end++;
            }
        }
        if (bn[0] == 0) {
            bn.erase(bn.begin());
        }
        return *this;
    }
};
