#ifndef DEFAULT_PAINTER_H
#define DEFAULT_PAINTER_H

#include "painter/base_painter.h"

class DefaultPainter : public BasePainter
{
public:
    void paint(TerrainPolygonModel &block) override;
};

#endif