#include <iostream>
#include <string>

using namespace std;

int main(void)
{
    string left, right;

    bool is_correct = 0;
    bool no_shrink = 1;
    bool is_cont_free = 1;

    bool was_right_s = 0;
    bool check_for_s = 0;

    while (cin >> left >> right) {
        //is correct section
        if (!left.compare("S")) {
            is_correct = 1;
        }

        bool has_term = 0;
        for (auto i = left.begin(); i != left.end(); i++) {
            if ( (*i) >= 'A' && (*i) <= 'Z') {
                has_term = 1;
                break;
            }
        }
        if (!has_term) {
            is_correct = 0;
            break;
        }
        // non-shrinking section
        if ( left.size() > right.size() ) {
            no_shrink = 0;
        }
        if (right.find(string("S") ) != string::npos) {
            was_right_s = 1;
        }
        if (!right.compare(string("_") ) ) {
            if (!left.compare(string("S"))) {
                check_for_s = 1;
            } else {
                no_shrink = 0;
            }
        }
        //is-context-free section
        if (left.size() > 1) {
            is_cont_free = 0;
        }
    }

    if (check_for_s && was_right_s) {
        no_shrink = 0;
    }

    if (!is_correct) {
        cout << "-1" << endl;
    } else if (no_shrink && is_cont_free) {
        cout << "23" << endl;
    } else if (is_cont_free) {
        cout << "2" << endl;
    } else {
        cout << "10" << endl;
    }

    return 0;
}
