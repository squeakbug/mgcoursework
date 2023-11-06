#ifndef ILANDSCAPE_MASK_H
#define ILANDSCAPE_MASK_H

#include <memory>

class Grid;

class ILandscapeMask
{
public:
    virtual ~ILandscapeMask() = 0;

    virtual void updateTerrain(std::shared_ptr<Grid> grid) = 0;
};

#endif