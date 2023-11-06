#ifndef BASE_PAINTER_H
#define BASE_PAINTER_H

class TerrainPolygonModel;

class BasePainter
{
public:
    virtual ~BasePainter() = 0;

    virtual void paint(TerrainPolygonModel &block) = 0;
};

#endif