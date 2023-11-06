#ifndef DRAWVISITOR_H
#define DRAWVISITOR_H

#include <memory>

#include "visitors/visitor.h"
#include "base_objects/vertex.h"
#include "graphics/base_drawer.h"

class DrawManager;

class DrawVisitor : public Visitor
{
public:
    DrawVisitor();
    DrawVisitor(std::shared_ptr<DrawManager> manager);

    virtual void visit(Scene &scene) override;
    virtual void visit(FrameModel &model) override;
    virtual void visit(PolygonModel &model) override;
    virtual void visit(TerrainBlock &terrain) override;
    virtual void visit(LightmapPool &lightmaps) override;

    void set_drawer(std::shared_ptr<BaseDrawer> drawer);
    void set_draw_manager(std::shared_ptr<DrawManager> manager);

private:
    void rasterBarTriangle(Vertex v1, Vertex v2, Vertex v3);

private:
    std::shared_ptr<BaseDrawer> _drawer;
    std::weak_ptr<DrawManager> _draw_manager;
};

#endif // DRAWVISITOR_H
