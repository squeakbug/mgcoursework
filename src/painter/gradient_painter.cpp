#include "painter/gradient_painter.h"
#include "primitives/terrain_polygon_model.h"

#include <iostream>

void GradientPainter::paint(TerrainPolygonModel &block)
{
    std::vector<std::shared_ptr<Vertex>> &VBO = block.getVBO();
    std::shared_ptr<TerrainBlock> parent = block.getParent();
    std::shared_ptr<Grid> grid = parent->get_grid();
    //TODO отвязаться от grid и terrainBlock, так как если поменять порядок заполнения массива вершин, то все накроется медным тазом

    for (size_t i = 0; i < grid->height(); i++)
    {
        for (size_t j = 0; j < grid->width(); j++)
            VBO[j + grid->width() * i]->setColor(_gradient->getColor((*grid)[i][j]));
    }

}

void GradientPainter::setGradient(std::shared_ptr<Gradient> gradient)
{
    _gradient = gradient;
}
