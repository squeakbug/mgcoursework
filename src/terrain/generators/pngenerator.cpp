#include <vector>
#include <iostream>

#include "terrain/generators/pngenerator.h"

PNGenerator::PNGenerator()
    : _octaves_cnt(1)
{

}


PNGenerator::PNGenerator(size_t octaves_cnt)
    : _octaves_cnt(octaves_cnt)
{

}


std::shared_ptr<Grid> PNGenerator::generate(size_t height, size_t width)
{
    std::shared_ptr<Grid> output(new Grid(height, width));
    std::vector<std::vector<vec2<>>> grid = getVectorgrid(height, width, gridSize, defaultVecsCnt);

    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            // Linear interpolation
            vec2<> luVec = { float(j % gridSize), -float(i % gridSize) };
            luVec = math<>::normalize(luVec);
            vec2<> ruVec = { -float(gridSize - j % gridSize), -float(i % gridSize) };
            ruVec = math<>::normalize(ruVec);

            float a = math<>::dot(luVec, grid[i / gridSize][j / gridSize]);
            float b = math<>::dot(ruVec, grid[i / gridSize][j / gridSize + 1]);
            float t = float(j % gridSize) / gridSize;

            float up = a * (1.f - t) + b * t;

            // Linear interpolation
            vec2<> ldVec = { float(j % gridSize), float(gridSize - i % gridSize) };
            ldVec = math<>::normalize(ldVec);
            vec2<> rdVec = { -float(gridSize - j % gridSize), float(gridSize - i % gridSize) };
            rdVec = math<>::normalize(rdVec);

            float c = math<>::dot(ldVec, grid[i / gridSize + 1][j / gridSize]);
            float d = math<>::dot(rdVec, grid[i / gridSize + 1][j / gridSize + 1]);
            float s = float(j % gridSize) / gridSize;

            float down = c * (1.f - s) + d * s;

            float v = float(i % gridSize) / gridSize;

            float res = up * (1.f - v) + down * v;

            (*output)[i][j] = res;
        }
    }

    normalizeHeights(output);

    return output;
}


void PNGenerator::set_octaves_cnt(size_t octaves_cnt)
{
    _octaves_cnt = octaves_cnt;
}

void PNGenerator::normalizeHeights(std::shared_ptr<Grid> grid)
{
    size_t width = grid->width();

    for (size_t i = 0; i < grid->height(); ++i)
    {
        for (size_t j = 0; j < width; ++j)
            (*grid)[i][j] = ((*grid)[i][j] + 1.f) / 2.f;
    }
}

std::vector<vec2<>> PNGenerator::genVectors(size_t cnt)
{
    if (cnt <= 0)
        cnt = defaultVecsCnt;

    std::vector<vec2<>> output;
    float angle = 360.f / cnt;
    float curAngle = 0.f;

    for (size_t i = 0; i < cnt; ++i)
    {
        output.push_back(vec2<>(cos(curAngle * math<>::DEG2RAD), sin(curAngle * math<>::DEG2RAD)));
        curAngle += angle;
    }

    return output;
}

std::vector<std::vector<vec2<>>> PNGenerator::getVectorgrid(size_t height, size_t width, size_t gridSize, size_t vecsCnt)
{
    std::vector<vec2<>> ndcVecs = genVectors(vecsCnt);
    std::vector<std::vector<vec2<>>> grid;
    int gridWidth = width / gridSize + 1;
    int gridHeight = height / gridSize + 1;

    grid.resize(gridHeight);
    for (int i = 0; i < gridHeight; ++i)
        grid[i].resize(gridWidth);

    srand((unsigned int)time(NULL));
    for (int i = 0; i < gridHeight; ++i)
    {
        for (int j = 0; j < gridWidth; j++)
            grid[i][j] = ndcVecs[rand() % vecsCnt];
    }

    return grid;
}
