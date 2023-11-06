#ifndef GRADIENT_H
#define GRADIENT_H

#include <vector>
#include <utility>
#include <algorithm>

#include "base_objects/vector3f.h"

class Gradient
{
public:
    vec3<> getColor(float value) const;

    void addStop(float stop, const vec3<> &color);
    void removeStopAtPosition(std::size_t pos);
    void setColorAtPosition(std::size_t pos, const vec3<> color);
    const vec3<> &getColorAtPosition(std::size_t pos) const;

private:
    std::vector<std::pair<float, vec3<>>> _stops;
};

#endif