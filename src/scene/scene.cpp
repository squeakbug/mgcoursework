#include "scene/scene.h"

Scene::Scene()
{

}


void Scene::accept(std::shared_ptr<Visitor> visitor)
{
    visitor->visit(*this);
}

void Scene::accept(LightmapGenerator &generator)
{
    generator.visit(*this);
}

void Scene::add_obj(std::shared_ptr<SceneObject> &obj)
{
    setUniqueId(obj);
    _objects.push_back(obj);
}

void Scene::removeObject(ObjectIterator iter)
{
    _objects.erase(iter);
}

const std::shared_ptr<Camera> Scene::get_camera()
{
    return _camera;
}

void Scene::set_camera(std::shared_ptr<Camera> camera)
{
    _camera = camera;
}

ObjectIterator Scene::begin()
{
    return _objects.begin();
}

ObjectIterator Scene::end()
{
    return _objects.end();
}

ConstObjectIterator Scene::cbegin() const
{
    return _objects.cbegin();
}

ConstObjectIterator Scene::cend() const
{
    return _objects.cend();
}

void Scene::setUniqueId(std::shared_ptr<SceneObject> obj)
{
    for (size_t i = 0; i < _objects.size(); i++)
    {
        bool isFinded = false;

        for (size_t j = 0; j < _objects.size(); ++j)
        {
            if (_objects[j]->getId() == i)
            {
                isFinded = true;
                break;
            }
        }

        if (!isFinded)
        {
            obj->setId(i);
            return ;
        }
    }

    obj->setId(_objects.size());
}
