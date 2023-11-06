#include "z_buffer.h"

#include <limits>

ZBuffer::ZBuffer(std::size_t height, std::size_t width)
{
    _height = height;
    _width = width;

    double *_data = new double[width * height];
    _pointers = new double * [height];
    for (std::size_t row = 0; row < height; ++row)
         _pointers[row] = (double*)((char*)_data + sizeof(double) * width * row);

    for (size_t i = 0; i < _height; ++i)
    {
        for (size_t j = 0; j < _width; ++j)
            _pointers[i][j] = std::numeric_limits<double>::max();
    }
}

ZBuffer::ZBuffer(const ZBuffer &other)
{
    _width = other._width;
    _height = other._height;

    double *_data = new double[_width * _height];
    _pointers = new double * [_height];
    for (std::size_t row = 0; row < _height; ++row)
         _pointers[row] = (double*)((char*)_data + sizeof(double) * _width * row);

    for (size_t i = 0; i < _height; ++i)
    {
        for (size_t j = 0; j < _width; ++j)
            _pointers[i][j] = other[i][j];
    }
}

ZBuffer::~ZBuffer()
{
    delete [] _pointers[0];
    delete [] _pointers;
}

void ZBuffer::clearBuffer()
{
    double mx = std::numeric_limits<double>::max();
    
    for (size_t i = 0; i < _height; ++i)
    {
        for (size_t j = 0; j < _width; ++j)
            _pointers[i][j] = mx;
    }
}

ZBuffer &ZBuffer::operator=(ZBuffer &&other)
{
    _height = other._height;
    _width = other._width;
    _pointers = other._pointers;
    other._pointers = nullptr;
    return *this;
}

const double* ZBuffer::operator[](std::size_t indx) const
{
    return _pointers[indx];
}

double* ZBuffer::operator[](std::size_t indx)
{
    return _pointers[indx];
}

std::size_t ZBuffer::width() const
{
    return _width;
}

std::size_t ZBuffer::height() const
{
    return _height;
}

double **ZBuffer::data()
{
    return _pointers;
}
