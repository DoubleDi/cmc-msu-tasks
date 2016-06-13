#include <iostream>

using namespace std;

int
main()
{
    int c, oldc = -1;
    int count = 0;
    while ((c = cin.get()) != EOF) {
        if (!count || oldc == c) {
            oldc = c;
            count++;
        } else {
            if (count > 4 || oldc == '#') {
                cout << "#" << char(oldc) << hex << count << "#";
            } else {
                for (auto i = 0; i < count; i++) {
                    cout << char(oldc);
                }
            }
            oldc = c;
            count = 1;
        }
    }
    if (count > 4 || oldc == '#') {
        cout << "#" << char(oldc) << hex << count << "#";
    } else {
        for (auto i = 0; i < count; i++) {
            cout << char(oldc);
        }
    }
    return 0;
}
