#include <iostream>
using namespace std;

void swapRefPtr(int &aRef, int *bPtr) {
    int temp = aRef; 
    aRef = *bPtr; 
    *bPtr = temp; 
}

int main() {
    int a = 30, b = 500;
    cout << "before: a=" << a << " b=" << b << endl;
    swapRefPtr(a, &b);
    cout << "after:  a=" << a << " b=" << b << endl;
}