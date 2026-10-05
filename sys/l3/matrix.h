#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
public:
    Matrix(int rows, int cols);
    void print() const;
    void clear();
    ~Matrix();

    int get(int row, int col) const;
    void set(int row, int col, int value);

private:
    int rows_;
    int cols_;
    int* data_;
};

#endif // MATRIX_H