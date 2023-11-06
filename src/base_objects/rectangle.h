#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <cstddef>

class Rectangle
{
public:
    Rectangle();
    Rectangle(size_t _x, size_t _y, size_t _width, size_t _height);

public:
    size_t x, y, width, height;
};

#endif // RECTANGLE_H
