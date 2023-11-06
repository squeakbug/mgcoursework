#include "base_objects/water_vertex.h"

WaterVertex::WaterVertex()
    : Vertex()
{
    _water_intencity = 0.f;
}
WaterVertex::WaterVertex(const vec3<VType> &clr, const vec3<VType> &pos, const vec3<VType> &norm)
    : Vertex(clr, pos, norm)
{

}

void WaterVertex::setColor(vec3<VType> clr)
{
    Vertex::setColor(clr);
    color = { 0.0, 0.0, 1.0 };
}
