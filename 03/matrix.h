#include <iostream>
#include <cassert> 

class Matrix {

    size_t nrows = 0;
    size_t ncols = 0;
    int* m = nullptr;

public:
    class Row{
        size_t row_len = 0;
        int* r = nullptr;

    public:
        Row(const Matrix * mat, size_t col);
        const int& operator[](size_t col) const;
        int& operator[](size_t col);
        ~Row();
    };

    Matrix(size_t rows, size_t cols);
    size_t getRows();
    size_t getColumns();
    const Row operator[](size_t rows) const;
    Row operator[](size_t rows);
    bool operator==(const Matrix& mat) const;
    bool operator!=(const Matrix& mat) const;
    const Matrix& operator*=(int n);
    ~Matrix();

};
