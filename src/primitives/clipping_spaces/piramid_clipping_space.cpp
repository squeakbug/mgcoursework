#include "piramid_clipping_space.h"


PiramidClippingSpace::PiramidClippingSpace(float fov, float aspectRatio, float near, float far, float minFov, float maxFov)
{
    _fov = fov;
    _aspectRatio = aspectRatio;
    _near = near;
    _far = far;
    _minFov = minFov;
    _maxFov = maxFov;
}

void PiramidClippingSpace::setAspectRatio(float newAspectRatio)
{
    _aspectRatio = newAspectRatio;
}

void PiramidClippingSpace::setNearFar(float newNear, float newFar)
{
    _near = newNear;
    _far = newFar;
}

void PiramidClippingSpace::setFov(float fov)
{
    _fov = fov;
}

float PiramidClippingSpace::getFov()
{
    return _fov;
}

float PiramidClippingSpace::getMinFov()
{
    return _minFov;
}

float PiramidClippingSpace::getMaxFov()
{
    return _maxFov;
}

mat4<> PiramidClippingSpace::getProjMatrix()
{
    return math<>::perspective(_fov, _aspectRatio, _near, _far);
}
