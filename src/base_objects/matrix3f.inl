#include <cassert>

template<typename T>
mat3<T>::mat3()
{
    _columns[0] = colType(0, 0, 0);
    _columns[1] = colType(0, 0, 0);
    _columns[2] = colType(0, 0, 0);
}

template<typename T>
mat3<T>::mat3(T value)
{
    _columns[0] = colType(value, 0, 0);
    _columns[1] = colType(0, value, 0);
    _columns[2] = colType(0, 0, value);
}

template<typename T>
mat3<T>::mat3(const mat3 &other)
{
    _columns[0] = other[0];
    _columns[1] = other[1];
    _columns[2] = other[2];
}

template<typename T>
mat3<T>::mat3(const mat4<T> &other)
{
    _columns[0] = colType(other[0]);
    _columns[1] = colType(other[1]);
    _columns[2] = colType(other[2]);
}

template<typename T>
mat3<T>::mat3(const colType &col1, const colType &col2, const colType &col3)
{
    _columns[0] = col1;
    _columns[1] = col2;
    _columns[2] = col3;
}

template<typename T>
mat3<T> &mat3<T>::operator=(const mat3 &other)
{
    _columns[0] = other[0];
    _columns[1] = other[1];
    _columns[2] = other[2];
    return *this;
}

template<typename T>
mat3<T> &mat3<T>::operator*=(T scalar)
{
    _columns[0] *= scalar;
    _columns[1] *= scalar;
    _columns[2] *= scalar;
    return *this;
}

template<typename T>
mat3<T> &mat3<T>::operator*=(mat3<T> const &src)
{
    return (*this = *this * src);
}

template<typename T>
mat3<T> &mat3<T>::operator/=(T scalar)
{
    _columns[0] /= scalar;
    _columns[1] /= scalar;
    _columns[2] /= scalar;
    return *this;
}

template<typename T>
mat3<T> &mat3<T>::operator/=(mat3<T> const &src)
{
    return *this *= math<T>::inverse(src);
}

template<typename T>
mat3<T> &mat3<T>::operator+=(T scalar)
{
    _columns[0] += scalar;
    _columns[1] += scalar;
    _columns[2] += scalar;
    return *this;
}

template<typename T>
mat3<T> &mat3<T>::operator+=(mat3<T> const &src)
{
    _columns[0] += src[0];
    _columns[1] += src[1];
    _columns[2] += src[2];
    return *this;
}

template<typename T>
mat3<T> &mat3<T>::operator-=(T scalar)
{
    _columns[0] -= scalar;
    _columns[1] -= scalar;
    _columns[2] -= scalar;
    return *this;
}

template<typename T>
mat3<T> &mat3<T>::operator-=(mat3<T> const &src)
{
    _columns[0] -= src[0];
    _columns[1] -= src[1];
    _columns[2] -= src[2];
    return *this;
}

template<typename T>
typename mat3<T>::colType const &mat3<T>::operator[](std::size_t indx) const
{
    assert(indx >= 0 && indx < 3);
	return _columns[indx];
}

template<typename T>
typename mat3<T>::colType &mat3<T>::operator[](std::size_t indx)
{
    assert(indx >= 0 && indx < 3);
	return _columns[indx];
}

template<typename T>
mat3<T> operator*(const mat3<T> &src1, const mat3<T> &src2)
{
    mat3<T> output;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            T scalar = 0;

            for (int k = 0; k < 3; ++k)
                scalar += src1[k][i] * src2[j][k];

            output[j][i] = scalar;
        }
    }

    return output;
}

template<typename T>
typename mat3<T>::colType operator*(const mat3<T> &src, typename mat3<T>::rowType const &vec)
{
    return typename mat3<T>::colType(
        src[0][0] * vec.x + src[1][0] * vec.y + src[2][0] * vec.z,
        src[0][1] * vec.x + src[1][1] * vec.y + src[2][1] * vec.z,
        src[0][2] * vec.x + src[1][2] * vec.y + src[2][2] * vec.z
    );
}

template<typename T>
typename mat3<T>::rowType operator*(typename mat3<T>::colType const &vec, const mat3<T> &src)
{
    return typename mat3<T>::rowType(
        src[0][0] * vec.x + src[0][1] * vec.y + src[0][2] * vec.z,
        src[1][0] * vec.x + src[1][1] * vec.y + src[1][2] * vec.z,
        src[2][0] * vec.x + src[2][1] * vec.y + src[2][2] * vec.z
    );
}

template<typename T>
mat3<T> operator*(const mat3<T> &src, T scalar)
{
    return mat3<T>(
        src[0] * scalar,
        src[1] * scalar,
        src[2] * scalar
    );
}

template<typename T>
mat3<T> operator*(T scalar, const mat3<T> &src)
{
    return mat3<T>(
        src[0] * scalar,
        src[1] * scalar,
        src[2] * scalar
    );
}

template<typename T>
mat3<T> operator/(const mat3<T> &src, T scalar)
{
    return mat3<T>(
        src[0] / scalar,
        src[1] / scalar,
        src[2] / scalar
    );
}

template<typename T>
mat3<T> operator/(T scalar, const mat3<T> &src)
{
    return mat3<T>(
        scalar / src[0],
        scalar / src[1],
        scalar / src[2]
    );
}

template<typename T>
mat3<T> operator+(const mat3<T> &src1, const mat3<T> &src2)
{
    return mat3<T>(
        src1[0] + src1[0],
        src1[1] + src2[1],
        src1[2] + src2[2]
    );
}

template<typename T>
mat3<T> operator+(const mat3<T> &src, T scalar)
{
    return mat3<T>(
        src[0] + scalar,
        src[1] + scalar,
        src[2] + scalar
    );
}

template<typename T>
mat3<T> operator+(T scalar, const mat3<T> &src)
{
    return mat3<T>(
        scalar + src[0],
        scalar + src[1],
        scalar + src[2]
    );
}

template<typename T>
mat3<T> operator-(const mat3<T> &src1, const mat3<T> &src2)
{
    return mat3<T>(
        src1[0] - src1[0],
        src1[1] - src2[1],
        src1[2] - src2[2]
    );
}

template<typename T>
mat3<T> operator-(const mat3<T> &src, T scalar)
{
    return mat3<T>(
        src[0] - scalar,
        src[1] - scalar,
        src[2] - scalar
    );
}

template<typename T>
mat3<T> operator-(T scalar, const mat3<T> &src)
{
    return mat3<T>(
        scalar - src[0],
        scalar - src[1],
        scalar - src[2]
    );
}

template<typename T>
mat3<T> operator-(mat3<T> const &src)
{
    return mat3<T>(-src[0], -src[1], -src[2]);
}
