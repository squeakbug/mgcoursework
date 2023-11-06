#ifndef GRADIENT_SLIDER_H
#define GRADIENT_SLIDER_H

#include <QWidget>
#include <QSlider>
#include <QColor>
#include <QPainter>
#include <QRect>
#include <QLinearGradient>
#include <QColorDialog>
#include <QMouseEvent>
#include <QDebug>

#include <vector>
#include <utility>
#include <cassert>
#include <memory>

#include "painter/gradient.h"

class GradientSlider : public QWidget
{
    Q_OBJECT

public:
    GradientSlider(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void mouseDoubleClickEvent(QMouseEvent *e) override;

    void addStop(double stop, const QColor &color);
    void removeStopAtPosition(int pos);
    void setColorAtPosition(int pos, QColor color);
    void assignColorAtPosition(int pos);

    std::shared_ptr<Gradient> getAsGradient() const;

signals:
    void gradientChanged();

private:
    int find_stop_handle_for_event(QMouseEvent *e, bool isFinalsExcluded);

private:
    std::vector<std::pair<double, QColor>> _gradient;

    int _dragedStop;

    std::size_t _handle_w = 10;
    std::size_t _handle_h = 10;
};

#endif
