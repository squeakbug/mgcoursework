#include "shaders/vertex_shader.h"


Vertex VertexShader::calculate(const Vertex &vert, const mat4<> &proj, const mat4<> &view, const mat4<> &model)
{
    mat4<> projViewModel = proj * view * model;
    return calculate(vert, projViewModel, model);
}

Vertex VertexShader::calculate(const Vertex &vert, const mat4<> &projViewModel, const mat4<> &model)
{
    // Перевод вершины из локального пространства в нормализованное пространство изображения
    vec4<> pos = vert.position;
    pos = projViewModel * pos;

    Vertex output(vert);
    output.position = pos;

    if (fabs(pos.w) < math<>::eps)
        pos.w = 1.f;

    // Выполнение перспективного деления
    output.position = output.position * (1.f / pos.w);

    // Перевод нормалей из локального пространства в глобальное пространство
    output.normal = vec3<>(model * vec4<>(vert.normal, 0.f));

    return output;
}
