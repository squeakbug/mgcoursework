#include "rect_clipping_space.h"

RectClippingSpace::RectClippingSpace(float left, float right, float bottom, float top, float near, float far, float fov, float minFov, float maxFov)
{
    _left = left;
    _right = right;
    _bottom = bottom;
    _top = top;
    _near = near;
    _far = far;
    _fov = fov;
    _minFov = minFov;
    _maxFov = maxFov;
}

void RectClippingSpace::setBottomTop(float newBottom, float newTop)
{
    _bottom = newBottom;
    _top = newTop;
}

void RectClippingSpace::setLeftRight(float newLeft, float newRight)
{
    _left = newLeft;
    _right = newRight;
}

void RectClippingSpace::setNearFar(float newNear, float newFar)
{
    _near = newNear;
    _far = newFar;
}

void RectClippingSpace::setFov(float fov)
{
    _fov = fov;
}

float RectClippingSpace::getFov()
{
    return _fov;   
}

float RectClippingSpace::getMinFov()
{
    return _minFov;
}

float RectClippingSpace::getMaxFov()
{
    return _maxFov;
}

mat4<> RectClippingSpace::getProjMatrix()
{
    float newLeft = _left / _maxFov * _fov;
    float newRight = _right / _maxFov * _fov;
    float newBottom = _bottom / _maxFov * _fov;
    float newTop = _top / _maxFov * _fov;

    return math<>::ortho(newLeft, newRight, newBottom, newTop, _near, _far);
}
