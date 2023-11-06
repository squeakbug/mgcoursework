#ifndef QT_FACTORY_H
#define QT_FACTORY_H

#include <QGraphicsScene>
#include <QImage>

#include <memory>

#include "graphics/qt/qt_drawer.h"
#include "graphics/graphicsfactory.h"

class QtFactory : public GraphicsFactory
{
public:
    QtFactory(QGraphicsScene *s);

    virtual std::shared_ptr<BaseDrawer> create_graphics(size_t width, size_t height) override;

private:
    QGraphicsScene *scene;
};

#endif // QTDRAWER_H
