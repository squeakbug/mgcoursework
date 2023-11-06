#ifndef DYNAMIC_QT_DRAWER_H
#define DYNAMIC_QT_DRAWER_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>
#include <QImage>

#include <memory>

#include "graphics/base_drawer.h"
#include "base_objects/vector3f.h"

class DynamicQtDrawer : public BaseDrawer
{
public:
    DynamicQtDrawer(size_t height, size_t width, vec3<> backgroundColor);
    ~DynamicQtDrawer();

    void initScene() override;
    void resizeScene(size_t newHeight, size_t newWidth) override;
    void swapBuffers() override;
    void terminateScene() override;

private:
    DynamicQtDrawer(const DynamicQtDrawer &drawer) = delete;
    DynamicQtDrawer &operator=(const DynamicQtDrawer &drawer) = delete;

private:
    QMainWindow *_window;
    QGraphicsView *_graphicsView;
    QGraphicsScene *_graphicsScene;
    std::shared_ptr<QImage> _img;
    bool _isWindowCreatedInit;
};

#endif