#ifndef DEFAULT_LANDSCAPE_MASK_H
#define DEFAULT_LANDSCAPE_MASK_H

#include <memory>

#include "terrain/ilandscape_mask.h"

class DefaultLandscapeMask : public ILandscapeMask
{
public:
    virtual void updateTerrain(std::shared_ptr<Grid> grid) override;
};

#endif