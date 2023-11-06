#include "qt_factory.h"

static const vec3<> defaultBackgroundColor = vec3<>(0.3, 0.3, 0.6);

QtFactory::QtFactory(QGraphicsScene *s)
    : scene(s)
{

}

std::shared_ptr<BaseDrawer> QtFactory::create_graphics(size_t width, size_t height)
{
    return std::shared_ptr<BaseDrawer>(new QtDrawer(scene, width, height, defaultBackgroundColor));
}
