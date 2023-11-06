#ifndef RECT_CLIPPING_SPACE_H
#define RECT_CLIPPING_SPACE_H

#include "math/math.h"
#include "primitives/clipping_space.h"

#define D2R(d) ((d)/180.f*M_PI)

class RectClippingSpace : public ClippingSpace
{
public:
    RectClippingSpace(float left, float right, float bottom, float top, float near, float far, float fov=D2R(45.f), float minFov=D2R(1.f), float maxFov=D2R(45.f));

    void setBottomTop(float newBottom, float newTop);
    void setLeftRight(float newLeft, float newRight);
    void setNearFar(float newNear, float newFar);

    virtual mat4<> getProjMatrix() override;

    virtual void setFov(float fov) override;
    virtual float getFov() override;
    virtual float getMinFov() override;
    virtual float getMaxFov() override;

private:
    float _bottom, _top;
    float _left, _right;
    float _near, _far;

    float _fov;
    float _minFov, _maxFov;
};

#endif // RECT_CLIPPING_SPACE_H
