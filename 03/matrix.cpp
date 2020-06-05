#include "matrix.h"

using namespace std;

// метод определения числа строк
size_t Matrix::getRows() {
	return nrows;
}

// метод определения числа столбцов
size_t Matrix::getColumns() {
	return ncols;
}

//конструктор матрицы 
Matrix::Matrix(size_t cols, size_t rows){
    ncols = cols;
    nrows =  rows;
    m = new int[nrows * ncols];
}

//конструктор строк матрицы
Matrix::Row::Row(const Matrix* mat, size_t col){
    //r = mat->m;
    this->row_len = mat->ncols; 
    r = mat->m + col*row_len;
}

//декструктор матрицы
Matrix::~Matrix(){
     delete [] m;
    }

//деструктор сторки 
Matrix::Row::~Row() {}

//проверка на равенство 
bool Matrix::operator==(const Matrix& mat) const{
  if (this == &mat) {
    return true;
  }
  else{
      for (size_t i=0; i < mat.nrows * mat.ncols;i++){
          if (mat.m[i] != this->m[i]){
              return false;
               }
        }
        return true; 
    }
}

//проверка на неравенство 
bool Matrix::operator!=(const Matrix& mat) const{
    return !(*this == mat);
}

//умножение на число 
const Matrix& Matrix::operator*=(int n){
        for (size_t i = 0; i < ncols*nrows; ++i){
            m[i] = m[i]*n;
        }
        return *this;
    }

//символика [][]
int& Matrix::Row::operator[](size_t col){
    if (col > row_len)
        throw out_of_range("");
    return r[col];
    // return *(r+col);
}

const int& Matrix::Row::operator[](size_t col) const{
    if (col > row_len)
        throw out_of_range("");
    return r[col];
	// return *(r+col);
}

Matrix::Row Matrix::operator[](size_t rows){
    if (rows > nrows)
        throw out_of_range("");
    // return Row(this->m+rows*this->ncols, this->ncols);
    return Matrix::Row(this, rows);
}

const Matrix::Row Matrix::operator[](size_t rows) const{
    if (rows > nrows)
        throw out_of_range("");
    // const Row res(this->m+rows*this->ncols, this->ncols);
    // return res;
    return Matrix::Row(this, rows);
}