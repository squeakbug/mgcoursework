#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include <cstddef>

#include "base_objects/vector3f.h"

class FrameBuffer
{
public:
    FrameBuffer(std::size_t height, std::size_t width);
    FrameBuffer(std::size_t height, std::size_t width, const vec3<> &clearColor);
    ~FrameBuffer();

    void setClearColor(const vec3<> &clr);
    void clearBuffer();

    FrameBuffer &operator=(FrameBuffer &&other);

    const vec3<>* operator[](std::size_t indx) const;
    vec3<>* operator[](std::size_t indx);

    std::size_t height() const;
    std::size_t width() const;
    vec3<> getClearColor() const;

    vec3<> *data();
    const vec3<> *data() const;

private:
    std::size_t _width, _height;
    vec3<> **_pointers;
    vec3<> _clearColor;
};

#endif // FRAME_BUFFER_H
