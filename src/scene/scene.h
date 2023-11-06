#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>

#include "visitors/visitor.h"
#include "primitives/lightsource.h"
#include "primitives/camera.h"
#include "lightmap/iprocedural_lightmapping.h"

using ObjectIterator = std::vector<std::shared_ptr<SceneObject>>::iterator;
using ConstObjectIterator = std::vector<std::shared_ptr<SceneObject>>::const_iterator;

class Scene : public IProceduralLightmapping
{
public:
    Scene();

    void accept(std::shared_ptr<Visitor> visitor);
    void accept(LightmapGenerator &generator) override;

    void add_obj(std::shared_ptr<SceneObject> &obj);
    void removeObject(ObjectIterator iter);

    const std::shared_ptr<Camera> get_camera();
    void set_camera(std::shared_ptr<Camera> camera);

    ObjectIterator begin();
    ObjectIterator end();
    ConstObjectIterator cbegin() const;
    ConstObjectIterator cend() const;

    void setUniqueId(std::shared_ptr<SceneObject> obj);

private:
    std::vector<std::shared_ptr<SceneObject>> _objects;
    std::shared_ptr<Camera> _camera;
};

#endif // SCENE_H
