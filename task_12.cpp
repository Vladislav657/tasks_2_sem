#include <iostream>

using namespace std;

class Matrix{
public:
    int rows, cols;
    double **elements;

    Matrix(int rows, int cols, double **elements){
        this->elements = new double * [rows];
        for (int i = 0; i < rows; ++i) {
            this->elements[i] = new double [cols];
            for (int j = 0; j < cols; ++j) this->elements[i][j] = elements[i][j];
        }
        this->rows = rows;
        this->cols = cols;
    }

    double neighboursAverage(int i, int j) const{
        if (i < 0 || i >= this->rows || j < 0 || j >= this->cols) throw range_error("Indices is out of range");
        int count = 0;
        double sum = 0;
        if (i - 1 >= 0 && j - 1 >= 0){
            count++;
            sum += this->elements[i - 1][j - 1];
        }
        if (i - 1 >= 0 && j + 1 < this->cols){
            count++;
            sum += this->elements[i - 1][j + 1];
        }
        if (i + 1 < this->rows && j - 1 >= 0){
            count++;
            sum += this->elements[i + 1][j - 1];
        }
        if (i + 1 < this->rows && j + 1 < this->cols){
            count++;
            sum += this->elements[i + 1][j + 1];
        }
        if (i - 1 >= 0){
            count++;
            sum += this->elements[i - 1][j];
        }
        if (i + 1 < this->rows){
            count++;
            sum += this->elements[i + 1][j];
        }
        if (j - 1 >= 0){
            count++;
            sum += this->elements[i][j - 1];
        }
        if (j + 1 < this->cols){
            count++;
            sum += this->elements[i][j + 1];
        }
        return sum == 0 ? sum : sum / count;
    }

    void smooth(){
        auto **copy = new double * [this->rows];
        for (int i = 0; i < this->rows; ++i) {
            copy[i] = new double [this->cols];
            for (int j = 0; j < this->cols; ++j) copy[i][j] = this->elements[i][j];
        }
        for (int i = 0; i < this->rows; ++i)
            for (int j = 0; j < this->cols; ++j) copy[i][j] = neighboursAverage(i, j);
        for (int i = 0; i < this->rows; ++i) delete[] this->elements[i];
        delete[] this->elements;
        this->elements = copy;
    }

    friend ostream& operator << (ostream& out, Matrix& matrix);

    ~Matrix(){
        for (int i = 0; i < this->rows; ++i) delete[] this->elements[i];
        delete[] this->elements;
    }
};

ostream& operator << (ostream& out, Matrix& matrix){
    out << endl;
    for (int i = 0; i < matrix.rows; ++i) {
        for (int j = 0; j < matrix.cols; ++j) out << matrix.elements[i][j] << ' ';
        out << endl;
    }
    return out;
}

int main(){
    int rows, cols;
    cin >> rows >> cols;
    auto **input = new double * [rows];
    for (int i = 0; i < rows; ++i) {
        input[i] = new double [cols];
        for (int j = 0; j < cols; ++j) cin >> input[i][j];
    }

    Matrix matrix = Matrix(rows, cols, input);
    matrix.smooth();
    cout << matrix;

    for (int i = 0; i < rows; ++i) delete[] input[i];
    delete[] input;
    return 0;
}
