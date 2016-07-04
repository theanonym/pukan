#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "pukan/common.hpp"

namespace pukan {

template<typename T>
class Matrix
{
public:
   Matrix(unsigned rows, unsigned columns);
   Matrix(const std::vector<std::vector<T>> & matrix);

   T get(unsigned row, unsigned column) const;
   void set(unsigned row, unsigned column, T value);

   unsigned getRows() const;
   unsigned getColumns() const;

   Matrix<T> operator + (const Matrix<T> & other) const;
   Matrix<T> operator * (const Matrix<T> & other) const;
   bool operator == (const Matrix<T> & other) const;
   bool operator != (const Matrix<T> & other) const;

private:
   std::vector<std::vector<T>> _matrix;
};

}

#endif // MATRIX_HPP
