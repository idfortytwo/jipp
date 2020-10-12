#include <iostream>
using namespace std;

// funkcja wpisująca wartości z inputów do podanej macierzy
void readMatrix(int matrix[2][3]) {
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++) {
            cout << "[" << i << "][" << j << "]: ";
            cin >> matrix[i][j];
        }
}

int main(int argc, char *argv[]) {
    int m1[2][3], m2[2][3], m3[2][3];

    // wczyt macierzy m1 i m2
    cout << "macierz m1:" << endl;
    readMatrix(m1);

    cout << "\nmacierz m2:" << endl;
    readMatrix(m2);

    // dodawanie m1 i m2
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++) 
            m3[i][j] = m1[i][j] + m2[i][j];

    // wyświetlanie m3
    cout << "\nwynik dodawania m1 i m2: \n";
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) 
            cout << m3[i][j] << " ";
        cout << endl;
    }

    return 0;
}