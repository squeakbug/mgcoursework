#include <cmath>

#include "terrain/generators/new_dsgenerator.h"

NewDSGenerator::NewDSGenerator()
{
    _roughness = 0.5f;
    for (int i = 0; i < 4; ++i)
        _heights[i] = 0.f;
    _delta = 0.f;
}


NewDSGenerator::NewDSGenerator(float roughness, float delta, const CornerHeights &heights)
{
    _roughness = roughness;
    set_height(heights);
    _delta = delta;
}

void NewDSGenerator::diamondStep(std::shared_ptr<Grid> grid, int x, int z, size_t reach, float delta)
{
    int count = 0;
    float mid = 0.f;

    if (x >= reach)
    {
        mid += (*grid)[x-reach][z];
        count++;
    }

    if (x + reach < grid->width())
    {
        mid += (*grid)[x+reach][z];
        count++;
    }

    if (z >= reach)
    {
        mid += (*grid)[x][z-reach];
        count++;
    }

    if (z + reach < grid->height())
    {
        mid += (*grid)[x][z+reach];
        count++;
    } 
    
    mid += fRandom(delta);
    mid /= count;
    (*grid)[x][z] = mid;
}

void NewDSGenerator::squareStep(std::shared_ptr<Grid> grid, int x, int z, size_t reach, float delta)
{
    int count = 0;
    float mid = 0.f;

    if (x - reach >= 0 && z - reach >= 0)
    {
        mid += (*grid)[x-reach][z-reach];
        count++;
    }

    if (x - reach >= 0 && z + reach < grid->height())
    {
        mid += (*grid)[x-reach][z+reach];
        count++;
    }

    if (x + reach < grid->width() && z - reach >= 0)
    {
        mid += (*grid)[x+reach][z-reach];
        count++;
    }

    if (x + reach < grid->width() && z + reach < grid->height())
    {
        mid += (*grid)[x+reach][z+reach];
        count++;
    }

    mid += fRandom(delta);
    mid /= count;
    (*grid)[x][z] = mid;
}

void NewDSGenerator::dsSubroutine(std::shared_ptr<Grid> grid, float delta, size_t size)
{
    int half = size / 2;
    if (half < 1)
        return ;

    for (int y = half; y < grid->height(); y += size)
    {
        for (int x = half; x < grid->width(); x += size)
            squareStep(grid, x % grid->width(), y % grid->height(), half, delta);
    }

    int col = 0;
    for (int x = 0; x < grid->width(); x += half)
    {
        col++;
        int y = (col % 2 == 1) ? half : 0;
        for (; y < grid->height(); y += size)
            diamondStep(grid, x % grid->width(), y % grid->height(), half, delta);
    }

    dsSubroutine(grid, delta * _roughness, size / 2);
}

std::shared_ptr<Grid> NewDSGenerator::generate(size_t height, size_t width)
{
    std::shared_ptr<Grid> grid(new Grid(height, width));

    (*grid)[0][0] = _heights[0];
    (*grid)[0][width-1] = _heights[1];
    (*grid)[height-1][width-1] = _heights[2];
    (*grid)[height-1][0] = _heights[3];

    dsSubroutine(grid, _delta, std::min(height, width));

    normalizeHeights(grid);

    return grid;
}

void NewDSGenerator::set_height(const CornerHeights &heights)
{
    _heights[0] = heights.leftUp;
    _heights[1] = heights.rightUp;
    _heights[2] = heights.rightDown;
    _heights[3] = heights.leftDown;
}

void NewDSGenerator::set_roughness(float roughness)
{
    _roughness = roughness;
}

void NewDSGenerator::normalizeHeights(std::shared_ptr<Grid> grid)
{
    size_t width = grid->width();
    float minv {0.f}, maxv {0.f};
    find_minmax(grid, minv, maxv);

    for (size_t i = 0; i < grid->height(); ++i)
    {
        for (size_t j = 0; j < width; ++j)
            (*grid)[i][j] = fabs(((*grid)[i][j] - minv) / maxv);
    }
}

