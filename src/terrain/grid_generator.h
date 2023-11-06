#ifndef GRID_GENERATOR_H
#define GRID_GENERATOR_H

#include <memory>

#include "terrain/grid.h"

struct CornerHeights
{
    float leftUp;
    float leftDown;
    float rightUp;
    float rightDown;
};

class GridGenerator
{
public:
    virtual ~GridGenerator() = 0;

    virtual std::shared_ptr<Grid> generate(std::size_t height, std::size_t width) = 0;

protected:
    void find_minmax(std::shared_ptr<Grid> grid, float &minv, float &maxv);
    float fRandom(float range);
};

#endif // GRID_GENERATOR_H
