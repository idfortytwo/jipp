#include <iostream>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[]) {
    int* input = (int*) malloc(sizeof(int));
    int inputLen = argc-1;
    
    // wpisywanie tekstowych argumentów argv do intowego arrayu input
    for (int i = 0; i < argc; i++)
        input[i] = atoi(argv[i+1]);

    // sortowanie arrayu input
    sort(input, input + inputLen);

    cout << "out = ";
    for (int i = 0; i < inputLen; i++)
        cout << input[i] << " ";
    cout << endl;
}