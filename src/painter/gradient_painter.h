#ifndef GRADIENT_PAINTER_H
#define GRADIENT_PAINTER_H

#include <memory>

#include "painter/base_painter.h"
#include "painter/gradient.h"

class GradientPainter : public BasePainter
{
public:
    void paint(TerrainPolygonModel &block) override;

    void setGradient(std::shared_ptr<Gradient> gradient);

private:
    std::shared_ptr<Gradient> _gradient;
};

#endif