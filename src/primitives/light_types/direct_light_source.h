#ifndef DIRECT_LIGHT_SOURCE_H
#define DIRECT_LIGHT_SOURCE_H

#include "primitives/lightsource.h"
#include "base_objects/vector3f.h"

class DirectLightSource : public LightSource
{
public:
    DirectLightSource();
    DirectLightSource(float ambient, float diffuse, float specular, const vec3<> &color, bool isEnabled, const vec3<> &direction);
    DirectLightSource(const LightSource &properties, const vec3<> &direction);

    const vec3<> &getDirection() const;
    void setDirection(const vec3<> &direction);

    mat4<> getViewMatrix() const;
    mat4<> getProjMatrix() const;

private:
    vec3<> _direction;
};

#endif