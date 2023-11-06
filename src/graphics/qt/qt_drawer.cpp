#include "graphics/qt/qt_drawer.h"
#include "shaders/vertex_shader.h"
#include "shaders/fragment_shader.h"

static const QColor termanatedSceneColor(255, 255, 255);

QtDrawer::QtDrawer(QGraphicsScene *s, size_t width, size_t height, vec3<> backgroundColor)
    : BaseDrawer(height, width, backgroundColor),
    _scene(s),
    _img(new QImage(width, height, QImage::Format_RGB32))
{
    
}

QtDrawer::~QtDrawer()
{

}

void QtDrawer::initScene()
{

}

void QtDrawer::resizeScene(size_t newHeight, size_t newWidth)
{
    _width = newWidth;
    _height = newHeight;
    _imageMatrix = math<>::image(_width, _height);

    _depthBuffer = std::make_shared<ZBuffer>(_height, _width);
    _frameBuffer = std::make_shared<FrameBuffer>(_height, _width, _backgroundColor);
    _img = std::shared_ptr<QImage>(new QImage(_width, _height, QImage::Format_RGB32));
}

void QtDrawer::swapBuffers()
{    
    for (size_t col = 0; col < _width; col++)
    {
        for (size_t row = 0; row < _height; row++)
        {
            vec3<> clr = (*_frameBuffer)[row][col];
            _img->setPixelColor(col, row, qRgb(clr.r, clr.g, clr.b));
        }
    }

    _scene->addPixmap(QPixmap::fromImage(*_img));
}

void QtDrawer::terminateScene()
{
    _img->fill(termanatedSceneColor);
}
