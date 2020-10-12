#include <iostream>
#include <string.h>
using namespace std;

int main(int argc, char *argv[]) {
    // odczyt pierwszego argumentu do char* zmiennej 
    char* arg = argv[1];
    int argLen = strlen(arg);

    for (int i = 0; i < argLen; i++) {
        char a = arg[i];
        char b = arg[argLen - i - 1];

        // porównywanie czy i-ty symbol argumentu nie jest różny od i-tego od końca
        if (a != b) {
            cout << arg << " nie jest palindromem" << endl;
            return 0;
        }
    }

    cout << arg << " jest palindromem" << endl;
    return 0;
}