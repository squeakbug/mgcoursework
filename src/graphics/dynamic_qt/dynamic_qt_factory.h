#ifndef DYNAMIC_QT_FACTORY_H
#define DYNAMIC_QT_FACTORY_H

#include <memory>

#include "dynamic_qt_drawer.h"
#include "graphics/graphicsfactory.h"

class DynamicQtFactory : public GraphicsFactory
{
public:
    DynamicQtFactory();

    virtual std::shared_ptr<BaseDrawer> create_graphics(size_t width, size_t height) override;
};

#endif