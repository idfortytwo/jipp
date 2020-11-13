#include "matrix.cpp"

using namespace std;

void testErrors() {
    cout << "--- Testing errors ---" << endl << endl;
    try {
        cout << "Creating matrix of size 3x0..." << endl;
        Matrix m20(2, 0);
    } catch(logic_error &e) {
        cout << "Error: " << e.what() << endl;
    }

    try {
        cout << "Creating square matrix of size (-1)x(-1)..." << endl;
        Matrix mMinus1(-1);
    } catch(logic_error &e) {
        cout << "Error: " << e.what() << endl;
    }

    try {
        Matrix m22(2);
        cout << "Getting a value at index (-1, 0)..." << endl;
        m22.get(-1, 0);
    } catch(out_of_range &e) {
        cout << "Error: " << e.what() << endl;
    }

    try {
        Matrix m22(2);
        cout << "Setting a value at index (3, 0) in 2x2 matrix..." << endl;
        m22.set(3, 0, 12.5);
    } catch(out_of_range &e) {
        cout << "Error: " << e.what() << endl;
    }

    try {
        cout << "Adding 2x3 matrix to 2x2 matrix..." << endl;
        Matrix m22(2, 2);
        Matrix m23(2, 3);
        m22.add(m23);
    } catch(logic_error &e) {
        cout << "Error: " << e.what() << endl;
    }

    try {
        cout << "Multiplying 1x5 matrix and 4x1 matrix..." << endl;
        Matrix m15(1, 5);
        Matrix m41(4, 1);
        m15.multiply(m41);
    } catch(logic_error &e) {
        cout << "Error: " << e.what() << endl;
    }

    try {
        cout << "Opening non existing file..." << endl;
        Matrix noFile("no_file", ".");
    } catch (runtime_error &e) {
        cout << "Error: " << e.what() << endl;
    }

    try {
        cout << "Storing matrix in non existing folder..." << endl;
        Matrix m(3, 3);
        m.store("m.mat", "./no_folder");
    } catch(invalid_argument &e) {
        cout << "Error: " << e.what() << endl;
    }

    try {
        cout << "Creating file with name \"folder\"..." << endl;
        Matrix mFolder(1);
        mFolder.store("folder", ".");

        cout << "Trying to store matrix at \"./folder/m22.mat\"..." << endl;
        Matrix m22(2);
        m22.store("m22.mat", "./folder");
    } catch(invalid_argument &e) {
        cout << "Error: " << e.what() << endl;
    }
}

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

    // cout << endl << "Storing m5 in D:\\m5.mat..." << endl;
    // m5.store("m5.mat", "D:\\");

    // cout << endl << "Creating m5_stored from D:\\m5.mat file..." << endl;
    // Matrix m5_stored("m5.mat", "D:\\");
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
    testErrors();
    cout << endl << endl;
    test();
}