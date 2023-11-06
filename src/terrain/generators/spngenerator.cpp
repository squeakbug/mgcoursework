#include <vector>
#include <random>
#include <algorithm>
#include <deque>

#include "terrain/generators/spngenerator.h"

SPNGenerator::SPNGenerator(size_t octavesCnt, bool unbias)
    : _octavesCnt(octavesCnt)
{
    _scaleFactor = 2.f * pow(2.f, -0.5f);
    _unbias = unbias;
}


std::shared_ptr<Grid> SPNGenerator::generate(size_t height, size_t width)
{
    std::shared_ptr<Grid> grid(new Grid(height, width));
    _tileWidth = width * 0.2;
    _tileHeight = height * 0.2;

    for (size_t i = 0; i < height; ++i)
    {
        for (size_t j = 0; j < width; ++j)
        {
            float n = genPoint(float(j)/_tileWidth, float(i)/_tileHeight);
            (*grid)[i][j] = n;
        }
    }

    normalizeHeights(grid);    

    return grid;
}


void SPNGenerator::set_octaves_cnt(size_t octavesCnt)
{
    _octavesCnt = octavesCnt;
}

vec2<> SPNGenerator::generateGradient()
{
    static std::random_device rd;
    static std::mt19937 mt(rd());
    static std::uniform_real_distribution<float> dist(0.f, 1.f);

    vec2<> rp = { dist(mt), dist(mt) };

    float scale = pow(rp.x * rp.x + rp.y + rp.y, -0.5f);

    return rp * scale;
}

float SPNGenerator::get_plain_noise(const vec2<> &vec)
{
    std::vector<vec2<size_t>> grid_coords;
    for (int i = 0; i < 2; ++i)
    {
        size_t min_coord = std::floor(vec[i]);
        size_t max_coord = min_coord + 1;
        grid_coords.push_back(vec2<size_t>(min_coord, max_coord));
    }

    std::deque<float> dots;
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            std::pair<size_t, size_t> tmpVec { grid_coords[0][i], grid_coords[1][j] };
            if (_gradients.find(tmpVec) == _gradients.end())
                _gradients[tmpVec] = generateGradient();
            vec2<> gradient = _gradients[tmpVec];

            float dot = 0.f;
            dot += gradient[0] * (vec[0] - tmpVec.first);
            dot += gradient[1] * (vec[1] - tmpVec.second);
            dots.push_back(dot);
        }
    }

    int dim = 2;
    while (dots.size() > 1)
    {
        dim -= 1;
        float s = math<>::smoothStep(vec[dim] - grid_coords[dim][0]);

        std::deque<float> next_dots;
        while (dots.size() > 0)
        {
            float prelast = dots.front(); dots.pop_front();
            float last = dots.front(); dots.pop_front();
            next_dots.push_back(math<>::lerp(s, prelast, last));
        }

        dots = next_dots;
    }

    return dots[0] * _scaleFactor;
}

float SPNGenerator::genPoint(float x, float y)
{
    float ret = 0;
    for (size_t i = 0; i < _octavesCnt; ++i)
    {
        size_t i2 = 1 << i;
        vec2<> new_point(x, y);

        new_point.x *= i2;
        new_point.x = fmod(new_point.x, _tileWidth * i2);
        new_point.y *= i2;
        new_point.y = fmod(new_point.y, _tileHeight * i2);

        ret += get_plain_noise(new_point) / i2;
    }

    ret /= 2.f - pow(2.f, (1.f - _octavesCnt));

    return ret;
}

void SPNGenerator::normalizeHeights(std::shared_ptr<Grid> grid)
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

