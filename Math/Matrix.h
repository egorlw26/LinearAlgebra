#pragma once

#include<iostream>

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
	Matrix<T>& operator +=(const Matrix<T>& rhs);
	Matrix<T>& operator -=(const Matrix<T>& rhs);

	Matrix<T> transpose() const;

	bool isSquare() const;

	template<class T, class U>
	friend Matrix<decltype(std::declval<T>()* std::declval<U>())> operator * (const Matrix<T>& lhs, const U& rhs);

	template<class T, class U>
	friend Matrix<decltype(std::declval<T>()* std::declval<U>())> operator * (const U& lhs, const Matrix<T>& rhs);

	template<class T, class U>
	friend Matrix<decltype(std::declval<T>() + std::declval<U>())> operator + (const Matrix<T>& lhs, const Matrix<U>& rhs);
	
	template<class T, class U>
	friend Matrix<decltype(std::declval<T>() - std::declval<U>())> operator - (const Matrix<T>& lhs, const Matrix<U>& rhs);

	template<class T, class U>
	friend Matrix<decltype(std::declval<T>()* std::declval<U>())> operator * (const Matrix<T>& lhs, const Matrix<U>& rhs);

	template<class U>
	friend std::ostream& operator<<(std::ostream& os, const Matrix<U>& obj);

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
inline Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& rhs)
{
	if (m_rows != rhs.m_rows || m_columns != rhs.m_columns)
		throw "You can't add matrix with different dimensions!";

	size_t size = m_rows * m_columns;
	for (size_t i = 0; i < size; ++i)
		mp_values[i] += rhs.mp_values[i];

	return *this;
}

template<class T>
inline Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& rhs)
{
	*this += -rhs;
	return *this;
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

template<class T>
inline std::ostream& operator<<(std::ostream& os, const Matrix<T>& obj)
{
	for (size_t i = 0; i < obj.getRows(); ++i)
		for (size_t j = 0; j < obj.getColumns(); ++j)
		{
			os << obj[i][j] << ' ';
			if (j == obj.getColumns() - 1 && i != obj.getRows() - 1)
				os << '\n';
		}
	return os;
}
