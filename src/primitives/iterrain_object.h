#ifndef ITERRAIN_OBJECT_H
#define ITERRAIN_OBJECT_H

#include <memory>

class ITerrainObject
{
public:
    virtual ~ITerrainObject() = 0;

    virtual void updateTerrainValues() = 0;
};

#endif