#include "frame_buffer.h"

#include <limits>

static const vec3<> _defaultClearColor = { 0.f, 0.f, 0.f };

FrameBuffer::FrameBuffer(std::size_t height, std::size_t width)
    : FrameBuffer(height, width, _defaultClearColor)
{
    
}

FrameBuffer::FrameBuffer(std::size_t height, std::size_t width, const vec3<> &clearColor)
{
    _height = height;
    _width = width;
    _clearColor = clearColor;

    vec3<> *_data = new vec3<>[width * height];
    _pointers = new vec3<> * [height];
    for (std::size_t row = 0; row < height; ++row)
         _pointers[row] = (vec3<>*)((char*)_data + sizeof(vec3<>) * width * row);

    for (size_t i = 0; i < _height; ++i)
    {
        for (size_t j = 0; j < _width; ++j)
            _pointers[i][j] = _clearColor;
    }
}

FrameBuffer::~FrameBuffer()
{
    delete [] _pointers[0];
    delete [] _pointers;
}

void FrameBuffer::setClearColor(const vec3<> &clearColor)
{
    _clearColor = clearColor;
}

#include <iostream>

void FrameBuffer::clearBuffer()
{
    for (size_t i = 0; i < _height; ++i)
    {
        for (size_t j = 0; j < _width; ++j)
            _pointers[i][j] = _clearColor;
    }
}

FrameBuffer &FrameBuffer::operator=(FrameBuffer &&other)
{
    _width = other._width;
    _height = other._height;
    _clearColor = other._clearColor;
    _pointers = other._pointers;
    other._pointers = nullptr;
    return *this;
}

const vec3<>* FrameBuffer::operator[](std::size_t indx) const
{
    return _pointers[indx];
}

vec3<>* FrameBuffer::operator[](std::size_t indx)
{
    return _pointers[indx];
}

std::size_t FrameBuffer::height() const
{
    return _height;
}

std::size_t FrameBuffer::width() const
{
    return _width;
}

vec3<> FrameBuffer::getClearColor() const
{
    return _clearColor;
}

vec3<> *FrameBuffer::data()
{
    return _pointers[0];
}

const vec3<> *FrameBuffer::data() const
{
    return _pointers[0];
}