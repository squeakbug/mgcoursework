#ifndef SPNGENERATOR_H
#define SPNGENERATOR_H

#include <map>

#include "terrain/grid_generator.h"
#include "math/math.h"
#include "base_objects/vector2f.h"

using std::size_t;

class SPNGenerator : public GridGenerator
{
public:
    SPNGenerator(size_t octavesCnt=1, bool unbias=false);

    virtual std::shared_ptr<Grid> generate(size_t height, size_t width) override;

    void set_octaves_cnt(size_t octaves_cnt);

private:
    void normalizeHeights(std::shared_ptr<Grid> grid);
    vec2<> generateGradient();
    float genPoint(float x, float y);
    float get_plain_noise(const vec2<> &vec);

private:
    size_t _tileWidth, _tileHeight;
    bool _unbias;
    size_t _octavesCnt;
    float _scaleFactor;

    std::map<std::pair<size_t, size_t>, vec2<>> _gradients;
};

#endif
