#include "pukan/math/matrix.hpp"

namespace pukan {

template<typename T>
Matrix<T>::Matrix(unsigned rows, unsigned columns)
   : _matrix(rows, std::vector<T>(columns, 0))
{
}

template<typename T>
Matrix<T>::Matrix(const std::vector<std::vector<T>> & matrix)
   : _matrix(matrix)
{
}

template<typename T>
T Matrix<T>::get(unsigned row, unsigned column) const
{
   return _matrix.at(row).at(column);
}

template<typename T>
void Matrix<T>::set(unsigned row, unsigned column, T value)
{
   _matrix.at(row).at(column) = value;
}

template<typename T>
unsigned Matrix<T>::getRows() const
{
   return _matrix.size();
}

template<typename T>
unsigned Matrix<T>::getColumns() const
{
   return _matrix.at(0).size();
}

template<typename T>
Matrix<T> Matrix<T>::operator + (const Matrix<T> & other) const
{

}

template<typename T>
Matrix<T> Matrix<T>::operator * (const Matrix<T> & other) const
{
   Matrix<T> result(other.getRows(), other.getColumns());

   return Matrix(
   {{ get(0, 0) * other.get(0, 0) + get(0, 1) * other.get(1, 0) },
    { get(1, 0) * other.get(0, 0) + get(1, 1) * other.get(1, 0)}});
}

template<typename T>
bool Matrix<T>::operator == (const Matrix<T> & other) const
{
   assert(getRows() == other.getRows() && getColumns() == other.getColumns());

   for(unsigned y = 0; y < getRows(); y++)
      for(unsigned x = 0; x < getColumns(); x++)
         if(_matrix[y][x] != other._matrix[y][x])
            return false;
   return true;
}

template<typename T>
bool Matrix<T>::operator != (const Matrix<T> & other) const
{
   return !(*this == other);
}

}
