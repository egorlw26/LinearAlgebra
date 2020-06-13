#pragma once

#ifdef MATHDLL_API
#define MATHDLL _declspec(dllexport)
#else
#define MATHDLL _declspec(dllimport)
#endif // !MATHDLL_API

#include<iostream>

template <class T>
class MATHDLL Matrix
{
public:
	Matrix(const size_t& i_rows, const size_t& i_columns);
	Matrix(const Matrix<T>& other);
	size_t getRows() const;
	size_t getColumns() const;
	T* operator [](const size_t& i_row);
	const T* operator [](const size_t& i_row) const;
	Matrix<T>& operator +=(const Matrix<T>& rhs);
	Matrix<T> operator *(const Matrix<T>& rhs);

	template<T>
	friend Matrix<T> operator +(Matrix<T> lhs, const Matrix<T>& rhs);

	template<T>
	friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& obj);

	~Matrix();

private:
	Matrix();
	T** mp_values;
	size_t m_rows;
	size_t m_columns;
};

template<class T>
inline Matrix<T>::Matrix() :
	mp_values(nullptr), m_rows(0), m_columns(0)
{
}

template<class T>
inline Matrix<T>::Matrix(const size_t& i_rows, const size_t& i_columns) :
	m_rows(i_rows), m_columns(i_columns)
{
	mp_values = new T * [i_rows];
	for (size_t i = 0; i < i_rows; i++)
		mp_values[i] = new T[i_columns];

	for (size_t i = 0; i < i_rows; i++)
		for (size_t j = 0; j < i_columns; j++)
			mp_values[i][j] = 0;
}

template<class T>
inline Matrix<T>::Matrix(const Matrix<T>& other) :
	m_rows(other.m_rows), m_columns(other.m_columns)
{
	mp_values = new T * [m_rows];
	for (size_t i = 0; i < m_rows; i++)
		mp_values[i] = new T[m_columns];

	for (size_t i = 0; i < m_rows; i++)
		for (size_t j = 0; j < m_columns; j++)
			mp_values[i][j] = other.mp_values[i][j];
}

template<class T>
inline size_t Matrix<T>::getRows() const
{
	return m_rows;
}

template<class T>
inline size_t Matrix<T>::getColumns() const
{
	return m_columns;
}

template<class T>
inline T* Matrix<T>::operator[](const size_t& i_row)
{
	if (i_row < 0 || i_row >= m_rows)
		throw "Index out of range, try again!";
	return mp_values[i_row];
}

template<class T>
inline const T* Matrix<T>::operator[](const size_t& i_row) const
{
	if (i_row < 0 || i_row >= m_rows)
		throw "Index out of range, try again!";
	return mp_values[i_row];
}

template<class T>
inline Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& rhs)
{
	for (size_t i = 0; i < m_rows; i++)
		for (size_t j = 0; j < m_columns; j++)
			mp_values[i][j] += rhs.mp_values[i][j];

	return *this;
}

template<class T>
inline Matrix<T> Matrix<T>::operator*(const Matrix<T>& rhs)
{
	Matrix<T> res(m_rows, rhs.m_columns);
	for (size_t res_j = 0; res_j < m_rows; ++res_j)
		for (size_t res_i = 0; res_i < rhs.m_columns; ++res_i)
			for (size_t j = 0; j < rhs.m_rows; ++j)
			{
				T l = (*this)[res_j][j];
				T r = rhs[j][res_i];
				res[res_j][res_i] += (*this)[res_j][j] * rhs[j][res_i];
			}
	return res;
}


template<class T>
inline Matrix<T>::~Matrix()
{
	for (size_t i = 0; i < m_rows; i++)
		delete[] mp_values[i];
	delete[] mp_values;
}

template<class T>
inline Matrix<T> operator+(Matrix<T> lhs, const Matrix<T>& rhs)
{
	lhs += rhs;
	return lhs;
}

template<class T>
inline std::ostream& operator<<(std::ostream& os, const Matrix<T>& obj)
{
	for(size_t i = 0; i < obj.getRows(); ++i)
		for (size_t j = 0; j < obj.getColumns(); ++j)
		{
			os << obj[i][j] << ' ';
			if (j == obj.getColumns() - 1 && i != obj.getRows() -1)
				os << '\n';
		}
	return os;
}
