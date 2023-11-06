#ifndef INCLINED_PLANE_GENERATOR_H
#define INCLINED_PLANE_GENERATOR_H

#include "terrain/grid_generator.h"
#include "math/math.h"

using std::size_t;

class InclinedPlaneGenerator : public GridGenerator
{
public:
    InclinedPlaneGenerator(float A = 1.f, float B = 1.f, float C = 1.f, float D = 0.f)
    {
        _A = A;
        _B = B;
        _C = C;
        _D = D;
    }

    std::shared_ptr<Grid> generate(size_t height, size_t width) override
    {
        std::shared_ptr<Grid> grid(new Grid(height, width));

        for (size_t i = 0; i < height; i++)
        {
            for (size_t j = 0; j < width; j++)
                (*grid)[i][j] = math<>::clamp((-_A*j - _B*i - _D) / _C, 0.f, 1.f);
        }

        return grid;
    }

private:
    float _A;
    float _B;
    float _C;
    float _D;
};

#endif
