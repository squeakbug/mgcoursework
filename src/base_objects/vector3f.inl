#include <cmath>
#include <cassert>

#include "base_objects/vector3f.h"
#include "math/math.h"

template<typename T>
vec3<T>::vec3()
{
    x = 0;
    y = 0;
    z = 0;
}

template<typename T>
vec3<T>::vec3(T value)
{
    x = value;
    y = value;
    z = value;
}

template<typename T>
vec3<T>::vec3(T _x, T _y, T _z)
{
    x = _x;
    y = _y;
    z = _z;
}

template<typename T>
vec3<T>::vec3(const vec3 &other)
{
    x = other.x;
    y = other.y;
    z = other.z;
}

template<typename T>
vec3<T>::vec3(vec3 &&other)
{
    x = other.x;
    y = other.y;
    z = other.z;
}

template<typename T>
vec3<T>::vec3(const vec4<T> &other)
{
    x = other.x;
    y = other.y;
    z = other.z;
}

template<typename T>
vec3<T> &vec3<T>::operator=(const vec3 &other)
{
    x = other.x;
    y = other.y;
    z = other.z;

    return *this;
}

template<typename T>
vec3<T> &vec3<T>::operator=(vec3 &&other)
{
    x = other.x;
    y = other.y;
    z = other.z;

    return *this;
}

template<typename T>
vec3<T> vec3<T>::operator/(T scalar) const
{
    return vec3<T>(
        x / scalar,
        y / scalar,
        z / scalar);
}

template<typename T>
vec3<T> vec3<T>::operator/(const vec3 &other) const
{
    return vec3<T>(
        x / other.x,
        y / other.y,
        z / other.z);
}

template<typename T>
vec3<T> &vec3<T>::operator/=(T scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;

    return *this;
}

template<typename T>
vec3<T> &vec3<T>::operator/=(const vec3 &other)
{
    x /= other.x;
    y /= other.y;
    z /= other.z;

    return *this;
}

template<typename T>
vec3<T> vec3<T>::operator*(T scalar) const
{
    return vec3<T>(
        x * scalar,
        y * scalar,
        z * scalar);
}

template<typename T>
vec3<T> vec3<T>::operator*(const vec3 &other) const
{
    return vec3<T>(
        x * other.x,
        y * other.y,
        z * other.z);
}

template<typename T>
vec3<T> &vec3<T>::operator*=(T scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;

    return *this;
}

template<typename T>
vec3<T> &vec3<T>::operator*=(const vec3 &other)
{
    x *= other.x;
    y *= other.y;
    z *= other.z;

    return *this;
}

template<typename T>
vec3<T> vec3<T>::operator-(T scalar) const
{
    return vec3<T>(
        x - scalar,
        y - scalar,
        z - scalar);
}

template<typename T>
vec3<T> vec3<T>::operator-(const vec3 &other) const
{
    return vec3<T>(
        x - other.x,
        y - other.y,
        z - other.z);
}

template<typename T>
vec3<T> &vec3<T>::operator-=(T scalar)
{
    x -= scalar;
    y -= scalar;
    z -= scalar;

    return *this;
}

template<typename T>
vec3<T> &vec3<T>::operator-=(const vec3 &other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;

    return *this;
}

template<typename T>
vec3<T> vec3<T>::operator+(T scalar) const
{
    return vec3<T>(
        x + scalar,
        y + scalar,
        z + scalar);
}

template<typename T>
vec3<T> vec3<T>::operator+(const vec3 &other) const
{
    return vec3<T>(
        x + other.x,
        y + other.y,
        z + other.z);
}

template<typename T>
vec3<T> &vec3<T>::operator+=(T scalar)
{
    x += scalar;
    y += scalar;
    z += scalar;

    return *this;
}

template<typename T>
vec3<T> &vec3<T>::operator+=(const vec3 &other)
{
    x += other.x;
    y += other.y;
    z += other.z;

    return *this;
}

template<typename T>
bool vec3<T>::operator==(const vec3 &other)
{
    return fabs(x - other.x) < math<T>::eps
        && fabs(y - other.y) < math<T>::eps
        && fabs(z - other.z) < math<T>::eps;
}

template<typename T>
bool vec3<T>::operator!=(const vec3 &other)
{
    return !(*this == other);
}

template<typename T>
vec3<T> vec3<T>::operator-() const
{
    return vec3<T>(-x, -y, -z);
}

template<typename T>
size_t vec3<T>::getDimension() const
{
    return 3;
}

template<typename T>
T vec3<T>::length() const
{
    return (T)sqrt(x*x + y*y + z*z);
}

template<typename T>
const T& vec3<T>::operator[](std::size_t indx) const
{
    assert(indx >= 0 && indx < 3);

    switch(indx)
    {
    default:
    case 0:
        return x;
    case 1:
        return y;
    case 2:
        return z;
    }
}

template<typename T>
T& vec3<T>::operator[](std::size_t indx)
{
    assert(indx >= 0 && indx < 3);

    switch(indx)
    {
    default:
    case 0:
        return x;
    case 1:
        return y;
    case 2:
        return z;
    }
}
