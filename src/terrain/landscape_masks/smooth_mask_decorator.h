#ifndef SMOOTH_MASK_DECORATOR_H
#define SMOOTH_MASK_DECORATOR_H

#include <memory>

#include "terrain/landscape_masks/default_landscape_mask.h"
#include "terrain/ilandscape_mask.h"

class SmoothMaskDecorator : public ILandscapeMask
{
public:
    SmoothMaskDecorator(std::shared_ptr<ILandscapeMask> wrappee, size_t radius, size_t repeatCnt);

    virtual void updateTerrain(std::shared_ptr<Grid> grid) override;

private:
    float findMax(std::shared_ptr<Grid> grid);
    void normalizeHeights(std::shared_ptr<Grid> grid);

private:
    std::shared_ptr<ILandscapeMask> _wrappee;
    size_t _radius;
    size_t _repeatCnt;
};

#endif