#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <cstddef>

#include "errors/logicexceptions.h"

template<typename T>
class vec4;

template<typename T = double>
class vec3
{
public:
    vec3();
    vec3(T value);
    vec3(T _x, T _y, T _z);
    vec3(const vec3 &other);
    vec3(vec3 &&other);
    vec3(const vec4<T> &other);

    size_t getDimension() const;
    T length() const;

    vec3<T> &operator=(const vec3<T> &other);
    vec3<T> &operator=(vec3<T> &&other);

    vec3 operator/(T scalar) const;
    vec3 operator/(const vec3 &other) const;
    vec3 &operator/=(T scalar);
    vec3 &operator/=(const vec3 &other);

    vec3 operator*(T scalar) const;
    vec3 operator*(const vec3 &other) const;
    vec3 &operator*=(T scalar);
    vec3 &operator*=(const vec3 &other);

    vec3 operator+(T scalar) const;
    vec3 operator+(const vec3 &other) const;
    vec3 &operator+=(T scalar);
    vec3 &operator+=(const vec3 &other);

    vec3 operator-(T scalar) const;
    vec3 operator-(const vec3 &other) const;
    vec3 &operator-=(T scalar);
    vec3 &operator-=(const vec3 &other);

    bool operator==(const vec3 &other);
    bool operator!=(const vec3 &other);

    vec3 operator-() const;

    const T& operator[](std::size_t indx) const;
    T& operator[](std::size_t indx);

    union { T x, r, s; };
    union { T y, g, t; };
    union { T z, b, p; };
};

#include "vector3f.inl"

#endif // VECTOR3F_H
