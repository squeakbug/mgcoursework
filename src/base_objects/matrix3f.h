#ifndef MATRIX3F_H
#define MATRIX3F_H

template<typename T>
class mat4;

template<typename T>
class math;

template<typename T>
class vec3;

template<typename T = double>
class mat3
{
public:
    typedef vec3<T> colType;
	typedef vec3<T> rowType;

public:
    mat3();
    explicit mat3(T value);
    mat3(const mat3 &other);
    mat3(const mat4<T> &other);
    mat3(const colType &col1, const colType &col2, const colType &col3);

    mat3 &operator=(const mat3 &other);

    mat3 &operator*=(T scalar);
    mat3 &operator*=(const mat3 &other);

    mat3 &operator/=(T scalar);
    mat3 &operator/=(const mat3 &other);

    mat3 &operator+=(T scalar);
    mat3 &operator+=(const mat3 &other);

    mat3 &operator-=(T scalar);
    mat3 &operator-=(const mat3 &other);

    const rowType &operator[](std::size_t indx) const;
    rowType &operator[](std::size_t indx);

private:
    colType _columns[3];
};


template<typename T>
mat3<T> operator*(const mat3<T> &src1, const mat3<T> &src2);

template<typename T>
typename mat3<T>::colType operator*(const mat3<T> &src, typename mat3<T>::rowType const &vec);

template<typename T>
typename mat3<T>::rowType operator*(typename mat3<T>::colType const &vec, const mat3<T> &src);

template<typename T>
mat3<T> operator*(const mat3<T> &src, T scalar);

template<typename T>
mat3<T> operator*(T scalar, const mat3<T> &src);

template<typename T>
mat3<T> operator/(const mat3<T> &src, T scalar);

template<typename T>
mat3<T> operator/(T scalar, const mat3<T> &src);

template<typename T>
mat3<T> operator+(const mat3<T> &src1, const mat3<T> &src2);

template<typename T>
mat3<T> operator+(const mat3<T> &src, T scalar);

template<typename T>
mat3<T> operator+(T scalar, const mat3<T> &src);

template<typename T>
mat3<T> operator-(const mat3<T> &src1, const mat3<T> &src2);

template<typename T>
mat3<T> operator-(const mat3<T> &src, T scalar);

template<typename T>
mat3<T> operator-(T scalar, const mat3<T> &src);

template<typename T>
mat3<T> operator-(mat3<T> const& src);

#include "matrix3f.inl"

#endif // MATRIX3F_H
