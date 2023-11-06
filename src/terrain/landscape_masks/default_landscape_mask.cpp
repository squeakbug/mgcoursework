#include "default_landscape_mask.h"
#include "terrainblock.h"

#include <iostream>

void DefaultLandscapeMask::updateTerrain(std::shared_ptr<Grid> grid)
{
    for (size_t i = 0; i < grid->height(); i++)
    {
        for (size_t j = 0; j < grid->width(); j++)
            (*grid)[i][j] = (*grid)[i][j] * 1.f;
    }
}