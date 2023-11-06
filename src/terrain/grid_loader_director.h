#ifndef GRID_LOADER_DIRECTOR_H
#define GRID_LOADER_DIRECTOR_H

#include <memory>

#include "terrain/grid.h"

class GridLoaderDirector
{
public:
    virtual ~GridLoaderDirector() = 0;

    virtual void loadGrid() = 0;
    virtual std::shared_ptr<Grid> getGrid() = 0;
};

#endif // GRID_LOADER_H
