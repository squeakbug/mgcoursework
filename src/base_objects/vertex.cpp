#include "vertex.h"

Vertex::Vertex()
{

}

Vertex::Vertex(const vec3<VType> &clr, const vec3<VType> &pos, const vec3<VType> &norm)
    : color(clr), position(pos), normal(norm)
{

}

void Vertex::setColor(vec3<VType> clr)
{
    color = clr;
}
