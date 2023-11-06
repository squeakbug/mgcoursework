#include "errors/math_exceptions.h"
#include "math/math.h"

template<typename T>
math<T>::math()
{

}

template<typename T>
mat4<T> math<T>::translate(const mat4<T> &mat, const vec3<T> &dir)
{
    mat4<T> output(T(1));

    output[3][0] = dir.x;
    output[3][1] = dir.y;
    output[3][2] = dir.z;

    output *= mat;

    return output;
}

template<typename T>
mat4<T> math<T>::scale(const mat4<T> &mat, const vec3<T> &dir)
{
    mat4<T> output(T(1));

    output[0][0] = dir.x;
    output[1][1] = dir.y;
    output[2][2] = dir.z;

    output *= mat;

    return output;
}

template<typename T>
mat4<T> math<T>::rotate(const mat4<T> &mat, T angle, const vec3<T> &axis)
{
    mat4<T> output(1.0);

    T c = (T) cos(angle);
    T s = (T) sin(angle);
    T x = axis.x;
    T y = axis.y;
    T z = axis.z;

    output[0][0] = (T(1) - c) * x * x + c;
    output[0][1] = (T(1) - c) * x * y - s * z;
    output[0][2] = (T(1) - c) * x * z + s * y;

    output[1][0] = (T(1) - c) * x * y + s * z;
    output[1][1] = (T(1) - c) * y * y + c;
    output[1][2] = (T(1) - c) * y * z - s * x;

    output[2][0] = (T(1) - c) * x * z - s * y;
    output[2][1] = (T(1) - c) * y * z + s * x;
    output[2][2] = (T(1) - c) * z * z + c;

    output *= mat;

    return output;
}

template<typename T>
mat4<T> math<T>::ortho(T left, T right, T bottom, T top, T near, T far)
{
    mat4<T> output(T(1));

    output[0][0] = T(2) / (right - left);
    output[3][0] = -(right + left) / (right - left);

    output[1][1] = T(2) / (top - bottom);
    output[3][1] = -(top + bottom) / (top - bottom);

    output[2][2] = T(2) / (far - near);
    output[3][2] = (far + near) / (far - near);

    return output;
}

template<typename T>
mat4<T> math<T>::getPerspective(T left, T right, T bottom, T top, T near, T far)
{
    mat4<T> output(T(1));

    output[0][0] = T(2) * near / (right - left);
    output[2][0] = (right + left) / (right - left);

    output[1][1] = T(2) * near / (top - bottom);
    output[2][1] = (top + bottom) / (top - bottom);

    output[2][2] = -(far + near) / (far - near);
    output[3][2] = -(T(2) * far * near) / (far - near);

    output[2][3] = T(-1);
    output[3][3] = T(0);

    return output;
}

template<typename T>
mat4<T> math<T>::perspective(T fov, T aspect_ratio, T near, T far)
{
    if (aspect_ratio < math<>::eps)
        throw ZeroAspectRatio(__FILE__, "Math class", __LINE__);

    float tangent = tan(fov / 2);           // Получить тангенс половины угла обзора
    float height = near * tangent;          // Получить половину высоты ближайшей к наблюдателю плоскости
    float width = height * aspect_ratio;    // Получить половину ширины ближайшей к наблюдателю плоскости

    return math<>::getPerspective(-width, width, -height, height, near, far);
}

template<typename T>
mat4<T> math<T>::lookAt(const vec3<T> &pos, const vec3<T> &target, const vec3<T> &globalUp)
{
    vec3<T> forward = math<T>::normalize(pos - target);
    vec3<T> right = math<T>::normalize(math<T>::cross(forward, math<T>::normalize(globalUp)));
    vec3<T> up = math<T>::normalize(math<T>::cross(right, forward));

    mat4<T> rotation(T(1));
    rotation[0][0] = -right[0];
    rotation[1][0] = -right[1];
    rotation[2][0] = -right[2];
    rotation[0][1] = up[0];
    rotation[1][1] = up[1];
    rotation[2][1] = up[2];
    rotation[0][2] = forward[0];
    rotation[1][2] = forward[1];
    rotation[2][2] = forward[2];

    mat4<T> translation(T(1));
    translation = math<T>::translate(translation, -pos);

    return rotation * translation;
}

template<typename T>
mat4<T> math<T>::image(size_t width, size_t height)
{
    mat4<T> imageMatrix;
    imageMatrix[0][0] = T(width)/2;   imageMatrix[0][1] = 0.f;           imageMatrix[0][2] = 0.f;   imageMatrix[0][3] = 0.f;
    imageMatrix[1][0] = 0.f;          imageMatrix[1][1] = T(height)/2;   imageMatrix[1][2] = 0.f;   imageMatrix[1][3] = 0.f;
    imageMatrix[2][0] = 0.f;          imageMatrix[2][1] = 0.f;           imageMatrix[2][2] = 1.f;   imageMatrix[2][3] = 0.f;
    imageMatrix[3][0] = T(width)/2;   imageMatrix[3][1] = T(height)/2;   imageMatrix[3][2] = 0.f;   imageMatrix[3][3] = 1.f;

    return imageMatrix;
}

template<typename T>
T math<T>::radians(T angle)
{
    return angle * M_PI / T(180);
}

template<typename T>
T math<T>::degrees(T angle)
{
    return angle * T(180) / M_PI;
}

template<typename T>
vec3<T> math<T>::reflect(const vec3<T> &lightDir, const vec3<T> &normal)
{
    T alpha = T(1);
    T betta = T(2) * math<T>::dot(-lightDir, normal);

    return lightDir * alpha + normal * betta;
}

template<typename T>
T math<T>::dot(const vec2<T> &vec1, const vec2<T> &vec2)
{
    return vec1.x*vec2.x + vec1.y*vec2.y;
}

template<typename T>
T math<T>::dot(const vec3<T> &vec1, const vec3<T> &vec2)
{
    return vec1.x*vec2.x + vec1.y*vec2.y + vec1.z*vec2.z;
}

template<typename T>
T math<T>::dot(const vec4<T> &vec1, const vec4<T> &vec2)
{
    return vec1.x*vec2.x + vec1.y*vec2.y + vec1.z*vec2.z + vec1.w*vec2.w;
}

template<typename T>
vec3<T> math<T>::cross(const vec3<T> &vec1, const vec3<T> &vec2)
{
    vec3<T> output;

    output.x = vec1.y*vec2.z - vec2.y*vec1.z;
    output.y = -(vec1.x*vec2.z - vec2.x*vec1.z);
    output.z = vec1.x*vec2.y - vec2.x*vec1.y;

    return output;
}

template<typename T>
vec2<T> math<T>::normalize(const vec2<T> &vec)
{
    T len = vec.length();
    vec2<T> output;

    if (len > math<T>::eps)
    {
        output.x = vec.x / len;
        output.y = vec.y / len;
    }

    return output;
}

template<typename T>
vec4<T> math<T>::normalize(const vec4<T> &vec)
{
    T len = vec.length();
    vec4<T> output;

    if (len > math<T>::eps)
    {
        output.x = vec.x / len;
        output.y = vec.y / len;
        output.z = vec.z / len;
        output.w = vec.w / len;
    }

    return output;
}

template<typename T>
vec3<T> math<T>::normalize(const vec3<T> &vec)
{
    T len = vec.length();
    vec3<T> output;

    if (len > math<T>::eps)
    {
        output.x = vec.x / len;
        output.y = vec.y / len;
        output.z = vec.z / len;
    }

    return output;
}

template<typename T>
T math<T>::length(const vec2<T> &vec)
{
    return vec.length();
}

template<typename T>
T math<T>::length(const vec3<T> &vec)
{
    return vec.length();
}

template<typename T>
T math<T>::length(const vec4<T> &vec)
{
    return vec.length();
}

template<typename T>
T math<T>::clamp(T value, T min_v, T max_v)
{
    if (value > max_v)
        return max_v;
    if (value < min_v)
        return min_v;

    return value;
}

template<typename T>
T math<T>::clamp(T value, T min_v)
{
    if (value < min_v)
        return min_v;

    return value;
}

template<typename T>
mat3<T> math<T>::inverse(const mat3<T> &src)
{
    T oneOverDeterminant = T(1) / math<T>::det(src);

    mat3<T> inverse;
    inverse[0][0] = + (src[1][1] * src[2][2] - src[2][1] * src[1][2]) * oneOverDeterminant;
    inverse[1][0] = - (src[1][0] * src[2][2] - src[2][0] * src[1][2]) * oneOverDeterminant;
    inverse[2][0] = + (src[1][0] * src[2][1] - src[2][0] * src[1][1]) * oneOverDeterminant;
    inverse[0][1] = - (src[0][1] * src[2][2] - src[2][1] * src[0][2]) * oneOverDeterminant;
    inverse[1][1] = + (src[0][0] * src[2][2] - src[2][0] * src[0][2]) * oneOverDeterminant;
    inverse[2][1] = - (src[0][0] * src[2][1] - src[2][0] * src[0][1]) * oneOverDeterminant;
    inverse[0][2] = + (src[0][1] * src[1][2] - src[1][1] * src[0][2]) * oneOverDeterminant;
    inverse[1][2] = - (src[0][0] * src[1][2] - src[1][0] * src[0][2]) * oneOverDeterminant;
    inverse[2][2] = + (src[0][0] * src[1][1] - src[1][0] * src[0][1]) * oneOverDeterminant;

    return inverse;
}

template<typename T>
mat4<T> math<T>::inverse(const mat4<T> &src)
{
    T coef00 = src[2][2] * src[3][3] - src[3][2] * src[2][3];
    T coef02 = src[1][2] * src[3][3] - src[3][2] * src[1][3];
    T coef03 = src[1][2] * src[2][3] - src[2][2] * src[1][3];

    T coef04 = src[2][1] * src[3][3] - src[3][1] * src[2][3];
    T coef06 = src[1][1] * src[3][3] - src[3][1] * src[1][3];
    T coef07 = src[1][1] * src[2][3] - src[2][1] * src[1][3];

    T coef08 = src[2][1] * src[3][2] - src[3][1] * src[2][2];
    T coef10 = src[1][1] * src[3][2] - src[3][1] * src[1][2];
    T coef11 = src[1][1] * src[2][2] - src[2][1] * src[1][2];

    T coef12 = src[2][0] * src[3][3] - src[3][0] * src[2][3];
    T coef14 = src[1][0] * src[3][3] - src[3][0] * src[1][3];
    T coef15 = src[1][0] * src[2][3] - src[2][0] * src[1][3];

    T coef16 = src[2][0] * src[3][2] - src[3][0] * src[2][2];
    T coef18 = src[1][0] * src[3][2] - src[3][0] * src[1][2];
    T coef19 = src[1][0] * src[2][2] - src[2][0] * src[1][2];

    T coef20 = src[2][0] * src[3][1] - src[3][0] * src[2][1];
    T coef22 = src[1][0] * src[3][1] - src[3][0] * src[1][1];
    T coef23 = src[1][0] * src[2][1] - src[2][0] * src[1][1];

    vec4<T> fac0(coef00, coef00, coef02, coef03);
    vec4<T> fac1(coef04, coef04, coef06, coef07);
    vec4<T> fac2(coef08, coef08, coef10, coef11);
    vec4<T> fac3(coef12, coef12, coef14, coef15);
    vec4<T> fac4(coef16, coef16, coef18, coef19);
    vec4<T> fac5(coef20, coef20, coef22, coef23);

    vec4<T> vec0(src[1][0], src[0][0], src[0][0], src[0][0]);
    vec4<T> vec1(src[1][1], src[0][1], src[0][1], src[0][1]);
    vec4<T> vec2(src[1][2], src[0][2], src[0][2], src[0][2]);
    vec4<T> vec3(src[1][3], src[0][3], src[0][3], src[0][3]);

    vec4<T> inv0(vec1 * fac0 - vec2 * fac1 + vec3 * fac2);
    vec4<T> inv1(vec0 * fac0 - vec2 * fac3 + vec3 * fac4);
    vec4<T> inv2(vec0 * fac1 - vec1 * fac3 + vec3 * fac5);
    vec4<T> inv3(vec0 * fac2 - vec1 * fac4 + vec2 * fac5);

    vec4<T> signA(+1, -1, +1, -1);
    vec4<T> signB(-1, +1, -1, +1);
    mat4<T> inverse(inv0 * signA, inv1 * signB, inv2 * signA, inv3 * signB);

    vec4<T> row0(inverse[0][0], inverse[1][0],inverse[2][0], inverse[3][0]);

    vec4<T> dot0(src[0] * row0);
    T dot1 = (dot0.x + dot0.y) + (dot0.z + dot0.w);

    T oneOverDeterminant = T(1) / dot1;

    return inverse * oneOverDeterminant;
}

template<typename T>
T math<T>::det(const mat3<T> &src)
{
    T det1 = src[0][0] * (src[1][1]*src[2][2] - src[1][2]*src[2][1]);
    T det2 = -src[0][1] * (src[1][0]*src[2][2] - src[1][2]*src[2][0]);
    T det3 = src[0][2] * (src[1][0]*src[2][1] - src[1][1]*src[2][0]);

    return det1 + det2 + det3;
}

template<typename T>
T math<T>::det(const mat4<T> &src)
{
    T minor00 = src[2][2] * src[3][3] - src[3][2] * src[2][3];
    T minor01 = src[2][1] * src[3][3] - src[3][1] * src[2][3];
    T minor02 = src[2][1] * src[3][2] - src[3][1] * src[2][2];
    T minor03 = src[2][0] * src[3][3] - src[3][0] * src[2][3];
    T minor04 = src[2][0] * src[3][2] - src[3][0] * src[2][2];
    T minor05 = src[2][0] * src[3][1] - src[3][0] * src[2][1];

    vec4<T> detCof(
        + (src[1][1] * minor00 - src[1][2] * minor01 + src[1][3] * minor02),
        - (src[1][0] * minor00 - src[1][2] * minor03 + src[1][3] * minor04),
        + (src[1][0] * minor01 - src[1][1] * minor03 + src[1][3] * minor05),
        - (src[1][0] * minor02 - src[1][1] * minor04 + src[1][2] * minor05)
    );

    return src[0][0] * detCof[0] + src[0][1] * detCof[1] +
        src[0][2] * detCof[2] + src[0][3] * detCof[3];
}

template<typename T>
mat3<T> math<T>::transpose(const mat3<T> &src)
{
    mat3<T> output(src);

    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < i; j++)
            std::swap(output[i][j], output[j][i]);        
    }
}

template<typename T>
mat4<T> math<T>::transpose(const mat4<T> &src)
{
    mat4<T> output(src);

    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < i; j++)
            std::swap(output[i][j], output[j][i]);        
    }
    

    return output;
}

template<typename T>
static T mix(T vec1, T vec2, T ratio)
{
    return vec1 * (T(1) - ratio) + vec2 * ratio;
}

template<typename T>
static vec2<T> mix(const vec2<T> &vec1, const vec2<T> &vec2, T ratio)
{
    T new_x = vec1.x * (T(1) - ratio) + vec2.x * ratio;
    T new_y = vec1.y * (T(1) - ratio) + vec2.y * ratio;

    return vec3<T>(new_x, new_y);
}

template<typename T>
vec3<T> math<T>::mix(const vec3<T> &vec1, const vec3<T> &vec2, T ratio)
{
    T new_x = vec1.x * (T(1) - ratio) + vec2.x * ratio;
    T new_y = vec1.y * (T(1) - ratio) + vec2.y * ratio;
    T new_z = vec1.z * (T(1) - ratio) + vec2.z * ratio;

    return vec3<T>(new_x, new_y, new_z);
}

template<typename T>
vec4<T> math<T>::mix(const vec4<T> &vec1, const vec4<T> &vec2, T ratio)
{
    T new_x = vec1.x * (T(1) - ratio) + vec2.x * ratio;
    T new_y = vec1.y * (T(1) - ratio) + vec2.y * ratio;
    T new_z = vec1.z * (T(1) - ratio) + vec2.z * ratio;
    T new_w = vec1.w * (T(1) - ratio) + vec2.w * ratio;

    return vec4<T>(new_x, new_y, new_z, new_w);
}

template<typename T>
vec3<T> math<T>::calculateFaceNormal(const vec3<T> &a, const vec3<T> &b, const vec3<T> &c)
{
    vec3<T> normal;

    normal.x = (a.y - b.y)*(a.z + b.z) + (b.y - c.y)*(b.z + c.z) + (c.y - a.y)*(c.z + a.z);
    normal.y = (a.z - b.z)*(a.x + b.x) + (b.z - c.z)*(b.x + c.x) + (c.z - a.z)*(c.x + a.x);
    normal.z = (a.x - b.x)*(a.y + b.y) + (b.x - c.x)*(b.y + c.y) + (c.x - a.x)*(c.y + a.y);

    return normal;
}

template<typename T>
vec3<T> math<T>::calculateFaceNormal(const vec3<T> *vertices, size_t cnt)
{
    vec3<T> normal = { 0, 0, 0 };

    for (int i = 0; i < cnt; ++i)
    {
        size_t nextVertIndx = (i+1)%cnt;
        normal.x += (vertices[i].y - vertices[nextVertIndx].y) * (vertices[i].z + vertices[nextVertIndx].z);
        normal.y += (vertices[i].z - vertices[nextVertIndx].z) * (vertices[i].x + vertices[nextVertIndx].x);
        normal.z += (vertices[i].x - vertices[nextVertIndx].x) * (vertices[i].y + vertices[nextVertIndx].y);
    }

    return normal;
}

template<typename T>
vec4<T> math<T>::barycentricInterpolation(const vec4<T> &a, const vec4<T> &b, const vec4<T> &c, const vec3<T> &target)
{
    T x = math<T>::dot({a.x, b.x, c.x}, target);
    T y = math<T>::dot({a.y, b.y, c.y}, target);
    T z = math<T>::dot({a.z, b.z, c.z}, target);
    T w = math<T>::dot({a.w, b.w, c.w}, target);
    return vec4<T>(x, y, z, w);
}

template<typename T>
vec3<T> math<T>::barycentricInterpolation(const vec3<T> &a, const vec3<T> &b, const vec3<T> &c, const vec3<T> &target)
{
    T x = math<T>::dot({a.x, b.x, c.x}, target);
    T y = math<T>::dot({a.y, b.y, c.y}, target);
    T z = math<T>::dot({a.z, b.z, c.z}, target);
    return vec3<T>(x, y, z);
}

template<typename T>
T math<T>::lerp(T t, T a, T b)
{
    return a + t * (b - a);
}

template<typename T>
T math<T>::psmoothStep(T x)
{
    return x * x * x * (x * (x * T(6) - T(15)) + T(10));
}

template<typename T>
T math<T>::psmoothStep(T edge0, T edge1, T x)
{
    x = math<T>::clamp((x - edge0) / (edge1 - edge0), T(0), T(1));

    return x * x * x * (x * (x * T(6) - T(15)) + T(10));
}

template<typename T>
T math<T>::smoothStep(T x)
{
    return x * x * (T(3) - T(2) * x);
}

template<typename T>
T math<T>::smoothStep(T edge0, T edge1, T x)
{
    x = math<T>::clamp((x - edge0) / (edge1 - edge0), T(0), T(1)); 

    return x * x * (T(3) - T(2) * x);
}


template<typename T>
T math<T>::calcBar(vec3<T> a, vec3<T> b, vec3<T> p)
{
    return (a.y - b.y) * p.x + (b.x - a.x) * p.y + (a.x * b.y - b.x * a.y);
}

// Edge подход
template<typename T>
vec3<T> math<T>::toBarycentric(vec3<T> a, vec3<T> b, vec3<T> c, vec3<T> p)
{
    T numA = calcBar(c, b, p);
    T numB = calcBar(a, c, p);

    T denumA = calcBar(c, b, a);
    T denumB = calcBar(a, c, b);

    T x = numA / denumA;
    T y = numB / denumB;
    T z = 1 - x - y;

    return vec3<T>(x, y, z);
}
