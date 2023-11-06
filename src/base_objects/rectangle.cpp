#include "rectangle.h"

Rectangle::Rectangle()
{
    x = 0;
    y = 0;
    width = 0;
    height = 0;
}

Rectangle::Rectangle(size_t _x, size_t _y, size_t _width, size_t _height)
{
    x = _x;
    y = _y;
    width = _width;
    height = _height;
}