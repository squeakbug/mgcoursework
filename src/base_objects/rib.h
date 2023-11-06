#ifndef RIB_H
#define RIB_H

#include <cstddef>

using std::size_t;

class Rib
{
public:
    Rib();
    Rib(size_t i1, size_t i2);
    Rib(const Rib &r);
    Rib(Rib &&r);

    Rib& operator=(const Rib &r);
    Rib& operator=(Rib &&r);

public:
    size_t indx1;
    size_t indx2;
};

#endif // RIB_H
