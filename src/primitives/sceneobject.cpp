#include "primitives/sceneobject.h"

SceneObject::SceneObject()
    : _isEnabled(true)
{

}

SceneObject::~SceneObject()
{

}

std::size_t SceneObject::getId() const
{
    return _id;
}

void SceneObject::setId(std::size_t id)
{
    _id = id;
}

void SceneObject::disable()
{
    _isEnabled = false;
}

void SceneObject::enable()
{
    _isEnabled = true;
}

bool SceneObject::isEnabled() const
{
    return _isEnabled == true;
}
