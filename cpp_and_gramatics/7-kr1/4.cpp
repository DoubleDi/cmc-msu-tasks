#include <iostream>
#include <stdexcept>
#include <cstring>

template <typename T>
class Matrix
{
    int rows;
    int cols;
    T *m = nullptr;
public:
    static const int ROWS_MAX = 16384;
    static const int COLS_MAX = 16384;
    static const int MEM_MAX = 1073741824;
    Matrix(int r, int c, T init = T()) : rows(r), cols(c)
    {
        if (c * r * sizeof(T) > MEM_MAX || c > COLS_MAX || r > ROWS_MAX || c <= 0 || r <= 0) {
            throw std::invalid_argument("Error in constructor");
        } else {
            m = new T[c * r];
            for (int i = 0; i < c * r; i++) {
                m[i] = init;
            }
        }
    }
    Matrix (const Matrix &other)
    {
        cols = other.cols;
        rows = other.rows;
        m = new T[cols * rows];
        memcpy(m, other.m, sizeof(T) * rows * cols);
    }
    Matrix & operator = (Matrix other)
    {
        if (this == &other) {
            return *this;
        }
        std::swap(cols, other.cols);
        std::swap(rows, other.rows);
        std::swap(m, other.m);
        return *this;
    }
    int get_rows() const
    {
        return rows;
    }
    int get_cols() const
    {
        return cols;
    }
    T & at(int row, int col) const
    {
        if (row >= rows || col >= cols || row < 0 || col < 0) {
            throw std::range_error("Error in at function");
        } else {
            return m[cols * row + col];
        }
    }
    ~Matrix()
    {
        if (m) {
            delete [] m;
            m = nullptr;
        }
    }
};
