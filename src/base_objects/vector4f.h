#ifndef VECTOR4F_H
#define VECTOR4F_H

#include "base_objects/vector3f.h"
#include "errors/logicexceptions.h"

template<typename T = double>
class vec4
{
public:
    vec4();
    vec4(T value);
    vec4(T _x, T _y, T _z, T _w);
    vec4(const vec4 &other);
    vec4(const vec3<T> &other, T _w = 1.0);
    vec4(vec4 &&other);

    size_t getDimension() const;
    T length() const;

    vec4 &operator=(const vec4 &other);
    vec4 &operator=(vec4 &&other);

    vec4 operator/(T scalar) const;
    vec4 operator/(const vec4 &other) const;
    vec4 &operator/=(T scalar);
    vec4 &operator/=(const vec4 &other);
    
    vec4 operator*(T scalar) const;
    vec4 operator*(const vec4 &other) const;
    vec4 &operator*=(T scalar);
    vec4 &operator*=(const vec4 &other);

    vec4 operator+(T scalar) const;
    vec4 operator+(const vec4 &other) const;
    vec4 &operator+=(T scalar);
    vec4 &operator+=(const vec4 &other);

    vec4 operator-(T scalar) const;
    vec4 operator-(const vec4 &other) const;
    vec4 &operator-=(T scalar);
    vec4 &operator-=(const vec4 &other);

    vec4 operator-() const;

    const T& operator[](std::size_t indx) const;
    T& operator[](std::size_t indx);

    union { T x, r, s; };
    union { T y, g, t; };
    union { T z, b, p; };
    union { T w, a, q; };
};

#include "vector4f.inl"

#endif // VECTOR4F_H
