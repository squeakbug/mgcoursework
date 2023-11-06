#ifndef WATER_VERTEX_H
#define WaTER_VERTEX_H

#include "base_objects/vertex.h"

class WaterVertex : public Vertex
{
public:
    WaterVertex();
    WaterVertex(const vec3<VType> &clr, const vec3<VType> &pos, const vec3<VType> &norm);

    virtual void setColor(vec3<VType> clr) override;

private:
    float _water_intencity;
};

#endif