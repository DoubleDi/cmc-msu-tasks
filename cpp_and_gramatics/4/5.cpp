#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

void process(vector<int> &v1,const vector<int> v2, int k)
{
    for(auto ind : v2) {
        if (ind - 1 < int(v1.size()) && ind - 1 >= 0) {
            v1[ind - 1] *= k;
        }
    }
    ostream_iterator<int> out_it(cout,"\n");
    copy(v1.begin(), v1.end(), out_it);
}
