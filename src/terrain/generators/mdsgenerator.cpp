#include <memory>

#include "terrain/generators/mdsgenerator.h"
#include "math/math.h"

static const size_t maxGridSize = 2048;
static const size_t minGridSize = 2;

MDSGenerator::MDSGenerator()
{
    _roughness = 0.5;
    for (int i = 0; i < 4; ++i)
        _heights[i] = 0.f;
    _delta = 0.f;
}

MDSGenerator::MDSGenerator(float roughness, float delta, const CornerHeights &heights)
{
    _roughness = roughness;
    _heights[0] = heights.leftUp;
    _heights[1] = heights.rightUp;
    _heights[2] = heights.rightDown;
    _heights[3] = heights.leftDown;
    _delta = delta;
}

#include <iostream>

void MDSGenerator::sub_generate(std::shared_ptr<Grid> grid, float delta,
    size_t x, size_t y, size_t h, size_t w,
    float v1, float v2, float v3, float v4)
{
    size_t halfW = w / 2;
    size_t halfH = h / 2;

    if (h > 1 && w > 1)
    {
        float mid = (v1 + v2 + v3 + v4) / 4 + fRandom(delta / _roughness);

        float top_mid = (v1 + v2) / 2 + fRandom(delta);
        float right_mid = (v2 + v3) / 2 + fRandom(delta);
        float bottom_mid = (v3 + v4) / 2 + fRandom(delta);
        float left_mid = (v4 + v1) / 2 + fRandom(delta);

        sub_generate(grid, delta * _roughness, x, y, halfH, halfW, v1, top_mid, mid, left_mid);
        sub_generate(grid, delta * _roughness, x + halfW, y, halfH, w - halfW, top_mid, v2, right_mid, mid);
        sub_generate(grid, delta * _roughness, x, y + halfH, h - halfH, halfW, mid, right_mid, v3, bottom_mid);
        sub_generate(grid, delta * _roughness, x + halfW, y + halfH, h - halfH, w - halfW, left_mid, mid, bottom_mid, v4);
    }
    else
    {
        float mid = (v1 + v2 + v3 + v4) / 4 + fRandom(delta / _roughness);
        (*grid)[x][y] = mid;
    }
}

std::shared_ptr<Grid> MDSGenerator::generate(std::size_t height, std::size_t width)
{
    if (height < minGridSize || width < minGridSize || height > maxGridSize || width > maxGridSize)
    {
        throw BadArgsToGridGeneratorException(__FILE__, typeid(*this).name(), __LINE__,
            "Программа не поддерживает генерацию матриц высот таких размеров");
    }

    std::shared_ptr<Grid> grid(new Grid(height, width));

    (*grid)[0][0] = _heights[0];
    (*grid)[0][width-1] = _heights[1];
    (*grid)[height-1][width-1] = _heights[2];
    (*grid)[height-1][0] = _heights[3];

    sub_generate(grid, _delta, 0, 0, height, width, _heights[0], _heights[3], _heights[1], _heights[2]);
    normalizeHeights(grid);

    return grid;
}

void MDSGenerator::set_height(const CornerHeights &heights)
{
    _heights[0] = heights.leftUp;
    _heights[1] = heights.rightUp;
    _heights[2] = heights.rightDown;
    _heights[3] = heights.leftDown;
}

void MDSGenerator::set_roughness(float roughness)
{
    _roughness = roughness;
}

void MDSGenerator::set_delta(float delta)
{
    _delta = delta;
}

void MDSGenerator::normalizeHeights(std::shared_ptr<Grid> grid)
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
