#ifndef LIGHTMAP_GENERATOR_H
#define LIGHTMAP_GENERATOR_H

#include "lightmap/lightmap_pool.h"

class Scene;
class TerrainPolygonModel;

class LightmapGenerator
{
public:
    LightmapGenerator(std::shared_ptr<LightmapPool> lightmapPool);

    void visit(Scene &scene);
    void visit(TerrainPolygonModel &model);

    void setLightmapPool(std::shared_ptr<LightmapPool> lightmapPool);

private:
    std::weak_ptr<LightmapPool> _lightmapPool;
};

#endif