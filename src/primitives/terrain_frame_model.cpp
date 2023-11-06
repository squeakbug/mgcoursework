#include "primitives/terrain_frame_model.h"


TerrainFrameModel::TerrainFrameModel(std::shared_ptr<TerrainBlock> parent)
    : FrameModel(),
    _parent(parent)
{

}

TerrainFrameModel::TerrainFrameModel(std::shared_ptr<Details> details, std::shared_ptr<TerrainBlock> parent)
    : FrameModel(details),
    _parent(parent)
{

}

std::shared_ptr<SceneObject> TerrainFrameModel::toPolygonModel()
{
    std::shared_ptr<SceneObject> output;

    if (!_parent.expired())
    {
        output = std::static_pointer_cast<SceneObject>(_parent.lock()->to_polygon_model());
        output->setId(_id);
    }
    else
    {
        output = FrameModel::toPolygonModel();
    }

    return output;
}

void TerrainFrameModel::updateTerrainValues()
{
    if (!_parent.expired())
    {
        bool oldIsEnabled = _isEnabled;
        size_t oldId = _id;
        *this = *_parent.lock()->to_frame_model();
        _isEnabled = oldIsEnabled;
        _id = oldId;
    }
}

void TerrainFrameModel::setParent(std::shared_ptr<TerrainBlock> parent)
{
    _parent = parent;
}