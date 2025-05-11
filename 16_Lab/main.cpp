#include <iostream>
#include <stdexcept>

template <class T>
class Matrix {
    int _rows;
    int _cols;
    T **_matrix = nullptr;

public:
    Matrix(int N, int M);
    Matrix(const Matrix& Other);
    ~Matrix();
    Matrix<T>& operator=(const Matrix<T>& Other);
    Matrix<T>& operator+=(const Matrix<T>& Other);
    Matrix<T> operator+(const Matrix<T>& Other);
    Matrix<T>& operator*=(const Matrix<T>& Other);
    Matrix<T> operator*(const Matrix<T>& Other);
    Matrix<T> operator++(int);
    Matrix<T>& operator++();
    T Determinant() const;
    T* operator[](int index) { return _matrix[index]; }
    
    void MakeNulls() {
        for (int i = 0; i < _rows; i++) 
            for (int j = 0; j < _cols; j++) 
                _matrix[i][j] = 0;
    }
    
    friend std::ostream& operator<<(std::ostream& out, const Matrix& Other) {
        for (int i = 0; i < Other._rows; i++) {
            for (int j = 0; j < Other._cols; j++) {
                out << Other._matrix[i][j] << " ";
            }
            out << std::endl;
        }
        return out;
    }
};

template <class T>
Matrix<T>::Matrix(int N, int M) : _rows(N), _cols(M) {
    _matrix = new T*[_rows];
    for (int i = 0; i < _rows; i++) {
        T *array = new T[_cols];
        _matrix[i] = array;
    }
}

template <class T>
Matrix<T>::~Matrix() {
    for (int i = 0; i < _rows; i++) {
        delete[] _matrix[i];
    }
    delete[] _matrix;
}

template <class T>
Matrix<T>::Matrix(const Matrix& Other) : Matrix(Other._rows, Other._cols) { // Делегирующий конструктор 
    for (int i = 0; i < _rows; i++) 
        for (int j = 0; j < _cols; j++) 
            _matrix[i][j] = Other._matrix[i][j];
} 

template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& Other) {
    if (_matrix != nullptr) { 
        for (int i = 0; i < _rows; i++){
            delete[] _matrix[i];
        }
        delete[] _matrix;
    }
    
    _rows = Other._rows;
    _cols = Other._cols;
    _matrix = new T*[_rows];
    for (int i = 0; i < _rows; i++) {
        T *array = new T[_cols];
        _matrix[i] = array;
    }

    for (int i = 0; i < _rows; i++) 
        for (int j = 0; j < _cols; j++) 
            _matrix[i][j] = Other._matrix[i][j];
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& Other) {
    if (_rows != Other._rows || _cols != Other._cols) { 
        throw std::length_error("Sizes don't match.");
    }
    for (int i = 0; i < _rows; i++) 
        for (int j = 0; j < _cols; j++) 
            _matrix[i][j] += Other._matrix[i][j];
    return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& Other) {
    Matrix<T> c = *this;
    c += Other;
    return c;
}

template <class T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& Other) {
    if (_cols != Other._rows) {
        throw std::length_error("Cols of first matrix != Rows of second matrix.");
    }
    Matrix<T> c(_rows, Other._cols);
    c.MakeNulls();
    size_t s = 0;
    for (int k = 0; k < _cols; k++) {
        for (int i = 0; i < _rows; i++) 
            for (int j = 0; j < Other._cols; j++) {
                c._matrix[i][j] += _matrix[i][k] * Other._matrix[k][j];
            }
    }
    *this = c;
    return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& Other) {
    Matrix<T> c = *this;
    c *= Other;
    return c;
}

template<class T>
Matrix<T> Matrix<T>::operator++(int) {
    Matrix c = *this;
    for (int i = 0; i < _rows; i++) 
        for (int j = 0; j < _cols; j++)
            _matrix[i][j] += 1;
    return c;
}

template<class T>
Matrix<T>& Matrix<T>::operator++() {
    for (int i = 0; i < _rows; i++) 
        for (int j = 0; j < _cols; j++)
            _matrix[i][j] += 1;
    return *this;
}

template <class T>
T Matrix<T>::Determinant() const {
    if (_rows != _cols)
        throw std::logic_error("Determinant is defined only for square matrices");

    if (_rows == 1) {
        return _matrix[0][0];
    }

    if (_rows == 2) {
        return _matrix[0][0] * _matrix[1][1] - _matrix[0][1] * _matrix[1][0];
    }

    if (_rows == 3) {
        return
            _matrix[0][0] * (_matrix[1][1] * _matrix[2][2] - _matrix[1][2] * _matrix[2][1]) -
            _matrix[0][1] * (_matrix[1][0] * _matrix[2][2] - _matrix[1][2] * _matrix[2][0]) +
            _matrix[0][2] * (_matrix[1][0] * _matrix[2][1] - _matrix[1][1] * _matrix[2][0]);
    }

    throw std::logic_error("Determinant for size > 3 is not supported.");
}

int main() {
    Matrix<int> a(2, 2);
    a[0][0] = 1;
    a[0][1] = 2;
    a[1][0] = 3;
    a[1][1] = 4;

    Matrix<int> b(2, 2);
    b[0][0] = 3;
    b[0][1] = 1;
    b[1][0] = 4;
    b[1][1] = 0;


    std::cout << a << std::endl << b << std::endl;
    Matrix<int> c = a * b;
    
    std::cout << c << std::endl;
    std::cout << c.Determinant() << std::endl;
    return 0;
}
