#include <string>
#include <sstream>
#include <sqlite3/sqlite3.h>

using namespace std;

#ifndef MATRIX
#define MATRIX

class Matrix {
    private:
        int n, m;
        double **data;
        int maxLength;

        void verifyIndex(int n, int m);
        void updateMaxLength();

    public:
        Matrix(int n, int m);
        Matrix(int n);

        void set(int n, int m, double val);
        double get(int n, int m);

        Matrix operator+ (Matrix m2);
        Matrix operator- (Matrix m2);
        Matrix operator* (Matrix m2);
        friend ostream& operator<< (ostream &out, Matrix mat);
        bool operator== (Matrix m2);
        double* operator[](int i);

        int cols();
        int rows();
        void print();

        void store(sqlite3* db, const string& name);
        *Matrix(sqlite3* db, const string& name);
};

#endif