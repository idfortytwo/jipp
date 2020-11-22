#include "../src/matrix.cpp"

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

    cout << "Cleaning up..." << endl;
    remove("./folder");
}

int main() {
    testErrors();
}