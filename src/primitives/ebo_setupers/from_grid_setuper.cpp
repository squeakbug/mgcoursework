#include "from_grid_setuper.h"

using std::size_t;

FromGridSetuper::FromGridSetuper(std::size_t width, std::size_t height)
{
    _width = width;
    _height = height;
}

void FromGridSetuper::setupEBO(std::vector<std::size_t> &ebo)
{
    /* 6 - два треугольника (3 вершины * 2 треугольника в квадрате) */
    ebo.reserve((_height - 1) * (_width - 1) * 6);

    for (size_t i = 0; i < _height - 1; i++)
    {
        for (size_t j = 0; j < _width - 1; j++)
        {
            /* Первый треугольник */
            ebo.push_back(j + _width * i);
            ebo.push_back(j + _width * i + 1);
            ebo.push_back(j + _width * (i+1));

            /* Второй треугольник */
            ebo.push_back(j + _width * (i+1));
            ebo.push_back(j + _width * (i+1) + 1);
            ebo.push_back(j + _width * i + 1);
        }
    }
}