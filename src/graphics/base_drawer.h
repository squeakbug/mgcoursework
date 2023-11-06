#ifndef BASE_DRAWER_H
#define BASE_DRAWER_H

#include <cstddef>
#include <memory>

#include "base_objects/matrix4f.h"
#include "base_objects/vertex.h"
#include "frame_buffers/frame_buffer.h"
#include "frame_buffers/z_buffer.h"
#include "shaders/fragment_shader.h"

class BaseDrawer
{
public:
    BaseDrawer(size_t height, size_t width, vec3<> backgroundColor, std::shared_ptr<FragmentShader> fragmentShader = nullptr);
    virtual ~BaseDrawer() = 0;

    virtual void initScene() = 0;
    virtual void resizeScene(size_t newHeight, size_t newWidth) = 0;
    virtual void swapBuffers() = 0;
    virtual void terminateScene() = 0;

    virtual void enableZBuffering();
    virtual void disableZBuffering();
    virtual void clearFrameBuffer();
    virtual void clearZBuffer();

    virtual void drawPoint(double x, double y, const vec3<> &color);
    virtual void drawLine(double x1, double y1, double x2, double y2, const vec3<> &color);
    virtual void drawLine(double x1, double y1, double x2, double y2);
    virtual void drawTriangle(Vertex v1, Vertex v2, Vertex v3
    #ifdef EXPERIMENT
    , long double *total_shading_time = nullptr
    #endif
    );

    void setBackgroundColor(const vec3<> &backgroundColor);
    void setDefaultLinesColor(const vec3<> &color);
    vec3<> getBackgroundColor();
    size_t getSceneWidth();
    size_t getSceneHeight();

    void setFragmentShader(std::shared_ptr<FragmentShader> fragmentShader);
    std::shared_ptr<FragmentShader> getFragmentShader();

    const std::shared_ptr<ZBuffer> getZBuffer() const;
    void loadZBufferToFrameBuffer();

protected:
    bool clip(const Vertex& v);
    bool testAndSet(const vec3<> &p, double **data);
    int getSign(int value);

protected:
    std::size_t _width, _height;
    vec3<> _backgroundColor;
    vec3<> _defaultLinesColor;
    std::shared_ptr<FrameBuffer> _frameBuffer;
    std::shared_ptr<ZBuffer> _depthBuffer;
    bool _isDepthTestingEnabled;
    mat4<> _imageMatrix;
    std::shared_ptr<FragmentShader> _fragmentShader;
};

#endif