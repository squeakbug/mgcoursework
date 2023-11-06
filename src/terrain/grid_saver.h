#ifndef GRID_SAVER_H
#define GRID_SAVER_H

#include "terrain/grid.h"
#include "base_objects/rectangle.h"

class GridSaver
{
public:
    virtual ~GridSaver() = 0;

    virtual void save_grid(const Grid &grid, Rectangle rect) = 0;
};

#endif // GRID_SAVER_H
