#include <iostream>
using namespace std;

// funkcja licząca sumę dzielników liczby n
int divisorSum(int n) {
    int sum = 0;

    for (int divisor = 1; divisor < n / 2 + 1; divisor++)
        if (n % divisor == 0)
            sum += divisor;

    return sum;
}

int main(int argc, char *argv[]) {
    int a, b;

    cout << "a: ";
    cin >> a;
    cout << "b: ";
    cin >> b;

    // wyznaczenie czy a i b są liczbami skojarzonymi
    if (divisorSum(a) == b + 1 && divisorSum(b) == a + 1)
        cout << "liczby " << a << " i " << b << " są skojarzone";
    else
        cout << "liczby " << a << " i " << b << " nie są skojarzone";


    return 0;
}