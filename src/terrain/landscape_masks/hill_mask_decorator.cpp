#include <cmath>
#include <iostream>

#include "hill_mask_decorator.h"
#include "grid.h"

HillMaskDecorator::HillMaskDecorator(std::shared_ptr<ILandscapeMask> wrappee)
    : _wrappee(wrappee)
{

}

void HillMaskDecorator::updateTerrain(std::shared_ptr<Grid> grid)
{
    _wrappee->updateTerrain(grid);
    
    size_t xCenter = grid->width() / 2;
    size_t yCenter = grid->height() / 2;

    //TODO check grid

    float maxDist = hypot(xCenter, yCenter);

    for (size_t i = 0; i < grid->height(); i++)
    {
        for (size_t j = 0; j < grid->width(); j++)
        {
            float distFromCenter = hypot(float(i) - yCenter, float(j) - xCenter);
            float f = (maxDist - distFromCenter) / maxDist;
            (*grid)[i][j] *= f * f;
        }
    }
    
}