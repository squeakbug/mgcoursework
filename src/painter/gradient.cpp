#include "painter/gradient.h"
#include "math/math.h"

#include <iostream>

vec3<> Gradient::getColor(float value) const
{
    size_t lowerBound = 0, upperBound = _stops.size() - 1;

    while (lowerBound + 1 < upperBound)
    {
        size_t mid = (lowerBound + upperBound) / 2;
        if (fabs(_stops[mid].first - value) < math<>::eps)
            return _stops[mid].second;

        if (value < _stops[mid].first)
            upperBound = mid;
        else
            lowerBound = mid;
    }

    float t = (value - _stops[lowerBound].first) / (_stops[upperBound].first - _stops[lowerBound].first);

    return _stops[lowerBound].second * (1.f - t) + _stops[upperBound].second * t;
}

void Gradient::addStop(float stop, const vec3<> &color)
{
    assert (0.0 <= stop && stop <= 1.0);

    for (size_t i = 0; i < _stops.size(); ++i)
    {
        if (_stops[i].first > stop)
        {
            _stops.insert(_stops.begin() + i, std::make_pair(stop, color));
            break;
        }
    }

    _stops.push_back(std::make_pair(stop, color));
}

void Gradient::removeStopAtPosition(std::size_t pos)
{
    if (pos != 0 && pos != _stops.size() - 1)
        _stops.erase(_stops.begin() + pos);

}

void Gradient::setColorAtPosition(std::size_t pos, const vec3<> color)
{
    if (pos < _stops.size() && pos >= 0)
    {
        std::pair<double, vec3<>> posColorPair = _stops[pos];
        _stops[pos] = std::make_pair(posColorPair.first, color);
    }
}

const vec3<> &Gradient::getColorAtPosition(std::size_t pos) const
{
    //TODO check existance

    return _stops[pos].second;
}
