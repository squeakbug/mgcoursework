#include "graphics/base_drawer.h"
#include "math/math.h"
#include "shaders/fragment_shader.h"

#include <iostream>
#ifdef EXPERIMENT
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

uint64_t time_stamp(void)
{
    uint32_t high, low;
    __asm__ __volatile__ (
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r" (high), "=r" (low)
        :: "%rax", "%rbx", "%rcx", "%rdx"
    );

    uint64_t ticks = ((uint64_t)high << 32) | low;
    return ticks;
}
#endif

BaseDrawer::BaseDrawer(size_t height, size_t width, vec3<> backgroundColor, std::shared_ptr<FragmentShader> fragmentShader)
    : _width(width),
    _height(height),
    _backgroundColor(backgroundColor),
    _defaultLinesColor({255.f, 255.f, 255.f}),
    _frameBuffer(new FrameBuffer(_height, _width, _backgroundColor)),
    _depthBuffer(new ZBuffer(_height, _width)),
    _isDepthTestingEnabled(false),
    _fragmentShader(fragmentShader)
{
    _imageMatrix = math<>::image(_width, _height);
}

BaseDrawer::~BaseDrawer()
{

}

void BaseDrawer::enableZBuffering()
{
    _isDepthTestingEnabled = true;
}

void BaseDrawer::disableZBuffering()
{
    _isDepthTestingEnabled = false;
}

void BaseDrawer::clearFrameBuffer()
{
    _frameBuffer->clearBuffer();
}

void BaseDrawer::clearZBuffer()
{
    _depthBuffer->clearBuffer();
}

void BaseDrawer::drawPoint(double x, double y, const vec3<> &color)
{
    vec4<> p = { x, y, 0.f, 1.f };
    p = vec3<>(_imageMatrix * p);
    
    (*_frameBuffer)[(size_t) p.y][(size_t) p.x] = color * 255.f;
}

void BaseDrawer::drawLine(double x1, double y1, double x2, double y2)
{
    drawLine(x1, y1, x2, y2, _defaultLinesColor * 255);
}

void BaseDrawer::drawLine(double x1, double y1, double x2, double y2, const vec3<> &color)
{
    if (x1 < -1.f || x1 > 1.f)
        return;
    if (x2 < -1.f || x2 > 1.f)
        return;

    if (y1 < -1.f || y1 > 1.f)
        return;
    if (y2 < -1.f || y2 > 1.f)
        return;

    vec4<> p1 = { x1, y1, 0.f, 1.f };
    vec4<> p2 = { x2, y2, 0.f, 1.f };  
    p1 = vec3<>(_imageMatrix * p1);
    p2 = vec3<>(_imageMatrix * p2);

    bool obmen = false;

    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;
    int sx = getSign(dx);
    int sy = getSign(dy);
    dx = abs(dx);
    dy = abs(dy);

    if (dy > dx)
    {
        obmen = true;
        std::swap(dx, dy);
    }

    int m = 2 * dy;
    int err = m - dx;

    int x = p1.x;
    int y = p1.y;

    for (int i = 0; i < dx; i++)
    {
        (*_frameBuffer)[y][x] = color * 255.f;

        if (obmen)
        {
            y += sy;
            if (err > 0)
            {
                err -= 2 * dx;
                x += sx;
            }
        }
        else
        {
            x += sx;
            if (err > 0)
            {
                err -= 2 * dx;
                y += sy;
            }
        }

        err += m;
    }
}

void BaseDrawer::drawTriangle(Vertex v1, Vertex v2, Vertex v3
#ifdef EXPERIMENT
, long double *total_shading_time
#endif
)
{
    v1.position = vec3<>(_imageMatrix * vec4<>(v1.position, 1.f));
    v2.position = vec3<>(_imageMatrix * vec4<>(v2.position, 1.f));
    v3.position = vec3<>(_imageMatrix * vec4<>(v3.position, 1.f));

    _fragmentShader->setFromImageToClipMatrix(math<>::inverse(_imageMatrix));

    vec3<> p1 = v1.position;
    vec3<> p2 = v2.position;
    vec3<> p3 = v3.position;

    double sx = std::floor(mmin3(p1.x, p2.x, p3.x));
    double ex = std::ceil(mmax3(p1.x, p2.x, p3.x));

    double sy = std::floor(mmin3(p1.y, p2.y, p3.y));
    double ey = std::ceil(mmax3(p1.y, p2.y, p3.y));

    std::size_t intSx = (std::size_t) sx, intEx = (std::size_t) ex, intSy = (std::size_t) sy, intEy = (std::size_t) ey;

    double **zbuffer = _depthBuffer->data();

    #ifdef EXPERIMENT
    double shading_time = 0.0;
    #endif

    //#pragma omp parallel for
    for (auto x = intSx; x < intEx; x++)
    {
        for (auto y = intSy; y < intEy; y++)
        {
            vec3<> bary = math<>::toBarycentric(p1, p2, p3, vec3<>(static_cast<double>(x), static_cast<double>(y), 0));

            if ( (bary.x > 0.0f) && (bary.x < 1.0f) &&
                 (bary.y > 0.0f) && (bary.y < 1.0f) &&
                 (bary.z > 0.0f))
            {
                vec3<> interpolated = math<>::barycentricInterpolation(p1, p2, p3, bary);

                interpolated.x = x;
                interpolated.y = y;
                if (testAndSet(interpolated, zbuffer))
                {
                    #ifdef EXPERIMENT
                    double _p1_ = time_stamp();
                    #endif
                    vec3<> pixel_color = _fragmentShader->shade(v1, v2, v3, bary) * 255.f;
                    #ifdef EXPERIMENT
                    double _p2_ = time_stamp();
                    shading_time += _p2_ - _p1_;
                    #endif
                    (*_frameBuffer)[y][x] = pixel_color;
                }
            }
        }
    }

    #ifdef EXPERIMENT
    if (total_shading_time != nullptr)
        *total_shading_time = shading_time;
    #endif
}

void BaseDrawer::setBackgroundColor(const vec3<> &backgroundColor)
{
    _backgroundColor = backgroundColor;
    _frameBuffer->setClearColor(_backgroundColor);
}

void BaseDrawer::setDefaultLinesColor(const vec3<> &color)
{
    _defaultLinesColor = color;
}

vec3<> BaseDrawer::getBackgroundColor()
{
    return _backgroundColor;
}

size_t BaseDrawer::getSceneWidth()
{
    return _width;
}

size_t BaseDrawer::getSceneHeight()
{
    return _height;
}

void BaseDrawer::setFragmentShader(std::shared_ptr<FragmentShader> fragmentShader)
{
    _fragmentShader = fragmentShader;
}

std::shared_ptr<FragmentShader> BaseDrawer::getFragmentShader()
{
    return _fragmentShader;
}

const std::shared_ptr<ZBuffer> BaseDrawer::getZBuffer() const
{
    return _depthBuffer;
}

void BaseDrawer::loadZBufferToFrameBuffer()
{
    for (size_t i = 0; i < _height; i++)
    {
        for (size_t j = 0; j < _width; j++)
            (*_frameBuffer)[i][j] = vec3<>(((*_depthBuffer)[i][j] > 1.f ? 1.f : (*_depthBuffer)[i][j]) * 255.f);
    }
}


bool BaseDrawer::clip(const Vertex& v)
{
    return (v.position.x > -1) && (v.position.x < 1) &&
           (v.position.y > -1) && (v.position.y < 1) &&
           (v.position.z > 0.f) && (v.position.z < 1);
}

bool BaseDrawer::testAndSet(const vec3<> &p, double **zbuffer)
{
    size_t x = std::round(p.x), y = std::round(p.y);

    if (x >= _width || y >= _height || x < 0 || y < 0)
        return false;

    if (p.z < zbuffer[y][x])
    {
        zbuffer[y][x] = p.z;
        return true;
    }

    return false;
}

int BaseDrawer::getSign(int value)
{
    if (value == 0)
        return 0;

    if (value > 0)
        return 1;
    else
        return -1;
}
