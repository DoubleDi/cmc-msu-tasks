#include <iostream>
#include <vector>

using namespace std;
class Sum {
    int a;
    int b;
public:
    Sum(int a, int b) {
        this->a = a;
        this->b = b;
    }
    int
    get() {
        return a + b;
    }
};

int
main(int argc, char const *argv[]) {
    Sum(2, 3).get();
    return 0;
}
