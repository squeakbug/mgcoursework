#ifndef QT_DRAWER_H
#define QT_DRAWER_H

#include <QGraphicsScene>
#include <QImage>

#include <memory>

#include "frame_buffers/frame_buffer.h"
#include "frame_buffers/z_buffer.h"
#include "graphics/base_drawer.h"
#include "math/math.h"

class QtDrawer : public BaseDrawer
{
public:
    QtDrawer(QGraphicsScene *s, size_t width, size_t height, vec3<> backgroundColor);
    ~QtDrawer();

    void initScene() override;
    void resizeScene(size_t newHeight, size_t newWidth) override;
    void swapBuffers() override;
    void terminateScene() override;

private:
    QtDrawer(const QtDrawer &drawer) = delete;
    QtDrawer &operator=(const QtDrawer &drawer) = delete;

private:
    QGraphicsScene *_scene;
    std::shared_ptr<QImage> _img;
};

#endif