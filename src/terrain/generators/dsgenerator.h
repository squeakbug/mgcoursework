#ifndef DSGENERATOR_H
#define DSGENERATOR_H

#include "terrain/grid_generator.h"

using std::size_t;

enum class SurfaceType
{
    Atol, Island, Random
};

class DSGenerator : public GridGenerator
{
public:
    DSGenerator();
    DSGenerator(float roughness, float delta, SurfaceType type, const CornerHeights &heights);

    virtual std::shared_ptr<Grid> generate(size_t height, size_t width) override;

    void set_height(const CornerHeights &heights);
    void set_roughness(float roughness);
    void set_type(SurfaceType type);

private:
    void normalizeHeights(std::shared_ptr<Grid> grid);
    void dsSubroutine(std::shared_ptr<Grid> grid, size_t x1, size_t y1, size_t x2, size_t y2, float delta, size_t level);

private:
    float _roughness;        // [0..1]
    float _heights[4];       // Four corners'
    float _delta;            // Start delta
    SurfaceType _type;       // Landscape type
};

#endif // DSGENERATOR_H
