#include <cassert>

#include "matrix4f.h"

template<typename T>
mat4<T>::mat4()
{
    _columns[0] = colType(0, 0, 0, 0);
    _columns[1] = colType(0, 0, 0, 0);
    _columns[2] = colType(0, 0, 0, 0);
    _columns[3] = colType(0, 0, 0, 0);
}

template<typename T>
mat4<T>::mat4(T value)
{
    _columns[0] = colType(value, 0, 0, 0);
    _columns[1] = colType(0, value, 0, 0);
    _columns[2] = colType(0, 0, value, 0);
    _columns[3] = colType(0, 0, 0, value);
}

template<typename T>
mat4<T>::mat4(const mat4 &other)
{
    _columns[0] = other[0];
    _columns[1] = other[1];
    _columns[2] = other[2];
    _columns[3] = other[3];
}

template<typename T>
mat4<T>::mat4(const colType &col1, const colType &col2, const colType &col3,  const colType &col4)
{
    _columns[0] = col1;
    _columns[1] = col2;
    _columns[2] = col3;
    _columns[3] = col4;
}

template<typename T>
mat4<T> &mat4<T>::operator=(const mat4 &other)
{
    _columns[0] = other[0];
    _columns[1] = other[1];
    _columns[2] = other[2];
    _columns[3] = other[3];
    return *this;
}

template<typename T>
mat4<T> &mat4<T>::operator*=(T scalar)
{
    _columns[0] *= scalar;
    _columns[1] *= scalar;
    _columns[2] *= scalar;
    _columns[3] *= scalar;
    return *this;
}

template<typename T>
mat4<T> &mat4<T>::operator*=(mat4<T> const &src)
{
    return (*this = *this * src);
}

template<typename T>
mat4<T> &mat4<T>::operator/=(T scalar)
{
    _columns[0] /= scalar;
    _columns[1] /= scalar;
    _columns[2] /= scalar;
    _columns[3] /= scalar;
    return *this;
}

template<typename T>
mat4<T> &mat4<T>::operator/=(mat4<T> const &src)
{
    return *this *= math<T>::inverse(src);
}

template<typename T>
mat4<T> &mat4<T>::operator+=(T scalar)
{
    _columns[0] += scalar;
    _columns[1] += scalar;
    _columns[2] += scalar;
    _columns[3] += scalar;
    return *this;
}

template<typename T>
mat4<T> &mat4<T>::operator+=(mat4<T> const &src)
{
    _columns[0] += src[0];
    _columns[1] += src[1];
    _columns[2] += src[2];
    _columns[3] += src[3];
    return *this;
}

template<typename T>
mat4<T> &mat4<T>::operator-=(T scalar)
{
    _columns[0] -= scalar;
    _columns[1] -= scalar;
    _columns[2] -= scalar;
    _columns[3] -= scalar;
    return *this;
}

template<typename T>
mat4<T> &mat4<T>::operator-=(mat4<T> const &src)
{
    _columns[0] -= src[0];
    _columns[1] -= src[1];
    _columns[2] -= src[2];
    _columns[3] -= src[3];
    return *this;
}

template<typename T>
typename mat4<T>::colType const &mat4<T>::operator[](std::size_t indx) const
{
    assert(indx >= 0 && indx < 4);
	return _columns[indx];
}

template<typename T>
typename mat4<T>::colType &mat4<T>::operator[](std::size_t indx)
{
    assert(indx >= 0 && indx < 4);
	return _columns[indx];
}

template<typename T>
mat4<T> operator*(const mat4<T> &src1, const mat4<T> &src2)
{
    mat4<T> output;

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            T scalar = 0;

            for (int k = 0; k < 4; ++k)
                scalar += src1[k][i] * src2[j][k];

            output[j][i] = scalar;
        }
    }

    return output;
}

template<typename T>
typename mat4<T>::colType operator*(const mat4<T> &src, typename mat4<T>::rowType const &vec)
{
    return typename mat4<T>::colType(
        src[0][0] * vec.x + src[1][0] * vec.y + src[2][0] * vec.z + src[3][0] * vec.w,
        src[0][1] * vec.x + src[1][1] * vec.y + src[2][1] * vec.z + src[3][1] * vec.w,
        src[0][2] * vec.x + src[1][2] * vec.y + src[2][2] * vec.z + src[3][2] * vec.w,
        src[0][3] * vec.x + src[1][3] * vec.y + src[2][3] * vec.z + src[3][3] * vec.w
    );
}

template<typename T>
typename mat4<T>::rowType operator*(typename mat4<T>::colType const &vec, const mat4<T> &src)
{
    return typename mat4<T>::rowType(
        src[0][0] * vec.x + src[0][1] * vec.y + src[0][2] * vec.z + src[0][3] * vec.w,
        src[1][0] * vec.x + src[1][1] * vec.y + src[1][2] * vec.z + src[1][3] * vec.w,
        src[2][0] * vec.x + src[2][1] * vec.y + src[2][2] * vec.z + src[2][3] * vec.w,
        src[3][0] * vec.x + src[3][1] * vec.y + src[3][2] * vec.z + src[3][3] * vec.w
    );
}

template<typename T>
mat4<T> operator*(const mat4<T> &src, T scalar)
{
    return mat4<T>(
        src[0] * scalar,
        src[1] * scalar,
        src[2] * scalar,
        src[3] * scalar
    );
}

template<typename T>
mat4<T> operator*(T scalar, const mat4<T> &src)
{
    return mat4<T>(
        src[0] * scalar,
        src[1] * scalar,
        src[2] * scalar,
        src[3] * scalar
    );
}

template<typename T>
mat4<T> operator/(const mat4<T> &src, T scalar)
{
    return mat4<T>(
        src[0] / scalar,
        src[1] / scalar,
        src[2] / scalar,
        src[3] / scalar
    );
}

template<typename T>
mat4<T> operator/(T scalar, const mat4<T> &src)
{
    return mat4<T>(
        scalar / src[0],
        scalar / src[1],
        scalar / src[2],
        scalar / src[3]
    );
}

template<typename T>
mat4<T> operator+(const mat4<T> &src1, const mat4<T> &src2)
{
    return mat4<T>(
        src1[0] + src1[0],
        src1[1] + src2[1],
        src1[2] + src2[2],
        src1[3] + src2[3]
    );
}

template<typename T>
mat4<T> operator+(const mat4<T> &src, T scalar)
{
    return mat4<T>(
        src[0] + scalar,
        src[1] + scalar,
        src[2] + scalar,
        src[3] + scalar
    );
}

template<typename T>
mat4<T> operator+(T scalar, const mat4<T> &src)
{
    return mat4<T>(
        scalar + src[0],
        scalar + src[1],
        scalar + src[2],
        scalar + src[3]
    );
}

template<typename T>
mat4<T> operator-(const mat4<T> &src1, const mat4<T> &src2)
{
    return mat4<T>(
        src1[0] - src1[0],
        src1[1] - src2[1],
        src1[2] - src2[2],
        src1[3] - src2[3]
    );
}

template<typename T>
mat4<T> operator-(const mat4<T> &src, T scalar)
{
    return mat4<T>(
        src[0] - scalar,
        src[1] - scalar,
        src[2] - scalar,
        src[3] - scalar
    );
}

template<typename T>
mat4<T> operator-(T scalar, const mat4<T> &src)
{
    return mat4<T>(
        scalar - src[0],
        scalar - src[1],
        scalar - src[2],
        scalar - src[3]
    );
}

template<typename T>
mat4<T> operator-(mat4<T> const &src)
{
    return mat4<T>(-src[0], -src[1], -src[2], -src[3]);
}

template<typename T>
std::ostream &operator<<(std::ostream &os, mat4<T> const& src)
{
    for (size_t i = 0; i < 4; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
            os << src[i][j] << '\t';
        os << std::endl;
    }

    return os;
}
