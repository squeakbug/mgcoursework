#ifndef TERRAIN_FRAME_MODEL_H
#define TERRAIN_FRAME_MODEL_H

#include <memory>

#include "primitives/framemodel.h"
#include "primitives/terrain_polygon_model.h"
#include "primitives/iterrain_object.h"

#include "terrain/terrainblock.h"

class TerrainFrameModel : public FrameModel, public ITerrainObject
{
public:
    TerrainFrameModel(std::shared_ptr<TerrainBlock> parent);
    TerrainFrameModel(std::shared_ptr<Details> details, std::shared_ptr<TerrainBlock> parent);

    std::shared_ptr<SceneObject> toPolygonModel() override;
    void updateTerrainValues() override;

    void setParent(std::shared_ptr<TerrainBlock> parent);

private:
    std::weak_ptr<TerrainBlock> _parent;
};

#endif