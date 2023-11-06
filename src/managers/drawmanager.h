#ifndef DRAWMANAGER_H
#define DRAWMANAGER_H

#include <memory>

#include "managers/basemanager.h"

#include "visitors/drawvisitor.h"
#include "terrain/terrainblock.h"
#include "primitives/camera.h"
#include "scene/scene.h"
#include "lightmap/lightmap_pool.h"
#include "shadowmap/shadowmap_pool.h"

class DrawManager : public BaseManager
{
public:
    static std::shared_ptr<DrawManager> instance();

    void set_main_visitor(std::shared_ptr<DrawVisitor> visitor);
    void set_heightmap_visitor(std::shared_ptr<DrawVisitor> visitor);
    void set_lightmap_visitor(std::shared_ptr<DrawVisitor> visitor);

    std::shared_ptr<DrawVisitor> getMainVisitor();

    void set_cam(std::shared_ptr<Camera> camera);
    std::shared_ptr<Camera> get_cam();

    void setLightmapUsing(bool state);
    bool getLightmapUsing() const;

    void setShadowmapUsing(bool state);
    bool getShadowmapUsing() const;

    void draw_scene(std::shared_ptr<Scene> scene);
    void draw_heightmap(std::shared_ptr<TerrainBlock> terrain);
    void draw_lightmap(std::shared_ptr<LightmapPool> lightmap);

    void setLightmapPool(std::shared_ptr<LightmapPool> pool);
    const std::shared_ptr<LightmapPool> getLightmapPool() const;

    void setShadowmapPool(std::shared_ptr<ShadowmapPool> pool);
    const std::shared_ptr<ShadowmapPool> getShadowmapPool() const;

private:
    DrawManager();
    DrawManager(const DrawManager &other) = delete;
    DrawManager &operator=(const DrawManager &other) = delete;

private:
    std::shared_ptr<DrawVisitor> _main_visitor;
    std::shared_ptr<DrawVisitor> _heightmap_visitor;
    std::shared_ptr<DrawVisitor> _lightmap_visitor;
    std::shared_ptr<Camera> _camera;

    bool _isLightmapUsing { false };
    std::shared_ptr<LightmapPool> _lightmapPool;

    bool _isShadowmapUsing { false };
    std::shared_ptr<ShadowmapPool> _shadowmapPool;
};

#endif // DRAWMANAGER_H
