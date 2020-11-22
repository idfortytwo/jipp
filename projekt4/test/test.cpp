#include "..\src\matrix.cpp"

using namespace std;

void test() {
    cout << endl << "--- Testing functionality ---" << endl << endl;

    Matrix m1(3, 5);
    m1.set(0, 0, 2);
    m1.set(0, 1, 4);
    m1.set(0, 2, 6);
    m1.set(0, 3, 8);
    m1.set(0, 4, 10);
    m1.set(1, 0, 22);
    m1.set(1, 1, 44);
    m1.set(1, 2, 66);
    m1.set(1, 3, 88);
    m1.set(1, 4, 110);
    m1.set(2, 0, 1.67);
    m1.set(2, 1, 1.33);
    m1.set(2, 2, 1);
    m1.set(2, 3, 0.67);
    m1.set(2, 4, 0.33);
    cout << "m1: " << endl; m1.print();

    Matrix m2(5);
    double value = -5;
    for(int i = 0; i < m2.cols(); i++) {
        for (int j = 0; j < m2.rows(); j++) {
            m2.set(i, j, value);
            value += 0.5;
        }
    }
    cout << endl << "m2: " << endl;  m2.print();

    Matrix m3 = m1.multiply(m2);
    cout << endl << "m3 = m1 x m2:" << endl;  m3.print();

    Matrix m4(3, 5);
    for (int j = 0; j < m4.rows(); j++)
        m4.set(2, j, m3.get(2, 0) * (-1));
    cout << endl << "m4:" << endl; m4.print();

    Matrix m5 = m3.add(m4);
    cout << endl << "m5 = m3 + m4: " << endl; m5.print();

    cout << endl << "Storing m5 in ./m5.mat..." << endl;
    m5.store("m5.mat", ".");

    cout << endl << "Creating m5_stored from ./m5.mat file..." << endl;
    Matrix m5_stored("m5.mat", ".");
    cout << "m5_stored:" << endl; m5_stored.print();

    Matrix m6(3, 5);
    for (int j = 0; j < m6.rows(); j++) {
        m6.set(0, j, 50 + 10 * (rand() % 5));
        m6.set(1, j, 500 + 100 * (rand() % 5));
        m6.set(2, j, 5 + rand() % 5);
    }
    cout << endl << "m6:" << endl;
    m6.print();

    Matrix m7(m6.cols(), m6.rows());
    m7 = m5_stored.subtract(m6);
    cout << endl << "m7 = m5_stored - m6:" << endl;  m7.print();
}

int main() {
    test();
}