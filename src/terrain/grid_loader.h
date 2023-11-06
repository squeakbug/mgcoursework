#ifndef GRID_LOADER_H
#define GRID_LOADER_H

#include <memory>

#include "terrain/grid.h"
#include "base_objects/rectangle.h"

class GridLoader
{
public:
    virtual ~GridLoader() = 0;

    virtual std::shared_ptr<Grid> getGrid() = 0;
};

#endif