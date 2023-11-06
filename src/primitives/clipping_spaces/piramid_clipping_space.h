#ifndef PIRAMID_CLIPPING_SPACE_H
#define PIRAMID_CLIPPING_SPACE_H

#include "math/math.h"
#include "primitives/clipping_space.h"

#define D2R(d) ((d)/180.f*M_PI)

class PiramidClippingSpace : public ClippingSpace
{
public:
    PiramidClippingSpace(float fov, float aspectRatio, float near, float far, float minFov=D2R(1.f), float maxFov=D2R(45.f));

    void setAspectRatio(float newAspectRatio);
    void setNearFar(float newNear, float newFar);

    virtual mat4<> getProjMatrix() override;

    void setFov(float fov) override;
    virtual float getFov() override;
    virtual float getMinFov() override;
    virtual float getMaxFov() override;

private:
    float _fov, _minFov, _maxFov;
    float _aspectRatio;
    float _near, _far;
};

#endif // PIRAMID_CLIPPING_SPACE_H
