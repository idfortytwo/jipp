#include <iostream>
using namespace std;

// zamienia wartości a i b przyjmując wskaźniki 
template <class T> void swap(T *a, T *b) {
    T temp = *a;
    *a = *b;
    *b = temp;
}

template <class T>
void testSwap(T a, T b) {
    T aAfter = a, bAfter = b;
    swap(&aAfter, &bAfter);

    // sprawdza czy wartości pozamienianych aAfter i bAfter są odpowiednio równe b i a
    if (aAfter == b && bAfter == a) 
        cout << "działa" << endl;
    else 
        cout << "nie działa" << endl;
}

int main() {
    int a = 30, b = 500;

    cout << "before: a=" << a << " b=" << b << endl;
    swap(&a, &b);
    cout << "after:  a=" << a << " b=" << b << endl;

    cout << "testowanie swap dla intów 30 i 500: ";
    testSwap(a, b);
    cout << endl;


    string c = "First", d = "sEcond";
    
    cout << "before: c=" << c << " d=" << d << endl;
    swap(&c, &d);
    cout << "after:  c=" << c << " d=" << d << endl;

    cout << "testowanie swap dla stringów \"First\" i \"sEcond\": ";
    testSwap(c, d);
}