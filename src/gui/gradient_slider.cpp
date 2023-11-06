#include "gui/gradient_slider.h"
#include "painter/gradient.h"
#include "commands/application_commands.h"


GradientSlider::GradientSlider(QWidget *parent)
    : QWidget(parent)
{

    setSizePolicy(
        QSizePolicy::MinimumExpanding,
        QSizePolicy::MinimumExpanding
    );

    _gradient.push_back(std::make_pair(0.0, QColor("#00ff00")));
    _gradient.push_back(std::make_pair(1.0, QColor("#00ff00")));

    _dragedStop = -1;
}

void GradientSlider::paintEvent(QPaintEvent *event)
{
    QPainter *painter = new QPainter(this);
    int width = painter->device()->width();
    int height = painter->device()->height();

    QLinearGradient *gradient = new QLinearGradient(0, 0, width, 0);
    for (auto stopColorPair : _gradient)
        gradient->setColorAt(stopColorPair.first, stopColorPair.second);

    QRect rect(0, 0, width, height);
    painter->fillRect(rect, *gradient);

    QPen pen;
    pen.setWidth(2);
    int y = height / 2;
    for (auto &posColorPair : _gradient)
    {
        pen.setColor(QColor("#ffffff"));
        painter->setPen(pen);

        double stop = posColorPair.first;
        painter->drawLine(stop * width, y - _handle_h, stop * width, y + _handle_h);

        pen.setColor(QColor("#ff0000"));
        painter->setPen(pen);

        QRect rect(
            stop * width - _handle_w/2,
            y - _handle_h/2,
            _handle_w,
            _handle_h
        );
        painter->drawRect(rect);
    }

    painter->end();
}

void GradientSlider::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::RightButton)
    {
        int pos = find_stop_handle_for_event(e, false);
        if (pos != -1)
            assignColorAtPosition(pos);
    }
    else if (e->button() == Qt::LeftButton)
    {
        int pos = find_stop_handle_for_event(e, true);
        if (pos != -1)
            _dragedStop = pos;
    }
}

void GradientSlider::mouseReleaseEvent(QMouseEvent *e)
{
    _dragedStop = -1;
    emit gradientChanged();
}

void GradientSlider::mouseMoveEvent(QMouseEvent *e)
{
    if (_dragedStop != -1)
    {
        double stop = double(e->x()) / width();
        if (stop > 0 && stop < 1)
        {
            std::pair<double, QColor> posColorPair = _gradient[_dragedStop];
            _gradient[_dragedStop] = std::make_pair(stop, posColorPair.second);
            update();
        }
    }
}

void GradientSlider::mouseDoubleClickEvent(QMouseEvent *e)
{
    int pos = find_stop_handle_for_event(e, false);
    if (pos != -1)
    {
        if (pos > 0 && pos + 1 < _gradient.size())
            removeStopAtPosition(pos);
    }
    else
    {
        double stop = double(e->x()) / width();
        addStop(stop, QColor("#ffffff"));
    }
}

void GradientSlider::addStop(double stop, const QColor &color)
{
    assert (0.0 - math<>::eps < stop
        && stop < 1.0 + math<>::eps);

    for (size_t i = 0; i < _gradient.size(); ++i)
    {
        if (_gradient[i].first > stop)
        {
            _gradient.insert(_gradient.begin() + i, std::make_pair(stop, color));
            break;
        }
    }

    emit gradientChanged();
    update();
}

void GradientSlider::removeStopAtPosition(int pos)
{
    if (pos != 0 && pos != _gradient.size() - 1)
    {
        _gradient.erase(_gradient.begin() + pos);
        emit gradientChanged();
        update();
    }
}

void GradientSlider::setColorAtPosition(int pos, QColor color)
{
    if (pos < _gradient.size() && pos >= 0)
    {
        std::pair<double, QColor> posColorPair = _gradient[pos];
        _gradient[pos] = std::make_pair(posColorPair.first, color);
        emit gradientChanged();
        update();
    }
}

void GradientSlider::assignColorAtPosition(int pos)
{
    QColorDialog *dlg = new QColorDialog(this);

    if (dlg->exec())
        setColorAtPosition(pos, dlg->currentColor());
}

std::shared_ptr<Gradient> GradientSlider::getAsGradient() const
{
    auto gradient = std::make_shared<Gradient>();

    for (auto &posColorPair : _gradient)
    {
        QColor clr = posColorPair.second;
        gradient->addStop(posColorPair.first, { clr.redF(), clr.greenF(), clr.blueF() });
    }

    return gradient;
}

int GradientSlider::find_stop_handle_for_event(QMouseEvent *e, bool isFinalsExcluded)
{
    int width = this->width();
    int height = this->height();
    int midpoint = height / 2;

    if (e->y() >= midpoint - _handle_h
        && e->y() <= midpoint + _handle_h)
    {

        for (size_t i = 0; i < _gradient.size(); ++i)
        {
            if (isFinalsExcluded && (i == 0 || i == _gradient.size() - 1))
                continue;

            double stop = _gradient[i].first;
            if (e->x() >= stop * width - _handle_w
                && e->x() <= stop * width + _handle_w)
            {
                return i;
            }
        }
    }

    return -1;
}
