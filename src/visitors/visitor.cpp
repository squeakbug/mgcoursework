#include "visitors/visitor.h"
#include "scene/scene.h"
#include "primitives/light_types/direct_light_source.h"

Visitor::~Visitor()
{

}

void Visitor::visit(Scene &scene)
{
    
}

void Visitor::visit(FrameModel &model)
{

}

void Visitor::visit(PolygonModel &model)
{

}

void Visitor::visit(LightSource &source)
{

}

void Visitor::visit(Camera &camera)
{

}

void Visitor::visit(TerrainBlock &terrain)
{

}

void Visitor::visit(LightmapPool &lightmaps)
{

}
