#ifndef GLFW_FACTORY_H
#define GLFW_FACTORY_H

#include <memory>

#include "graphics/glfw/glfw_drawer.h"
#include "graphics/graphicsfactory.h"

class GLFWFactory : public GraphicsFactory
{
public:
    GLFWFactory();
    ~GLFWFactory();

    virtual std::shared_ptr<BaseDrawer> create_graphics(size_t width, size_t height) override;
};

#endif