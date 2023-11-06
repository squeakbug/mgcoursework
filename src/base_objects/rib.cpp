#include "rib.h"

Rib::Rib()
{

}


Rib::Rib(size_t i1, size_t i2)
{
    indx1 = i1;
    indx2 = i2;
}


Rib::Rib(const Rib &r)
{
    indx1 = r.indx1;
    indx2 = r.indx2;
}


Rib::Rib(Rib &&r)
{
    indx1 = r.indx1;
    indx2 = r.indx2;
}


Rib &Rib::operator=(const Rib &r)
{
    indx1 = r.indx1;
    indx2 = r.indx2;

    return *this;
}


Rib &Rib::operator=(Rib &&r)
{
    indx1 = r.indx1;
    indx2 = r.indx2;

    return *this;
}
