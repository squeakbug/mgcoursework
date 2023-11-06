#include "terrain/grid.h"

Grid::Grid() :
    _height(0),
    _width(0),
    _heights(nullptr)
{

}


Grid::Grid(const Grid &other) :
    _height(other._height),
    _width(other._width)
{
    _heights = new float[_height * _width];
    memcpy(_heights, other._heights, sizeof(float) * _height * _width);
}


Grid::Grid(Grid &&other) :
    _height(other._height),
    _width(other._width)
{
    _heights = other._heights;
    other._heights = nullptr;
}

Grid::~Grid()
{
    delete [] _heights;
}


Grid::Grid(size_t height, size_t width, float defaultHeight) :
    _height(height),
    _width(width)
{
    _heights = new float[height * width];

    for (size_t i = 0; i < height * width; ++i)
        _heights[i] = defaultHeight;
}


size_t Grid::width() const
{
    return _width;
}


size_t Grid::height() const
{
    return _height;
}

const float *Grid::data() const
{
    return _heights;
}

float *Grid::data()
{
    return _heights;
}

Grid::Row Grid::operator[](std::size_t indx)
{
    if (indx >= _height)
    {
        throw LogicException(__FILE__, typeid(*this).name(),
                             __LINE__, "Выход на границы массива\n");
    }
    float *start_indx = _heights + indx * _width;

    return Row(start_indx, _width);
}

Grid &Grid::operator=(const Grid &other)
{
    _height = other._height;
    _width = other._width;
    _heights = new float[_height * _width];
    memcpy(_heights, other._heights, sizeof(float) * _height * _width);

    return *this;
}

Grid &Grid::operator=(Grid &&other)
{
    _height = other._height;
    _width = other._width;
    _heights = other._heights;
    other._heights = nullptr;

    return *this;
}


void Grid::normalize_heights(float min1, float max1, float min2, float max2)
{
    for (size_t i = 0; i < _height; ++i)
    {
        for (size_t j = 0; j < _width; ++j)
            _heights[j + i * _width] = (_heights[j + i * _width] - min1) / max1 * max2 + min2;
    }
}

/* ============= Grid::Row ============= */

Grid::Row::Row(float *start, std::size_t width)
{
    _start = start;
    _width = width;
}


float &Grid::Row::operator[](std::size_t indx)
{
    if (indx >= _width)
    {
        throw LogicException(__FILE__, typeid(*this).name(),
                             __LINE__, "Выход на границы массива\n");
    }

    return _start[indx];
}
