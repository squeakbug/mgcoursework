#include "primitives/terrain_polygon_model.h"

TerrainPolygonModel::TerrainPolygonModel(std::shared_ptr<TerrainBlock> parent)
    : PolygonModel(),
    _parent(parent)
{

}

TerrainPolygonModel::TerrainPolygonModel(std::shared_ptr<MaterialProperty> material, std::shared_ptr<TerrainBlock> parent)
    : PolygonModel(material),
    _parent(parent)
{

}

std::shared_ptr<SceneObject> TerrainPolygonModel::toFrameModel()
{
    std::shared_ptr<SceneObject> output;

    if (!_parent.expired())
    {
        output = std::static_pointer_cast<SceneObject>(_parent.lock()->to_frame_model());
        output->setId(_id);
    }
    else
    {
        output = PolygonModel::toFrameModel();
    }

    return output;
}

void TerrainPolygonModel::updateTerrainValues()
{
    //TODO Грубейшая ошибка: при добавлении новых полей в класс полигональной модели, они не будут копироваться, 
    // Необходимо как-то напомнить разработчику, что тут требуется скопировать некоторые данные
    // Здесь необходимо реализовать такой функционал, что копируются только те данные, которые подверглись изменению
    // Кто должен знать о том, что изменилось или что необходимо поменять???
    if (!_parent.expired())
    {
        bool oldIsEnabled = _isEnabled;
        std::shared_ptr<FragmentShader> oldFragmentShader = _fragmentShader;
        size_t oldId = _id;
        *this = *_parent.lock()->to_polygon_model();
        _fragmentShader = oldFragmentShader;
        _isEnabled = oldIsEnabled;
        _id = oldId;
    }
}

void TerrainPolygonModel::setParent(std::shared_ptr<TerrainBlock> parent)
{
    _parent = parent;
}

const std::shared_ptr<TerrainBlock> TerrainPolygonModel::getParent() const
{
    if (_parent.expired())
        return nullptr;
    else
        return _parent.lock();
}

void TerrainPolygonModel::accept(LightmapGenerator &generator)
{
    generator.visit(*this);
}
