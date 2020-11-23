#include <string>
#include <sstream>

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

        Matrix add(Matrix m2);
        Matrix subtract(Matrix m2);
        Matrix multiply(Matrix m2);

        int cols();
        int rows();
        void print();

        void store(string filename, string path);
        Matrix(string filename, string path);
};

#endif