#ifndef VISITOR_H
#define VISITOR_H

class Scene;
class FrameModel;
class PolygonModel;
class LightSource;
class Camera;
class TerrainBlock;
class LightmapPool;

class Visitor
{
public:
    virtual ~Visitor() = 0;

    virtual void visit(Scene &scene);
    virtual void visit(FrameModel &model);
    virtual void visit(PolygonModel &model);
    virtual void visit(LightSource &source);
    virtual void visit(Camera &camera);
    virtual void visit(TerrainBlock &terrain);
    virtual void visit(LightmapPool &lightmaps);
};

#endif // VISITOR_H
