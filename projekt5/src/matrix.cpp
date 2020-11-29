#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sys/stat.h>

#include <matrix.hpp>

using namespace std;


Matrix::Matrix(int n, int m) {
    if (n <= 0) {
        stringstream errorMsg;
        errorMsg << "n should be greater than 0" << endl;
        errorMsg << "n: " << n << endl;
        throw invalid_argument(errorMsg.str());
    }
    if (m <= 0) {
        stringstream errorMsg;
        errorMsg << "m should be greater than 0" << endl;
        errorMsg << "m: " << m << endl;
        throw invalid_argument(errorMsg.str());
    }

    this->n = n;
    this->m = m;
    this->maxLength = 1;

    data = new double*[n];
    for(int i = 0; i < n; i++)
        data[i] = new double[m];
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            data[i][j] = 0;
}


Matrix::Matrix(int n) {
    if (n <= 0) {
        stringstream errorMsg;
        errorMsg << "n should be greater than 0" << endl;
        errorMsg << "n: " << n << endl;
        throw invalid_argument(errorMsg.str());
    }

    this->n = n;
    this->m = n;
    this->maxLength = 1;

    data = new double*[n];
    for(int i = 0; i < n; ++i)
        data[i] = new double[n];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            data[i][j] = 0;
}


void Matrix::verifyIndex(int n, int m) {
    if (n >= this->n) {
        stringstream errorMsg;
        errorMsg << "n should be less than matrix.n" << endl;
        errorMsg << "matrix.n: " << this->n << endl;
        errorMsg << "n: " << n << endl;
        throw out_of_range(errorMsg.str());
    } else if (n < 0) {
        stringstream errorMsg;
        errorMsg << "n should be positive" << endl;
        errorMsg << "n: " << n << endl;
        throw out_of_range(errorMsg.str());
    } else if (m >= this->m) {
        stringstream errorMsg;
        errorMsg << "m should be less than Matrix.m" << endl;
        errorMsg << "matrix.m: " << this->m << endl;
        errorMsg << "m: " << n << endl;
        throw out_of_range(errorMsg.str());
    } else if (m < 0) {
        stringstream errorMsg;
        errorMsg << "m should be positive" << endl;
        errorMsg << "m: " << m << endl;
        throw out_of_range(errorMsg.str());
    }
}


void Matrix::set(int n, int m, double val) {
    verifyIndex(n, m);
    data[n][m] = val;
}


double Matrix::get(int n, int m) {
    verifyIndex(n, m);
    return data[n][m];
};


Matrix Matrix::add(Matrix m2) {
    if (this->n != m2.n || this->m != m2.m) {
        stringstream errorMsg;
        errorMsg << "Matrix dimension mismatch" << endl;
        errorMsg << "m1: " << this->n << "x" << this->m  << endl;
        errorMsg << "m2: " << m2.n << "x" << m2.m  << endl;
        throw invalid_argument(errorMsg.str());
    }

    Matrix m3(n, m);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            m3.data[i][j] = this->data[i][j] + m2.data[i][j];

    return m3;
};


Matrix Matrix::subtract(Matrix m2) {
    if (this->n != m2.n || this->m != m2.m) {
        stringstream errorMsg;
        errorMsg << "Matrix dimension mismatch" << endl;
        errorMsg << "m1: " << this->n << "x" << this->m  << endl;
        errorMsg << "m2: " << m2.n << "x" << m2.m  << endl;
        throw logic_error(errorMsg.str());
    }

    Matrix m3(n, m);

    for (int i = 0; i < n; i++) 
        for (int j = 0; j < m; j++) 
            m3.data[i][j] = this->data[i][j] - m2.data[i][j];

    return m3;
};


Matrix Matrix::multiply(Matrix m2) {
    if (this->m != m2.n) {
        stringstream errorMsg;
        errorMsg << "Matrices dimension mismatch" << endl;
        errorMsg << "m1: " << this->n << "x" << this->m  << endl;
        errorMsg << "m2: " << m2.n << "x" << m2.m  << endl;
        throw invalid_argument(errorMsg.str());
    }

    Matrix m3(this->n, m2.m);

    for (int i = 0; i < this->n; i++) {
        for (int j = 0; j < m2.m; j++) {
            double sum = 0;
            for (int k = 0; k < m2.n; k++)
                sum += this->data[i][k] * m2.data[k][j];
            m3.data[i][j] = sum;
        }
    }

    return m3;
};


int Matrix::cols() {
    return n;
};


int Matrix::rows() {
    return m;
};

void Matrix::updateMaxLength() {
    double value;
    int length;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            value = data[i][j];

            stringstream ss;
            ss << value;
            length = ss.str().length();

            if (length > maxLength)
                maxLength = length;
        }
    }
}

void Matrix::print() {
    updateMaxLength();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cout << left << setw(maxLength) << data[i][j] << " ";
        cout << endl;
    }
};


void Matrix::store(string filename, string path) {
    ofstream output;

    struct stat info{};
    if (stat(path.c_str(), &info) != 0) {
        string errorMsg = "Cannot access directory \"" + path + "\"\n";
        throw(invalid_argument(errorMsg));

    } else if(!(info.st_mode & S_IFDIR)) {
        string errorMsg = '"' + path + "\" is not a directory\n";
        throw(invalid_argument(errorMsg));
    }

    string fullPath = path + '/' + filename;

    output.open(fullPath);
    if (output.is_open()) {
        output << n << ' ' << m << endl;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++)
                output << data[i][j] << ' ';
            output << endl;
        }
        
        cout << "Successfully created file \"" << filename << '"' << endl;
        output.close();
    } else {
        string errorMsg = "Could not create file at \"" + fullPath + "\"\n";
        throw(runtime_error(errorMsg));
    }
};


Matrix::Matrix(string filename, string path) {
    ifstream input;
    string fullPath = path + '/' + filename;

    input.open(fullPath);
    if (input.is_open()) {
        input >> this->n;
        input >> this->m;
        this->maxLength = 1;

        data = new double*[n];

        for (int i = 0; i < n; i++) {
            data[i] = new double[m];

            for (int j = 0; j < m; j++)
                input >> data[i][j];
        }
        
        input.close();
    } else {
        string errorMsg = "Could not read file at \"" + fullPath + "\"\n";
        throw(runtime_error(errorMsg));
    }
}