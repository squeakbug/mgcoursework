#ifndef IPOLY_TRANSFORMABLE_H
#define IPOLY_TRANSFORMABLE_H

#include <memory>

#include "primitives/sceneobject.h"

template<typename T>
class IPolyTransformable
{
public:
    virtual ~IPolyTransformable() = 0;

    virtual std::shared_ptr<SceneObject> toPolygonModel() = 0;
};

#include "ipoly_transformable.inl"

#endif