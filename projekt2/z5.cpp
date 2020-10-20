#include <iostream>
using namespace std;

template <class T> void swap(T *a, T *b) {
    T temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int a = 30, b = 500;
    cout << "before: a=" << a << " b=" << b << endl;
    swap(&a, &b);
    cout << "after:  a=" << a << " b=" << b << endl << endl;

    string c = "First", d = "sEcond";
    cout << "before: c=" << c << " d=" << d << endl;
    swap(&c, &d);
    cout << "after:  c=" << c << " d=" << d << endl;
}