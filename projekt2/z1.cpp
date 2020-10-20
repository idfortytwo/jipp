#include <iostream>
using namespace std;

void swapIfSmaller(int *a, int *b) {
    if (*a < *b) {
        int temp = *a; 
        *a = *b; 
        *b = temp; 
    }
}

int main() {
    int a = 30, b = 500;
    cout << "before: a=" << a << " b=" << b << endl;
    swapIfSmaller(&a, &b);
    cout << "after:  a=" << a << " b=" << b << endl << endl;

    int c = 1000, d = 500;
    cout << "before: c=" << c << " d=" << d << endl;
    swapIfSmaller(&c, &b);
    cout << "after:  c=" << c << " d=" << d << endl;
}