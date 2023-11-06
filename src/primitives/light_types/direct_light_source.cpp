#include "direct_light_source.h"

static const vec3<> defaultDirection = { 1.f, 1.f, 1.f };

DirectLightSource::DirectLightSource()
    : LightSource(),
    _direction(defaultDirection)
{

}

DirectLightSource::DirectLightSource(float ambient, float diffuse, float specular, const vec3<> &color, bool isEnabled, const vec3<> &direction)
    : LightSource(ambient, diffuse, specular, color, isEnabled),
    _direction(direction)
{

}

DirectLightSource::DirectLightSource(const LightSource &properties, const vec3<> &direction)
    : LightSource(properties),
    _direction(direction)
{

}

const vec3<> &DirectLightSource::getDirection() const
{
    return _direction;
}

void DirectLightSource::setDirection(const vec3<> &direction)
{
    _direction = direction;
}

mat4<> DirectLightSource::getViewMatrix() const
{
    vec3<> pos = math<>::normalize(-_direction) * 100.f;
    vec3<> forward = math<>::normalize(_direction) * 100.f;
    vec3<> right = math<>::normalize(math<>::cross(forward, math<>::normalize({ 0.f, 0.f, 1.f })));
    vec3<> up    = math<>::normalize(math<>::cross(right, forward));

    return math<>::lookAt(pos, { 0.f, 0.f, 0.f }, up); 
    
}

mat4<> DirectLightSource::getProjMatrix() const
{
    return math<>::ortho(-100.f, 100.f, -100.f, 100.f, 0.1f, 1000.f);
}
