#ifndef MDSGENERATOR_H
#define MDSGENERATOR_H

#include <random>
#include <memory>

#include "terrain/grid_generator.h"

using std::size_t;

class MDSGenerator : public GridGenerator
{
public:
    MDSGenerator();
    MDSGenerator(float roughness, float delta, const CornerHeights &heights);

    virtual std::shared_ptr<Grid> generate(size_t height, size_t width) override;

    void set_height(const CornerHeights &heights);
    void set_roughness(float roughness);
    void set_delta(float delta);

private:
    void normalizeHeights(std::shared_ptr<Grid> grid);
    void sub_generate(std::shared_ptr<Grid> grid, float delta,
        size_t lx, size_t ly, size_t h, size_t w,
        float v1, float v2, float v3, float v4);

private:
    float _roughness;        // [0..1]
    float _heights[4];       // Four corners'
    float _delta;            // Start delta
};

#endif // MDSGENERATOR_H
