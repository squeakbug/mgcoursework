#ifndef TERRAIN_POLYGON_MODEL_H
#define TERRAIN_POLYGON_MODEL_H

#include <memory>

#include "primitives/polygonmodel.h"
#include "primitives/framemodel.h"
#include "primitives/terrain_frame_model.h"
#include "primitives/iterrain_object.h"

#include "terrain/terrainblock.h"

class TerrainPolygonModel : public PolygonModel, public ITerrainObject, public IProceduralLightmapping
{
public:
    TerrainPolygonModel(std::shared_ptr<TerrainBlock> parent);
    TerrainPolygonModel(std::shared_ptr<MaterialProperty> material, std::shared_ptr<TerrainBlock> parent);

    std::shared_ptr<SceneObject> toFrameModel() override;
    void updateTerrainValues() override;

    void setParent(std::shared_ptr<TerrainBlock> parent);
    const std::shared_ptr<TerrainBlock> getParent() const;

    void accept(LightmapGenerator &generator) override;

private:
    std::weak_ptr<TerrainBlock> _parent;
};

#endif