#ifndef Z_BUFFER_H
#define Z_BUFFER_H

#include <cstddef>

class ZBuffer
{
public:
    ZBuffer(std::size_t height, std::size_t width);
    ZBuffer(const ZBuffer &other);
    ~ZBuffer();

    void clearBuffer();

    ZBuffer &operator=(ZBuffer &&other);

    const double* operator[](std::size_t indx) const;
    double* operator[](std::size_t indx);

    std::size_t width() const;
    std::size_t height() const;

    double **data();

private:
    std::size_t _width, _height;
    double **_pointers;
};

#endif // Z_BUFFER_H
