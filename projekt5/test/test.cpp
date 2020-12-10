#include <iostream>

#include <sqlite3/sqlite3.h>
#include <matrix.hpp>

using namespace std;

void testErrors(sqlite3 *db) {
    cout << "--- Testing errors ---" << endl << endl;
    try {
        cout << "Creating matrix of size 3x0..." << endl;
        Matrix(2, 0);
    } catch(logic_error &e) {
        cout << "Error: " << e.what() << endl;
    }

    try {
        cout << "Creating square matrix of size (-1)x(-1)..." << endl;
        Matrix(-1);
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
        m22 + m23;
    } catch(invalid_argument &e) {
        cout << "Error: " << e.what() << endl;
    }

    try {
        cout << "Multiplying 1x5 matrix and 4x1 matrix..." << endl;
        Matrix m15(1, 5);
        Matrix m41(4, 1);
        m15 * m41;
    } catch(invalid_argument &e) {
        cout << "Error: " << e.what() << endl;
    }

    try {
        cout << "Loading non existing matrix..." << endl;
        Matrix(db, "no_matrix");
    } catch (runtime_error &e) {
        cout << "Error: " << e.what() << endl;
    }

    sqlite3 *noDB;
    try {
        cout << "Storing matrix using empty db..." << endl;

        sqlite3_open("not_existant_database", &noDB);

        Matrix m(3, 3);
        m.store(noDB, "m");

    } catch(exception &e) {
        cout << "Error: " << e.what() << endl;
    }
    sqlite3_close(noDB);

}

void test(sqlite3 *db) {

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

    Matrix m3 = m1 * m2;
    cout << endl << "m3 = m1 x m2:" << endl;  m3.print();

    Matrix m4(3, 5);
    for (int j = 0; j < m4.rows(); j++)
        m4.set(2, j, m3.get(2, 0) * (-1));
    cout << endl << "m4:" << endl; m4.print();

    Matrix m5 = m3 + m4;
    cout << endl << "m5 = m3 + m4: " << endl; m5.print();

    cout << endl << "Storing m5 in db..." << endl;
    m5.store(db, "m5");

    cout << endl << "Loading m5_stored from db ..." << endl;
    Matrix m5_stored(db, "m5");
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
    m7 = m5_stored - m6;
    cout << endl << "m7 = m5_stored - m6:" << endl;  m7.print();

    cout << endl << "cout << m7:" << endl;
    cout << m7 << endl;

    cout << "m5 == m7: " << (m5 == m7) << endl;
    cout << "m5 == m5_stored: " << (m5 == m5_stored) << endl << endl;

    cout << "m7[0]: ";
    double *m7row0 = m7[0];
    for (int i = 0; i < m7.cols(); i++)
        cout << m7row0[i] << " ";

    double *m7row2 = m7[2];
    cout << endl << "m7[2]: ";
    for (int i = 0; i < m7.cols(); i++)
        cout << m7row2[i] << " ";
}

sqlite3* connect() {
    sqlite3 *db;

    int rc = sqlite3_open("db.sqlite", &db);
    if(rc) {
        cerr << "Can't open database: " << endl << sqlite3_errmsg(db) << endl;
        exit(1);
    } else {
        cout << "Opened database successfully" << endl;
    }

    return db;
}

void createTableIfNotExists(sqlite3 *db) {
    const char *sql;
    char **errMsg = nullptr;
    int rc;

    sql = "CREATE TABLE IF NOT EXISTS matrices(\n"
          "    matrix_name VARCHAR(30) PRIMARY KEY,\n"
          "    n INTEGER NOT NULL,\n"
          "    m INTEGER NOT NULL,\n"
          "    data TEXT NOT NULL,\n"
          "    max_length NOT NULL\n"
          ");";
    rc = sqlite3_exec(db, sql, nullptr, nullptr, errMsg);

    if (rc != SQLITE_OK) {
        cerr << "Error creating table:" << endl << errMsg << endl;
        exit(1);
    }
}

void clearTable(sqlite3 *db) {
    const char *sql;
    char **errMsg = nullptr;
    int rc;

    sql = "DELETE FROM matrices";
    rc = sqlite3_exec(db, sql, nullptr, nullptr, errMsg);

    if (rc != SQLITE_OK) {
        cerr << "Error clearing table \"matrices\":" << endl << errMsg << endl;
        exit(1);
    }
}



int main() {
    sqlite3* db = connect();

    createTableIfNotExists(db);
    clearTable(db);

    test(db);
    cout << endl << endl;
    testErrors(db);

    sqlite3_close(db);
}