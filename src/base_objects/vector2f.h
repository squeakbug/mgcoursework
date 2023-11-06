#ifndef VECTOR2F_H
#define VECTOR2F_H

#include <cstddef>

#include "errors/logicexceptions.h"

template<typename T = double>
class vec2
{
public:
    vec2();
    vec2(T value);
    vec2(T _x, T _y);

    size_t getDimension() const;
    T length() const;

    vec2 operator/(T scalar) const;
    vec2 operator/(const vec2 &other) const;
    vec2 &operator/=(T scalar);
    vec2 &operator/=(const vec2 &other);

    vec2 operator*(T scalar) const;
    vec2 operator*(const vec2 &other) const;
    vec2 &operator*=(T scalar);
    vec2 &operator*=(const vec2 &other);

    vec2 operator+(T scalar) const;
    vec2 operator+(const vec2 &other) const;
    vec2 &operator+=(T scalar);
    vec2 &operator+=(const vec2 &other);

    vec2 operator-(T scalar) const;
    vec2 operator-(const vec2 &other) const;
    vec2 &operator-=(T scalar);
    vec2 &operator-=(const vec2 &other);

    bool operator==(const vec2 &other);
    bool operator!=(const vec2 &other);

    vec2 operator-() const;

    const T& operator[](std::size_t indx) const;
    T& operator[](std::size_t indx);

    union { T x, s; };
    union { T y, t; };
};

#include "vector2f.inl"

#endif // VECTOR2F_H
