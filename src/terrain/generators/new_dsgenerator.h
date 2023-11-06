#ifndef NEW_DSGENERATOR_H
#define NEW_DSGENERATOR_H

#include "terrain/grid_generator.h"

using std::size_t;

class NewDSGenerator : public GridGenerator
{
public:
    NewDSGenerator();
    NewDSGenerator(float roughness, float delta, const CornerHeights &heights);

    virtual std::shared_ptr<Grid> generate(size_t height, size_t width) override;

    void set_height(const CornerHeights &heights);
    void set_roughness(float roughness);

private:
    void diamondStep(std::shared_ptr<Grid> grid, int x, int z, size_t reach, float delta);
    void squareStep(std::shared_ptr<Grid> grid, int x, int z, size_t reach, float delta);
    void normalizeHeights(std::shared_ptr<Grid> grid);
    void dsSubroutine(std::shared_ptr<Grid> grid, float delta, size_t level);

private:
    float _roughness;        // [0..1]
    float _heights[4];       // Four corners'
    float _delta;            // Start delta
};

#endif 
