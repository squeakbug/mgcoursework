#ifndef GLFW_DRAWER_H
#define GLFW_DRAWER_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <cstddef>

#include "frame_buffers/frame_buffer.h"
#include "frame_buffers/z_buffer.h"
#include "graphics/base_drawer.h"
#include "math/math.h"

enum class GLObjectType
{
    Vertex,
    Fragment,
    ShaderProgram
};

class GLFWDrawer : public BaseDrawer
{
public:
    GLFWDrawer(size_t height, size_t width, vec3<> backgroundColor);
    ~GLFWDrawer();

    void initScene() override;
    void resizeScene(size_t newHeight, size_t newWidth) override;
    void swapBuffers() override;
    void terminateScene() override;

    void enableZBuffering() override;
    void disableZBuffering() override;
    void clearFrameBuffer() override;
    void clearZBuffer() override;

private:
    GLFWDrawer(const GLFWDrawer &drawer) = delete;
    GLFWDrawer &operator=(const GLFWDrawer &drawer) = delete;

    void prepareShaderProgram();
    void checkCompileErrors(unsigned int shader, GLObjectType type);
    void processInput();

    uint8_t* getFrameBufferDataInBytes();

private:
    GLuint _shaderProgramID;
    GLFWwindow* _window;
    bool _isGLFWWindowCreated;
};

#endif