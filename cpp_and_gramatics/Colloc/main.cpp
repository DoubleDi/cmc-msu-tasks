#include <iostream>
#include <cstring>
#include <typeinfo>
#include <vector>
#include <list>
using namespace std;



template <class T>
typename T::value_type sum7(const T& t){
			typename T::value_type s = T::value_type();
			typename T::const_iterator p = t.begin();
for (int i = 0; i < 7; i++) {
if (p == t.end())
return 0;
				s += *p++;
			}
return s;
}

int main(int argc, char const *argv[]) {
    try {

    } catch(bad_cast) {
        
    }
    return 0;
}
