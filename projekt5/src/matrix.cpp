#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>
#include <sys/stat.h>
#include <math.h>

#include <matrix.hpp>
#include <sqlite3/sqlite3.h>

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


Matrix Matrix::operator+(Matrix m2) {
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


Matrix Matrix::operator-(Matrix m2) {
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
            m3.data[i][j] = this->data[i][j] - m2.data[i][j];

    return m3;
};


Matrix Matrix::operator*(Matrix m2) {
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
}


void Matrix::store(sqlite3 *db, const string& name) {
    char *zErrMsg = nullptr;
    int rc;

    stringstream ss;
    ss << "INSERT INTO matrices ('matrix_name', 'n', 'm', 'data', 'max_length') ";
    ss << "VALUES ('" << name  << "', '" << this->n << "', '" << this->m << "', '";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            ss << data[i][j] << ' ';
    ss << "', '" << this->maxLength << "');";

    const string & sql_str = ss.str();
    const char* sql = sql_str.c_str();

    rc = sqlite3_exec(db, sql, nullptr, nullptr, &zErrMsg);

    if (rc != SQLITE_OK) {
        string errorMsg;
        if (!strcmp(zErrMsg, "UNIQUE constraint failed: matrices.matrix_name"))
            errorMsg = "Matrix with name \"" + name + "\" already exists in database";
        else {
            errorMsg = "Could not store matrix \"" + name + "\"";
        }
        throw(runtime_error(errorMsg));

    } else {
        cout << "Successfully stored matrix \"" << name << '"' << endl;
    }
};

int loadMatrixData(void *data, int argc, char **argv, char **azColName) {
    vector<string> *v = (vector<string> *)(data);

    v->push_back(argv[1]);
    v->push_back(argv[2]);
    v->push_back(argv[3]);
    v->push_back(argv[4]);

    return 0;
}

Matrix::Matrix(sqlite3 *db, const string& name) {
    char *zErrMsg = nullptr;
    int rc;
    const char *sql;
    string sql_str;
    vector<string> matrixData;

    sql_str = "SELECT * FROM matrices WHERE matrix_name == '" + name + "'";
    sql = sql_str.c_str();

    rc = sqlite3_exec(db, sql, loadMatrixData, &matrixData, &zErrMsg);
    if (rc != SQLITE_OK) {
        string errorMsg = "Error loading matrix \"" + name + "\": " + zErrMsg;
        throw(runtime_error(errorMsg));
    } else {
        if (!matrixData.empty()) {
            cout << "Successfully loaded matrix \"" << name << '"' << endl;
        } else {
            string errorMsg = "No such matrix \"" + name + "\"\n";
            throw(runtime_error(errorMsg));
        }
    }

    string nStr = matrixData[0];
    string mStr = matrixData[1];
    stringstream dataSS(matrixData[2]);
    string maxLengthStr = matrixData[3];

    this->n = atoi(nStr.c_str());
    this->m = atoi(mStr.c_str());
    this->maxLength = atoi(maxLengthStr.c_str());

    data = new double*[n];

    for (int i = 0; i < n; i++) {
        data[i] = new double[m];

        for (int j = 0; j < m; j++) {
            string buf;
            dataSS >> buf;

            data[i][j] = atof(buf.c_str());
        }
    }
}

ostream& operator<<(ostream &out, Matrix mat) {
    out << mat.cols() << " " << mat.rows() << endl;
    for (int i = 0; i < mat.cols(); i++) {
        for (int j = 0; j < mat.rows(); j++)
            out << mat.get(i, j) << ' ';
        out << endl;
    }
    return out;
}

bool Matrix::operator==(Matrix m2) {
    if (n != m2.n || m != m2.m) {
        cout << "111" << endl;
        return false;
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (fabs(data[i][j] - m2.data[i][j] > 0.0000000001))
                return false;

    return true;
}

double *Matrix::operator[](int i) {
    if (i >= this->n) {
        stringstream errorMsg;
        errorMsg << "n should be less than matrix.n" << endl;
        errorMsg << "matrix.n: " << this->n << endl;
        errorMsg << "n: " << n << endl;
        throw out_of_range(errorMsg.str());
    } else if (i < 0) {
        stringstream errorMsg;
        errorMsg << "n should be positive" << endl;
        errorMsg << "n: " << n << endl;
        throw out_of_range(errorMsg.str());
    }

    return data[i];
}
