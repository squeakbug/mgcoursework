#include <cmath>
#include <cassert>

#include "base_objects/vector2f.h"
#include "math/math.h"

template<typename T>
vec2<T>::vec2()
{
    x = 0;
    y = 0;
}

template<typename T>
vec2<T>::vec2(T value)
{
    x = value;
    y = value;
}

template<typename T>
vec2<T>::vec2(T _x, T _y)
{
    x = _x;
    y = _y;
}

template<typename T>
vec2<T> vec2<T>::operator/(T scalar) const
{
    return vec2<T>(
        x / scalar,
        y / scalar
    );
}

template<typename T>
vec2<T> vec2<T>::operator/(const vec2 &other) const
{
    return vec2<T>(
        x / other.x,
        y / other.y
    );
}

template<typename T>
vec2<T> &vec2<T>::operator/=(T scalar)
{
    x /= scalar;
    y /= scalar;

    return *this;
}

template<typename T>
vec2<T> &vec2<T>::operator/=(const vec2 &other)
{
    x /= other.x;
    y /= other.y;

    return *this;
}

template<typename T>
vec2<T> vec2<T>::operator*(T scalar) const
{
    return vec2<T>(
        x * scalar,
        y * scalar
    );
}

template<typename T>
vec2<T> vec2<T>::operator*(const vec2 &other) const
{
    return vec2<T>(
        x * other.x,
        y * other.y
    );
}

template<typename T>
vec2<T> &vec2<T>::operator*=(T scalar)
{
    x *= scalar;
    y *= scalar;

    return *this;
}

template<typename T>
vec2<T> &vec2<T>::operator*=(const vec2 &other)
{
    x *= other.x;
    y *= other.y;

    return *this;
}

template<typename T>
vec2<T> vec2<T>::operator-(T scalar) const
{
    return vec2<T>(
        x - scalar,
        y - scalar
    );
}

template<typename T>
vec2<T> vec2<T>::operator-(const vec2 &other) const
{
    return vec2<T>(
        x - other.x,
        y - other.y
    );
}

template<typename T>
vec2<T> &vec2<T>::operator-=(T scalar)
{
    x -= scalar;
    y -= scalar;

    return *this;
}

template<typename T>
vec2<T> &vec2<T>::operator-=(const vec2 &other)
{
    x -= other.x;
    y -= other.y;

    return *this;
}

template<typename T>
vec2<T> vec2<T>::operator+(T scalar) const
{
    return vec2<T>(
        x + scalar,
        y + scalar
    );
}

template<typename T>
vec2<T> vec2<T>::operator+(const vec2 &other) const
{
    return vec2<T>(
        x + other.x,
        y + other.y
    );
}

template<typename T>
vec2<T> &vec2<T>::operator+=(T scalar)
{
    x += scalar;
    y += scalar;

    return *this;
}

template<typename T>
vec2<T> &vec2<T>::operator+=(const vec2 &other)
{
    x += other.x;
    y += other.y;

    return *this;
}

template<typename T>
bool vec2<T>::operator==(const vec2 &other)
{
    return fabs(x - other.x) < math<T>::eps
        && fabs(y - other.y) < math<T>::eps;
}

template<typename T>
bool vec2<T>::operator!=(const vec2 &other)
{
    return !(*this == other);
}

template<typename T>
vec2<T> vec2<T>::operator-() const
{
    return vec2<T>(-x, -y);
}

template<typename T>
size_t vec2<T>::getDimension() const
{
    return 2;
}

template<typename T>
T vec2<T>::length() const
{
    return (T)sqrt(x*x + y*y);
}

template<typename T>
const T& vec2<T>::operator[](std::size_t indx) const
{
    assert(indx >= 0 && indx < 2);

    switch(indx)
    {
    default:
    case 0:
        return x;
    case 1:
        return y;
    }
}

template<typename T>
T& vec2<T>::operator[](std::size_t indx)
{
    assert(indx >= 0 && indx < 2);

    switch(indx)
    {
    default:
    case 0:
        return x;
    case 1:
        return y;
    }
}
