#ifndef PNGENERATOR_H
#define PNGENERATOR_H

#include "terrain/grid_generator.h"
#include "math/math.h"
#include "base_objects/vector2f.h"

using std::size_t;

class PNGenerator : public GridGenerator
{
public:
    PNGenerator();
    PNGenerator(size_t octaves_cnt);

    virtual std::shared_ptr<Grid> generate(size_t height, size_t width) override;

    void set_octaves_cnt(size_t octaves_cnt);

private:
    std::vector<vec2<>> genVectors(size_t cnt);
    std::vector<std::vector<vec2<>>> getVectorgrid(size_t height, size_t width, size_t gridSize, size_t vecsCnt);
    void normalizeHeights(std::shared_ptr<Grid> grid);

private:
    static const size_t defaultVecsCnt = 256;
    static const size_t defaultGridSize = 4;

    size_t _octaves_cnt;
    
    size_t gridSize { defaultGridSize };
};

#endif // PNGENERATOR_H
