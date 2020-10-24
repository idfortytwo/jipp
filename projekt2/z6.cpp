#include <iostream>
using namespace std;

template <class T> void swap(T **a, T **b) {
    T* temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int a = 30, b = 500;
    int *aPtr = &a, *bPtr = &b;

    cout << "before: a=" << *aPtr << " b=" << *bPtr << endl;
    swap(aPtr, bPtr);
    cout << "after:  a=" << *aPtr << " b=" << *bPtr << endl << endl;
    

    string c = "First", d = "sEcond";
    string *cPtr = &c, *dPtr = &d;
    
    cout << "before: c=" << *cPtr << " d=" << *dPtr << endl;
    swap(cPtr, dPtr);
    cout << "after:  c=" << *cPtr << " d=" << *dPtr << endl;
}