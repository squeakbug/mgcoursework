#ifndef SIMPLE_FRAGMENT_SHADER_H
#define SIMPLE_FRAGMENT_SHADER_H

#include "shaders/fragment_shader.h"

class SimpleFragmentShader : public FragmentShader
{
public:
    vec3<> shade(const Vertex &a, const Vertex &b, const Vertex &c, const vec3<> &pos) override;

protected:
    vec3<> calculateIntencity(const vec3<> &objectColor, const vec3<> &outNormal);
};

#endif