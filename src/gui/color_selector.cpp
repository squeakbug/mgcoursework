#include "gui/color_selector.h"
#include "commands/application_commands.h"

ColorSelector::ColorSelector(QWidget *parent)
    : QWidget(parent)
{
    setSizePolicy(
        QSizePolicy::MinimumExpanding,
        QSizePolicy::MinimumExpanding
    );
}

void ColorSelector::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter(this);
    int width = painter->device()->width();
    int height = painter->device()->height();

    QRect rect(0, 0, width, height);
    painter->fillRect(rect, _curColor);

    painter->end();
}

void ColorSelector::mousePressEvent(QMouseEvent *e)
{
    QColorDialog *dlg = new QColorDialog(this);

    if (dlg->exec())
        _curColor = dlg->currentColor();
}

void ColorSelector::mouseReleaseEvent(QMouseEvent *e)
{
    emit colorChanged();
}

QColor ColorSelector::getColor()
{
    return _curColor;
}
