#include "painter/default_painter.h"
#include "primitives/terrain_polygon_model.h"


void DefaultPainter::paint(TerrainPolygonModel &block)
{
    std::vector<std::shared_ptr<Vertex>> &VBO = block.getVBO();
    std::shared_ptr<TerrainBlock> parent = block.getParent();
    std::shared_ptr<Grid> grid = parent->get_grid();

    for (size_t i = 0; i < grid->height(); i++)
    {
        for (size_t j = 0; j < grid->width(); j++)
            VBO[j + grid->width() * i]->setColor(vec3<>(255.f, 255.f, 255.f));
    }

}

