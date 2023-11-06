#ifndef IFRAME_TRANSFORMABLE_H
#define IFRAME_TRANSFORMABLE_H

#include <memory>

#include "primitives/sceneobject.h"

template<typename T>
class IFrameTransformable
{
public:
    virtual ~IFrameTransformable() = 0;

    virtual std::shared_ptr<SceneObject> toFrameModel() = 0;
};

#include "iframe_transformable.inl"

#endif