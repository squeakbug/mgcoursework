#include "lightmap/lightmap_generator.h"
#include "primitives/terrain_polygon_model.h"
#include "scene/scene.h"

LightmapGenerator::LightmapGenerator(std::shared_ptr<LightmapPool> lightmapPool)
    : _lightmapPool(lightmapPool)
{

}


void LightmapGenerator::visit(Scene &scene)
{
    for (auto &obj : scene)
    {
        if (std::dynamic_pointer_cast<IProceduralLightmapping>(obj) != nullptr)
            std::dynamic_pointer_cast<IProceduralLightmapping>(obj)->accept(*this);
    }
}

void LightmapGenerator::visit(TerrainPolygonModel &model)
{
    std::shared_ptr<FragmentShader> fragmentShader = model.getFragmentShader();
    fragmentShader->setMaterial(model.getMaterial());
    std::size_t width = model.getParent()->get_grid()->width();
    std::size_t height = model.getParent()->get_grid()->height();
    std::shared_ptr<FrameBuffer> lightmap(new FrameBuffer(height, width));
    std::vector<std::shared_ptr<Vertex>> VBO = model.getVBO();

    //TODO перенести матрицу модели в класс модели
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            Vertex v = *VBO[j + i * width];
            (*lightmap)[i][j] = fragmentShader->calculateIntencityForLightmap(v.color, v.normal);
        }
    }

    if (!_lightmapPool.expired())
        _lightmapPool.lock()->addLightMap(model.getId(), lightmap);
}

void LightmapGenerator::setLightmapPool(std::shared_ptr<LightmapPool> lightmapPool)
{
    _lightmapPool = lightmapPool;
}