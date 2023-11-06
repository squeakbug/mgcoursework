#ifndef GRID_H
#define GRID_H

#include <cstddef>
#include <cstring>

#include "errors/logicexceptions.h"

using std::size_t;

class Grid
{
    class Row
    {
    public:
        Row(float *_start, size_t width);

        float &operator[](size_t indx);

    private:
        size_t _width;
        float *_start;
    };

public:
    Grid();
    Grid(size_t height, size_t width, float defaultHeight = 0.f);
    Grid(const Grid &other);
    Grid(Grid &&other);
    ~Grid();

    size_t width() const;
    size_t height() const;
    const float *data() const;
    float *data();

    Row operator[](size_t indx);
    Grid &operator=(const Grid &other);
    Grid &operator=(Grid &&other);

    void normalize_heights(float min1, float max1, float min2, float max2);

private:
    size_t _height;
    size_t _width;
    float *_heights;
};

#endif // GRID_H
