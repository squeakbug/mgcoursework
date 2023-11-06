#ifndef MATRIX4F_H
#define MATRIX4F_H

#include <iostream>

template<typename T>
class math;

template<typename T>
class vec4;

template<typename T = double>
class mat4
{
public:
    typedef vec4<T> colType;
	typedef vec4<T> rowType;

public:
    mat4();
    explicit mat4(T value);
    mat4(const mat4<T> &other);
    mat4(const colType &col1, const colType &col2, const colType &col3, const colType &col4);

    mat4 &operator=(const mat4 &other);

    mat4 &operator*=(T scalar);
    mat4 &operator*=(const mat4 &other);

    mat4 &operator/=(T scalar);
    mat4 &operator/=(const mat4 &other);

    mat4 &operator+=(T scalar);
    mat4 &operator+=(const mat4 &other);

    mat4 &operator-=(T scalar);
    mat4 &operator-=(const mat4 &other);

    const colType &operator[](std::size_t indx) const;
    colType &operator[](std::size_t indx);

private:
    colType _columns[4];
};

template<typename T>
mat4<T> operator*(const mat4<T> &src1, const mat4<T> &src2);

template<typename T>
typename mat4<T>::colType operator*(const mat4<T> &src, typename mat4<T>::rowType const &vec);

template<typename T>
typename mat4<T>::rowType operator*(typename mat4<T>::colType const &vec, const mat4<T> &src);

template<typename T>
mat4<T> operator*(const mat4<T> &src, T scalar);

template<typename T>
mat4<T> operator*(T scalar, const mat4<T> &src);

template<typename T>
mat4<T> operator/(const mat4<T> &src, T scalar);

template<typename T>
mat4<T> operator/(T scalar, const mat4<T> &src);

template<typename T>
mat4<T> operator+(const mat4<T> &src1, const mat4<T> &src2);

template<typename T>
mat4<T> operator+(const mat4<T> &src, T scalar);

template<typename T>
mat4<T> operator+(T scalar, const mat4<T> &src);

template<typename T>
mat4<T> operator-(const mat4<T> &src1, const mat4<T> &src2);

template<typename T>
mat4<T> operator-(const mat4<T> &src, T scalar);

template<typename T>
mat4<T> operator-(T scalar, const mat4<T> &src);

template<typename T>
mat4<T> operator-(mat4<T> const& src);

template<typename T>
std::ostream & operator<<(std::ostream &os, mat4<T> const& src);

#include "matrix4f.inl"

#endif // MATRIX4F_H
