#ifndef MATH_H
#define MATH_H

#include <cmath>

#include "base_objects/matrix3f.h"
#include "base_objects/matrix4f.h"
#include "base_objects/vector3f.h"
#include "base_objects/vector4f.h"
#include "base_objects/vector2f.h"

#define mmax2(a, b) ((a) > (b) ? (a) : (b))
#define mmin2(a, b) ((a) < (b) ? (a) : (b))
#define mmax3(a, b, c) ((a) > (b) ? mmax2((a), (c)) : mmax2((b), (c)))
#define mmin3(a, b, c) ((a) < (b) ? mmin2((a), (c)) : mmin2((b), (c)))

template<typename T = double>
class math
{
public:
    static mat4<T> translate(const mat4<T> &mat, const vec3<T> &dir);
    static mat4<T> scale(const mat4<T> &mat, const vec3<T> &dir);
    static mat4<T> rotate(const mat4<T> &mat, T angle, const vec3<T> &axis);

    static mat4<T> ortho(T left, T right, T bottom, T top, T near, T far);
    static mat4<T> perspective(T fov, T aspect_ratio, T near, T far);
    static mat4<T> lookAt(const vec3<T> &pos, const vec3<T> &target, const vec3<T> &globalUp);
    static mat4<T> image(size_t width, size_t height);

    static T radians(T angle);
    static T degrees(T angle);

    static vec3<T> reflect(const vec3<T> &lightDir, const vec3<T> &normal);

    static T dot(const vec2<T> &vec1, const vec2<T> &vec2);
    static T dot(const vec3<T> &vec1, const vec3<T> &vec2);
    static T dot(const vec4<T> &vec1, const vec4<T> &vec2);
    static vec3<T> cross(const vec3<T> &vec1, const vec3<T> &vec2);
    static vec2<T> normalize(const vec2<T> &vec);
    static vec4<T> normalize(const vec4<T> &vec);
    static vec3<T> normalize(const vec3<T> &vec);
    static T length(const vec2<T> &vec);
    static T length(const vec3<T> &vec);
    static T length(const vec4<T> &vec);

    static T clamp(T value, T min_v, T max_v);
    static T clamp(T value, T min_v);

    static mat3<T> inverse(const mat3<T> &src);
    static mat4<T> inverse(const mat4<T> &src);

    static mat3<T> transpose(const mat3<T> &src);
    static mat4<T> transpose(const mat4<T> &src);

    static T det(const mat3<T> &src);
    static T det(const mat4<T> &src);

    static T mix(T vec1, T vec2, T ratio);
    static vec2<T> mix(const vec2<T> &vec1, const vec2<T> &vec2, T ratio);
    static vec3<T> mix(const vec3<T> &vec1, const vec3<T> &vec2, T ratio);
    static vec4<T> mix(const vec4<T> &vec1, const vec4<T> &vec2, T ratio);

    static vec3<T> calculateFaceNormal(const vec3<T> &a, const vec3<T> &b, const vec3<T> &c);
    static vec3<T> calculateFaceNormal(const vec3<T> *vertices, size_t cnt);

    static vec3<T> barycentricInterpolation(const vec3<T> &a, const vec3<T> &b, const vec3<T> &c, const vec3<T> &target);
    static vec4<T> barycentricInterpolation(const vec4<T> &a, const vec4<T> &b, const vec4<T> &c, const vec3<T> &target);

    static vec3<T> toBarycentric(vec3<T> a, vec3<T> b, vec3<T> c, vec3<T> p);
    static T calcBar(vec3<T> a, vec3<T> b, vec3<T> p);

    static T lerp(T t, T a, T b);

    static T psmoothStep(T x);
    static T psmoothStep(T edge0, T edge1, T x);
    static T smoothStep(T x);
    static T smoothStep(T edge0, T edge1, T x);

public:
    static constexpr T eps = 1e-6;
    static constexpr T DEG2RAD = (T) M_PI / 180.f;
    static constexpr T RAD2DEG = 180.f / (T) M_PI;

private:
    static mat4<T> getPerspective(T left, T right, T bottom, T top, T near, T far);

private:
    math();
    math(const math &other) = delete;
    math(math &&other) = delete;
    math &operator=(const math &other) = delete;
    math &operator=(math &&other) = delete;
};

#include "math.inl"

#endif // MATH_H
