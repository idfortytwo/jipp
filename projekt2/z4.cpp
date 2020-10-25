#include <iostream>
using namespace std;

// zwraca iloczyn a*b oraz zapisuje sumę a+b do &sum
int productAndSum(int a, int b, int &sum) {
    int product = a * b;
    sum = a + b;
    return product;
}

int main() {
    int a = 30, b = 500;
    int product, sum;

    product = productAndSum(a, b, sum);
    cout << a << " * " << b << " = " << product << endl;
    cout << a << " + " << b << " = " << sum << endl;
}