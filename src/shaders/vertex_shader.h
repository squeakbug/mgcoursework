#ifndef VERTEX_SHADER_H
#define VERTEX_SHADER_H

#include "base_objects/vertex.h"
#include "math/math.h"

class VertexShader
{
public:
    Vertex calculate(const Vertex &vert, const mat4<> &proj, const mat4<> &view, const mat4<> &model);
    Vertex calculate(const Vertex &vert, const mat4<> &projView, const mat4<> &model);
};

#endif // VERTEX_SHADER_H
