#include <random>

#include "terrain/grid_generator.h"

GridGenerator::~GridGenerator()
{

}

void GridGenerator::find_minmax(std::shared_ptr<Grid> grid, float &minv, float &maxv)
{
    minv = maxv = (*grid)[0][0];

    for (size_t i = 0; i < grid->height(); ++i)
    {
        for (size_t j = 0; j < grid->width(); ++j)
        {
            if ((*grid)[i][j] > maxv)
                maxv = (*grid)[i][j];
            else if ((*grid)[i][j] < minv)
                minv = (*grid)[i][j];
        }
    }
}

float GridGenerator::fRandom(float range)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(-range, range);

    return dist(mt);
}
