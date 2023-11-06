#ifndef CLIPPING_SPACE_H
#define CLIPPING_SPACE_H

#include "math/math.h"

enum class ClipSpaceType
{
    ORTHO,
    PERSPECTIVE
};

class ClippingSpace
{
public:
    ClippingSpace();

    virtual mat4<> getProjMatrix() = 0;

    virtual void setFov(float fov) = 0;
    virtual float getFov() = 0;
    virtual float getMinFov() = 0;
    virtual float getMaxFov() = 0;
};

#endif // CLIPPING_SPACE_H
