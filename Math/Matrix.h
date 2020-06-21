#pragma once

#include<iostream>
#include<string>

template <class T>
class Matrix
{
public:
	Matrix(const size_t& i_rows, const size_t& i_columns);
	Matrix(const Matrix<T>& other);
	size_t getRows() const;
	size_t getColumns() const;
	T* operator [](const size_t& i_row);
	const T* operator [](const size_t& i_row) const;
	Matrix<T> operator-() const;

	bool operator == (const Matrix<T>& rhs);

	template<class U>
	Matrix<T>& operator =(const Matrix<U>& rhs);

	Matrix<T> transpose() const;

	bool isSquare() const;

	template<class U>
	Matrix<T>& operator +=(const Matrix<U>& rhs);

	template<class U>
	Matrix<T>& operator -=(const Matrix<U>& rhs);

	template<class T, class U>
	friend Matrix<decltype(std::declval<T>() + std::declval<U>())> operator + (const Matrix<T>& lhs, const Matrix<U>& rhs);
	
	template<class T, class U>
	friend Matrix<decltype(std::declval<T>() - std::declval<U>())> operator - (const Matrix<T>& lhs, const Matrix<U>& rhs);

	template<class T, class U>
	friend Matrix<decltype(std::declval<T>()* std::declval<U>())> operator * (const Matrix<T>& lhs, const Matrix<U>& rhs);

	template<class T, class U>
	friend Matrix<decltype(std::declval<T>()* std::declval<U>())> operator * (const Matrix<T>& lhs, const U& rhs);

	template<class T, class U>
	friend Matrix<decltype(std::declval<T>()* std::declval<U>())> operator * (const U& lhs, const Matrix<T>& rhs);

	static Matrix<T> createIdentity(const size_t dimension);

	double determinant() const;

	Matrix<T> removeRowAndColumn(const size_t i_row, const size_t i_column) const;

	std::string toString() const;

	~Matrix();

private:
	Matrix();
	T* mp_values;
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
	size_t size = i_rows * i_columns;
	mp_values = new T[size];
	for (size_t i = 0; i < size; ++i)
		mp_values[i] = 0;

}

template<class T>
inline Matrix<T>::Matrix(const Matrix<T>& other) :
	m_rows(other.m_rows), m_columns(other.m_columns)
{
	size_t size = m_rows * m_columns;
	mp_values = new T[size];

	for (size_t i = 0; i < size; ++i)
		mp_values[i] = other.mp_values[i];
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
	return (mp_values + i_row * m_columns);
}

template<class T>
inline const T* Matrix<T>::operator[](const size_t& i_row) const
{
	if (i_row < 0 || i_row >= m_rows)
		throw "Index out of range, try again!";
	return (mp_values + i_row * m_columns);
}

template<class T>
inline Matrix<T> Matrix<T>::operator-() const
{
	Matrix<T> res(*this);
	for (size_t i = 0; i < m_rows * m_columns; ++i)
		res.mp_values[i] *= -1;
	return res;
}

template<class T>
inline bool Matrix<T>::operator==(const Matrix<T>& rhs)
{
	for (size_t i = 0; i < m_rows * m_columns; ++i)
		if (mp_values[i] != rhs.mp_values[i])
			return false;
	return true;
}

template<class T>
template<class U>
inline Matrix<T>& Matrix<T>::operator=(const Matrix<U>& rhs)
{
	size_t size = rhs.m_rows * rhs.m_columns;
	mp_values = new T * [size];
	for (size_t i = 0; i < size; ++i)
		mp_values[i] = rhs.mp_values[i];
	return *this;
}

template<class T>
template<class U>
inline Matrix<T>& Matrix<T>::operator+=(const Matrix<U>& rhs)
{
	if (m_rows != rhs.m_rows || m_columns != rhs.m_columns)
		throw "You can't add matrix with different dimensions!";

	size_t size = m_rows * m_columns;
	for (size_t i = 0; i < size; ++i)
		mp_values[i] += rhs.mp_values[i];

	return *this;
}

template<class T>
template<class U>
inline Matrix<T>& Matrix<T>::operator-=(const Matrix<U>& rhs)
{
	*this += -rhs;
	return *this;
}

template<class T>
inline Matrix<T> Matrix<T>::createIdentity(const size_t dimension)
{
	Matrix<T> res(dimension, dimension);
	for (size_t i = 0; i < dimension; ++i)
		res[i][i] = 1;
	return res;
}

template<class T>
inline double Matrix<T>::determinant() const
{
	if (!isSquare())
		throw "You can calculate determinant only for square matrix";

	if (m_rows == 2)
		return (double)mp_values[0] * mp_values[3] - mp_values[1] * mp_values[2];
	if (m_rows == 3)
		return (double)
		mp_values[0] * mp_values[4] * mp_values[8] +
		mp_values[1] * mp_values[5] * mp_values[6] +
		mp_values[2] * mp_values[3] * mp_values[7] - 
		mp_values[2] * mp_values[4] * mp_values[6] -
		mp_values[1] * mp_values[3] * mp_values[8] -
		mp_values[0] * mp_values[5] * mp_values[7];

	double determinant = 0;
	for (size_t j = 0; j < m_columns; ++j)
		if ((*this)[0][j] != 0)
		{
			auto test = removeRowAndColumn(0, j);
			determinant += std::pow(-1, j) * mp_values[j] * removeRowAndColumn(0, j).determinant();
		}
	return determinant;
}

template<class T>
inline Matrix<T> Matrix<T>::removeRowAndColumn(const size_t i_row, const size_t i_column) const
{
	Matrix<T> res(m_rows - 1, m_columns - 1);
	for(size_t i = 0; i < m_rows; ++i)
		for (size_t j = 0; j < m_columns; ++j)
		{
			if (i < i_row && j < i_column)
				res[i][j] = (*this)[i][j];
			if (i < i_row && j > i_column)
				res[i][j - 1] = (*this)[i][j];
			if (i > i_row && j < i_column)
				res[i - 1][j] = (*this)[i][j];
			if (i > i_row && j > i_column)
				res[i - 1][j - 1] = (*this)[i][j];
		}
	return res;
}

template<class T>
inline std::string Matrix<T>::toString() const
{
	std::string res = "";
	for (size_t i = 0; i < m_rows; ++i)
		for (size_t j = 0; j < m_columns; ++j)
		{
			res += std::to_string((*this)[i][j]) + ' ';
			if (j == m_columns - 1 && i != m_rows - 1)
				res += '\n';
		}
	return res;
}

template<class T>
inline Matrix<T>::~Matrix()
{
	delete[] mp_values;
	mp_values = nullptr;
}

template<class T>
inline Matrix<T> Matrix<T>::transpose() const
{
	Matrix<T> res(*this);
	for (size_t i = 0; i < m_rows; ++i)
		for (size_t j = 0; j < m_columns; ++j)
			res[i][j] = (*this)[j][i];
	return res;
}

template<class T>
inline bool Matrix<T>::isSquare() const
{
	return m_rows == m_columns;
}

template<class T, class U>
inline Matrix<decltype(std::declval<T>()* std::declval<U>())> operator*(const Matrix<T>& lhs, const U& rhs)
{
	Matrix<decltype(std::declval<T>()* std::declval<U>())> res(lhs.m_rows, lhs.m_columns);

	for (size_t i = 0; i < lhs.getRows() * lhs.getColumns(); ++i)
		res.mp_values[i] = lhs.mp_values[i] * rhs;
	return res;
}

template<class T, class U>
inline Matrix<decltype(std::declval<T>()* std::declval<U>())> operator*(const U& lhs, const Matrix<T>& rhs)
{
	return rhs * lhs;
}

template<class T, class U>
inline Matrix<decltype(std::declval<T>() + std::declval<U>())> operator+(const Matrix<T>& lhs, const Matrix<U>& rhs)
{
	Matrix<decltype(std::declval<T>() + std::declval<U>())> res(lhs.m_rows, lhs.m_columns);
	for (size_t i = 0; i < res.m_rows * res.m_columns; ++i)
		res.mp_values[i] = lhs.mp_values[i] + rhs.mp_values[i];

	return res;
}

template<class T, class U>
inline Matrix<decltype(std::declval<T>() - std::declval<U>())> operator-(const Matrix<T>& lhs, const Matrix<U>& rhs)
{
	Matrix<decltype(std::declval<T>() - std::declval<U>())> res(lhs.m_rows, lhs.m_columns);
	for (size_t i = 0; i < res.m_rows * res.m_columns; ++i)
		res.mp_values[i] = lhs.mp_values[i] - rhs.mp_values[i];
	return res;
}

template<class T, class U>
inline Matrix<decltype(std::declval<T>()* std::declval<U>())> operator*(const Matrix<T>& lhs, const Matrix<U>& rhs)
{
	Matrix<decltype(std::declval<T>()* std::declval<U>())> res (lhs.m_rows, lhs.m_rows);
	for (size_t res_j = 0; res_j < lhs.m_rows; ++res_j)
		for (size_t res_i = 0; res_i < rhs.m_columns; ++res_i)
			for (size_t j = 0; j < rhs.m_rows; ++j)
				res[res_j][res_i] += lhs[res_j][j] * rhs[j][res_i];
	return res;
}
