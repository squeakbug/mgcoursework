#ifndef GRAPHICSFACTORY_H
#define GRAPHICSFACTORY_H

#include <memory>

#include "base_drawer.h"

class GraphicsFactory
{
public:
    virtual ~GraphicsFactory() = 0;

    virtual std::shared_ptr<BaseDrawer> create_graphics(size_t width, size_t height) = 0;
};

#endif // GRAPHICSFACTORY_H
