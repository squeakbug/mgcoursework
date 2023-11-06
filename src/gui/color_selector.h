#ifndef COLOR_SELECTOR_H
#define COLOR_SELECTOR_H

#include <QWidget>
#include <QSlider>
#include <QColor>
#include <QPainter>
#include <QRect>
#include <QLinearGradient>
#include <QColorDialog>
#include <QMouseEvent>
#include <QDebug>

#include <memory>

class ColorSelector : public QWidget
{
    Q_OBJECT
public:
    explicit ColorSelector(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;

    QColor getColor();

signals:
    void colorChanged();

private:
    QColor _curColor;
};

#endif