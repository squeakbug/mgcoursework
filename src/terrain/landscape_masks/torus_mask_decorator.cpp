#include <cmath>
#include <iostream>

#include "terrain/landscape_masks/torus_mask_decorator.h"
#include "terrain/grid.h"
#include "math/math.h"

TorusMaskDecorator::TorusMaskDecorator(std::shared_ptr<ILandscapeMask> wrappee)
    : _wrappee(wrappee)
{

}

void TorusMaskDecorator::updateTerrain(std::shared_ptr<Grid> grid)
{
    _wrappee->updateTerrain(grid);
    
    size_t xCenter = grid->width() / 2;
    size_t yCenter = grid->height() / 2;

    //TODO check grid

    auto func = [](float dist){ return math<>::clamp(-cos(dist * M_PI * 2), 0.f, 1.f); };

    for (size_t i = 0; i < grid->height(); i++)
    {
        for (size_t j = 0; j < grid->width(); j++)
        {
            float distFromCenter = hypot(float(i) - yCenter, float(j) - xCenter) / grid->width();
            float f = func(distFromCenter);
            (*grid)[i][j] *= f;
        }
    }
}