#include <cassert>

#include "vector4f.h"

template<typename T>
vec4<T>::vec4()
{
    x = 0;
    y = 0;
    z = 0;
    w = 0;
}

template<typename T>
vec4<T>::vec4(T value)
{
    x = value;
    y = value;
    z = value;
    w = value;
}

template<typename T>
vec4<T>::vec4(T _x, T _y, T _z, T _w)
{
    x = _x;
    y = _y;
    z = _z;
    w = _w;
}

template<typename T>
vec4<T>::vec4(const vec4 &other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
}

template<typename T>
vec4<T>::vec4(const vec3<T> &other, T _w)
{
    x = other.x;
    y = other.y;
    z = other.z;
    w = _w;
}

template<typename T>
vec4<T>::vec4(vec4 &&other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
}

template<typename T>
vec4<T> &vec4<T>::operator=(const vec4 &other)
{
    if (&other != this)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        w = other.w;
    }

    return *this;
}

template<typename T>
vec4<T> &vec4<T>::operator=(vec4 &&other)
{
    if (&other != this)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        w = other.w;
    }

    return *this;
}

template<typename T>
vec4<T> vec4<T>::operator/(T scalar) const
{
    return vec4<T>(
        x / scalar,
        y / scalar,
        z / scalar,
        w / scalar
    );
}

template<typename T>
vec4<T> vec4<T>::operator/(const vec4 &other) const
{
    return vec4<T>(
        x / other.x,
        y / other.y,
        z / other.z,
        w / other.w
    );
}

template<typename T>
vec4<T> &vec4<T>::operator/=(T scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;

    return *this;
}

template<typename T>
vec4<T> &vec4<T>::operator/=(const vec4 &other)
{
    x /= other.x;
    y /= other.y;
    z /= other.z;
    w /= other.w;

    return *this;
}

template<typename T>
vec4<T> vec4<T>::operator*(T scalar) const
{
    return vec4<T>(
        x * scalar,
        y * scalar,
        z * scalar,
        w * scalar
    );
}

template<typename T>
vec4<T> vec4<T>::operator*(const vec4 &other) const
{
    return vec4<T>(
        x * other.x,
        y * other.y,
        z * other.z,
        w * other.w
    );
}

template<typename T>
vec4<T> &vec4<T>::operator*=(T scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;

    return *this;
}

template<typename T>
vec4<T> &vec4<T>::operator*=(const vec4 &other)
{
    x *= other.x;
    y *= other.y;
    z *= other.z;
    w *= other.w;

    return *this;
}

template<typename T>
vec4<T> vec4<T>::operator-(T scalar) const
{
    return vec4<T>(
        x - scalar,
        y - scalar,
        z - scalar,
        w - scalar
    );
}

template<typename T>
vec4<T> vec4<T>::operator-(const vec4 &other) const
{
    return vec4<T>(
        x - other.x,
        y - other.y,
        z - other.z,
        w - other.w
    );
}

template<typename T>
vec4<T> &vec4<T>::operator-=(T scalar)
{
    x -= scalar;
    y -= scalar;
    z -= scalar;
    w -= scalar;

    return *this;
}

template<typename T>
vec4<T> &vec4<T>::operator-=(const vec4 &other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;

    return *this;
}

template<typename T>
vec4<T> vec4<T>::operator-() const
{
    return vec4<T>(-x, -y, -z, -w);
}

template<typename T>
size_t vec4<T>::getDimension() const
{
    return 4;
}

template<typename T>
T vec4<T>::length() const
{
    return (T)sqrt(x*x + y*y + z*z + w*w);
}

template<typename T>
vec4<T> vec4<T>::operator+(T scalar) const
{
    return vec4<T>(
        x + scalar,
        y + scalar,
        z + scalar,
        w + scalar
    );
}

template<typename T>
vec4<T> vec4<T>::operator+(const vec4 &other) const
{
    return vec4<T>(
        x + other.x,
        y + other.y,
        z + other.z,
        w + other.w
    );
}

template<typename T>
vec4<T> &vec4<T>::operator+=(T scalar)
{
    x += scalar;
    y += scalar;
    z += scalar;
    w += scalar;

    return *this;
}

template<typename T>
vec4<T> &vec4<T>::operator+=(const vec4 &other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;

    return *this;
}

template<typename T>
const T& vec4<T>::operator[](std::size_t indx) const
{
    assert(indx >= 0 && indx < 4);

    switch(indx)
    {
    default:
    case 0:
        return x;
    case 1:
        return y;
    case 2:
        return z;
    case 3:
        return w;
    }
}

template<typename T>
T& vec4<T>::operator[](std::size_t indx)
{
    assert(indx >= 0 && indx < 4);

    switch(indx)
    {
    default:
    case 0:
        return x;
    case 1:
        return y;
    case 2:
        return z;
    case 3:
        return w;
    }
}
