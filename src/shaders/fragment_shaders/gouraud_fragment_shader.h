#ifndef GOURAUD_FRAGMENT_SHADER_H
#define GOURAUD_FRAGMENT_SHADER_H

#include "shaders/fragment_shader.h"

class GouraudFragmentShader : public FragmentShader
{
public:
    vec3<> shade(const Vertex &a, const Vertex &b, const Vertex &c, const vec3<> &pos) override;

protected:
    vec3<> calculateIntencity(const vec3<> &objectColor, const vec3<> &outNormals);
};

#endif