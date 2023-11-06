#ifndef IPROCEDURAL_LIGHTMAPPING_H
#define IPROCEDURAL_LIGHTMAPPING_H

#include "lightmap/lightmap_generator.h"

class IProceduralLightmapping
{
public:
    virtual ~IProceduralLightmapping() = 0;

    virtual void accept(LightmapGenerator &generator) = 0;
};

#endif