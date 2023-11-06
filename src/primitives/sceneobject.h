#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <memory>

#include "visitors/visitor.h"

class SceneObject
{
public:
    SceneObject();
    virtual ~SceneObject() = 0;

    virtual void accept(Visitor &visitor) = 0;

    std::size_t getId() const;
    void setId(std::size_t id);

    void disable();
    void enable();
    bool isEnabled() const;

protected:
    std::size_t _id;
    bool _isEnabled;
};

#endif // SCENEOBJECT_H
