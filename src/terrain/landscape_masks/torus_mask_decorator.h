#ifndef TORUS_MASK_DECORATOR_H
#define TORUS_MASK_DECORATOR_H

#include <memory>

#include "terrain/landscape_masks/default_landscape_mask.h"
#include "terrain/ilandscape_mask.h"

class TorusMaskDecorator : public ILandscapeMask
{
public:
    TorusMaskDecorator(std::shared_ptr<ILandscapeMask> wrappee);

    virtual void updateTerrain(std::shared_ptr<Grid> grid) override;

private:
    std::shared_ptr<ILandscapeMask> _wrappee;
};

#endif