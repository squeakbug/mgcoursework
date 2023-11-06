#include <cmath>
#include <iostream>

#include "terrain/landscape_masks/smooth_mask_decorator.h"
#include "terrain/grid.h"
#include "math/math.h"

SmoothMaskDecorator::SmoothMaskDecorator(std::shared_ptr<ILandscapeMask> wrappee, size_t radius, size_t repeatCnt)
    : _wrappee(wrappee)
{
    _radius = radius;
    _repeatCnt = repeatCnt;
}

static int lim(int value, int min, int max)
{
    if (value >= max)
        value = max-1;
    if (value < min)
        value = min;
    return value;
}

void SmoothMaskDecorator::updateTerrain(std::shared_ptr<Grid> grid)
{
    _wrappee->updateTerrain(grid);

    size_t h = grid->height();
    size_t w = grid->width();
    for (size_t r = 0; r < _repeatCnt; ++r)
    {
        for (size_t i = 0; i < h; i++)
        {
            for (size_t j = 0; j < w; j++)
            {
                float kernelSum = (*grid)[i][j];

                for (size_t k = 1; k <= _radius; ++k)
                {
                    kernelSum += (*grid)[lim(i-k, 0, h)][j];
                    kernelSum += (*grid)[lim(i+k, 0, h)][j];
                    for (size_t ik = 1; ik <= k; ++ik)
                    {
                        kernelSum += (*grid)[lim(i-k, 0, h)][lim(j+ik, 0, h)];
                        kernelSum += (*grid)[lim(i-k, 0, h)][lim(j-ik, 0, w)];
                        kernelSum += (*grid)[lim(i+k, 0, h)][lim(j+ik, 0, h)];
                        kernelSum += (*grid)[lim(i+k, 0, h)][lim(j-ik, 0, w)];
                    }

                    kernelSum += (*grid)[i][lim(j+k, 0, w)];
                    kernelSum += (*grid)[i][lim(j-k, 0, w)];
                    for (size_t ik = 1; ik < k; ++ik)
                    {
                        kernelSum += (*grid)[lim(i+ik, 0, h)][lim(j+k, 0, w)];
                        kernelSum += (*grid)[lim(i-ik, 0, h)][lim(j+k, 0, w)];
                        kernelSum += (*grid)[lim(i+ik, 0, h)][lim(j-k, 0, w)];
                        kernelSum += (*grid)[lim(i-ik, 0, h)][lim(j-k, 0, w)];
                    }
                }

                (*grid)[i][j] = kernelSum / size_t(pow(2*_radius + 1, 2) + math<>::eps);
            }
        }
    }

    normalizeHeights(grid);

}

float SmoothMaskDecorator::findMax(std::shared_ptr<Grid> grid)
{
    float maxValue = 0.f;

    for (size_t i = 0; i < grid->height(); ++i)
    {
        for (size_t j = 0; j < grid->width(); ++j)
        {
            if ((*grid)[i][j] > maxValue)
                maxValue = (*grid)[i][j];
        }
    }

    return maxValue;
}

void SmoothMaskDecorator::normalizeHeights(std::shared_ptr<Grid> grid)
{
    float maxHeight = findMax(grid);

    for (size_t i = 0; i < grid->height(); ++i)
    {
        for (size_t j = 0; j < grid->width(); ++j)
            (*grid)[i][j] = (*grid)[i][j] / maxHeight;
    }
}
