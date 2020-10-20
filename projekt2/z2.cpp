#include <iostream>
using namespace std;

void swapRef(int &aRef, int &bRef) {
    int temp = aRef; 
    aRef = bRef; 
    bRef = temp; 
}

int main() {
    int a = 30, b = 500;
    cout << "before: a=" << a << " b=" << b << endl;
    swapRef(a, b);
    cout << "after:  a=" << a << " b=" << b << endl;
}