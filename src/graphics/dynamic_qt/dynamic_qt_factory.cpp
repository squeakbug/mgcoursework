#include "dynamic_qt_factory.h"

static const vec3<> defaultBackgroundColor = vec3<>(0.3, 0.3, 0.6);

DynamicQtFactory::DynamicQtFactory()
{

}

std::shared_ptr<BaseDrawer> DynamicQtFactory::create_graphics(size_t width, size_t height)
{
    return std::shared_ptr<BaseDrawer>(new DynamicQtDrawer(height, width, defaultBackgroundColor));
}