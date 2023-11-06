#ifndef DEFAULT_GENERATOR_H
#define DEFAULT_GENERATOR_H

#include "terrain/grid_generator.h"

using std::size_t;

class DefaultGenerator : public GridGenerator
{
public:
    std::shared_ptr<Grid> generate(size_t height, size_t width) override
    {
        return std::shared_ptr<Grid>(new Grid(height, width, defaultHeight));
    }

private:
    static constexpr float defaultHeight = 100.f;
};

#endif
