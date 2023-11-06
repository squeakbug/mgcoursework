#include <random>

#include "terrain/generators/dsgenerator.h"

DSGenerator::DSGenerator()
{
    _roughness = 0.5f;
    for (int i = 0; i < 4; ++i)
        _heights[i] = 0.f;
    _delta = 0.f;
    _type = SurfaceType::Random;
}


DSGenerator::DSGenerator(float roughness, float delta, SurfaceType type, const CornerHeights &heights)
{
    _roughness = roughness;
    set_height(heights);
    _delta = delta;
    _type = type;
}

void DSGenerator::dsSubroutine(std::shared_ptr<Grid> grid, size_t x1, size_t y1, size_t x2, size_t y2, float delta, size_t level)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(0.f, delta);

    if (level < 1)
        return;

    for (size_t i = x1 + level; i < x2; i += level)
    {
        for (size_t j = y1 + level; j < y2; j += level)
        {
            float a = (*grid)[i - level][j - level];
            float b = (*grid)[i][j - level];
            float c = (*grid)[i - level][j];
            float d = (*grid)[i][j];

            (*grid)[i - level / 2][j - level / 2] = (a + b + c + d) / 4 + dist(mt);
        }
    }

    for (unsigned i = x1 + 2 * level; i < x2; i += level)
    {
        for (unsigned j = y1 + 2 * level; j < y2; j += level)
        {
            float a = (*grid)[i - level][j - level];
            float b = (*grid)[i][j - level];
            float c = (*grid)[i - level][j];
            float e = (*grid)[i - level / 2][j - level / 2];

            (*grid)[i - level][j - level / 2] = (a + c + e + (*grid)[i - 3 * level / 2][j - level / 2]) / 4 + dist(mt);
            (*grid)[i - level / 2][j - level] = (a + b + e + (*grid)[i - level / 2][j - 3 * level / 2]) / 4 + dist(mt);
        }
    }

    dsSubroutine(grid, x1, y1, x2, y2, delta * _roughness, level / 2);
}

std::shared_ptr<Grid> DSGenerator::generate(size_t height, size_t width)
{
    std::shared_ptr<Grid> grid(new Grid(height, width));

    (*grid)[0][0] = _heights[0];
    (*grid)[0][width-1] = _heights[1];
    (*grid)[height-1][width-1] = _heights[2];
    (*grid)[height-1][0] = _heights[3];

    dsSubroutine(grid, 0, 0, width, height, _delta, std::min(height, width)-1);

    return grid;
}


void DSGenerator::set_height(const CornerHeights &heights)
{
    _heights[0] = heights.leftUp;
    _heights[1] = heights.rightUp;
    _heights[2] = heights.rightDown;
    _heights[3] = heights.leftDown;
}


void DSGenerator::set_roughness(float roughness)
{
    _roughness = roughness;
}


void DSGenerator::set_type(SurfaceType type)
{
    _type = type;
}

void DSGenerator::normalizeHeights(std::shared_ptr<Grid> grid)
{
    size_t width = grid->width();

    for (size_t i = 0; i < grid->height(); ++i)
    {
        for (size_t j = 0; j < width; ++j)
        {
            (*grid)[i][j] = (*grid)[i][j];
        }
    }
}

