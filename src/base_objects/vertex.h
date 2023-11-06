#ifndef VERTEX_H
#define VERTEX_H

#include "base_objects/vector3f.h"

typedef double VType;

class Vertex
{
public:
    Vertex();
    Vertex(const vec3<VType> &clr, const vec3<VType> &pos, const vec3<VType> &norm);

    virtual void setColor(vec3<VType> clr);

public:
    vec3<VType> color;
    vec4<VType> position;
    vec3<VType> normal;

    vec3<VType> texCoords;
};

#endif // VERTEX_H
