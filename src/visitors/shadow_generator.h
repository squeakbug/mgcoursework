#ifndef SHADOW_GENERATOR_H
#define SHADOW_GENERATOR_H

#include <memory>

#include "primitives/light_types/direct_light_source.h"
#include "frame_buffers/z_buffer.h"
#include "visitors/visitor.h"
#include "graphics/base_drawer.h"

//TODO Этот класс предназначен для генерации теней от направленных источников
// Для поддержки кубических теней следует выделить базовый класс
class ShadowGenerator : public Visitor
{
public:
    ShadowGenerator();

    void visit(Scene &scene) override;
    void visit(PolygonModel &model) override;

    const std::shared_ptr<ZBuffer> getShadowmap() const;
    void clearShadowmap();

    void setCurrentLightSource(std::shared_ptr<DirectLightSource> source);
    const std::shared_ptr<DirectLightSource> getCurrentLightSource() const;

    void set_drawer(std::shared_ptr<BaseDrawer> drawer);

private:
    mat4<> getProjMatrix(std::shared_ptr<DirectLightSource>);
    mat4<> getViewMatrix(std::shared_ptr<DirectLightSource>);

private:
    std::shared_ptr<ZBuffer> _shadowmap;
    std::shared_ptr<DirectLightSource> _currentLightSource;
    std::weak_ptr<BaseDrawer> _drawer;
};

#endif