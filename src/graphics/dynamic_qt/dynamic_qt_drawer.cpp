#include "dynamic_qt_drawer.h"

DynamicQtDrawer::DynamicQtDrawer(size_t height, size_t width, vec3<> backgroundColor)
    : BaseDrawer(height, width, backgroundColor),
    _window(nullptr),
    _graphicsView(nullptr),
    _graphicsScene(nullptr),
    _img(new QImage(_width, _height, QImage::Format_RGB32)),
    _isWindowCreatedInit(false)
{
    
}

DynamicQtDrawer::~DynamicQtDrawer()
{

}

void DynamicQtDrawer::initScene()
{
    if (_isWindowCreatedInit == true)
        return;

    _window = new QMainWindow();
    _window->setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
    _graphicsView = new QGraphicsView(_window);
    _graphicsScene = new QGraphicsScene(_window);

    _graphicsView->setScene(_graphicsScene);
    _graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    _graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _graphicsView->resize(_width, _height);
    _window->resize(_width, _height);
    _graphicsScene->setSceneRect(0, 0, _width, _height);
    _window->show();

    _isWindowCreatedInit = true;
}

void DynamicQtDrawer::resizeScene(size_t newHeight, size_t newWidth)
{
    _width = newWidth;
    _height = newHeight;
    _imageMatrix = math<>::image(_width, _height);

    _depthBuffer = std::make_shared<ZBuffer>(_height, _width);
    _frameBuffer = std::make_shared<FrameBuffer>(_height, _width, _backgroundColor);
    _img = std::shared_ptr<QImage>(new QImage(_width, _height, QImage::Format_RGB32));
}

void DynamicQtDrawer::swapBuffers()
{    
    for (size_t col = 0; col < _width; col++)
    {
        for (size_t row = 0; row < _height; row++)
        {
            vec3<> clr = (*_frameBuffer)[row][col];
            _img->setPixelColor(col, row, qRgb(clr.r, clr.g, clr.b));
        }
    }

    _graphicsScene->addPixmap(QPixmap::fromImage(*_img));
}

void DynamicQtDrawer::terminateScene()
{
    _isWindowCreatedInit = false;

    delete _graphicsView;
    delete _graphicsScene;
    delete _window;
}
