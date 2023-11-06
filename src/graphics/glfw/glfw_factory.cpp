#include "glfw_factory.h"

static const vec3<> defaultBackgroundColor = vec3<>(0.f, 0.f, 0.f);

GLFWFactory::GLFWFactory()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false);
}

GLFWFactory::~GLFWFactory()
{
    glfwTerminate();
}

std::shared_ptr<BaseDrawer> GLFWFactory::create_graphics(size_t width, size_t height)
{
    return std::shared_ptr<BaseDrawer>(new GLFWDrawer(height, width, defaultBackgroundColor));
}