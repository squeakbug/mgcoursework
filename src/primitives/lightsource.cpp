#include <string>

#include "errors/logicexceptions.h"
#include "primitives/lightsource.h"

LightSource::LightSource()
    : _ambient(0.f),
    _diffuse(0.f),
    _specular(0.f)
{

}

LightSource::LightSource(float ambient, float diffuse, float specular, const vec3<> &color, bool isEnabled)
{
    checkAmbient(ambient);
    checkDiffuse(diffuse);
    checkSpecular(specular);
    checkColor(color);

    _ambient = ambient;
    _diffuse = diffuse;
    _specular = specular;
    _color = color;
    _isEnabled = isEnabled;
}

LightSource::~LightSource()
{

}


float LightSource::getAmbient() const
{
    return _ambient;
}

float LightSource::getDiffuse() const
{
    return _diffuse;
}

float LightSource::getSpecular() const
{
    return _specular;
}

const vec3<> &LightSource::getColor() const
{
    return _color;
}

void LightSource::accept(Visitor &visitor)
{
    visitor.visit(*this);
}

void LightSource::setAmbient(float ambient)
{
    checkAmbient(ambient);

    _ambient = ambient;
}

void LightSource::setDiffuse(float diffuse)
{
    checkDiffuse(diffuse);
    
    _diffuse = diffuse;
}

void LightSource::setSpecular(float specular)
{
    checkSpecular(specular);

    _specular = specular;
}

void LightSource::setColor(const vec3<> &color)
{
    checkColor(color);

    _color = color;
}

void LightSource::checkAmbient(float value)
{
    if (value < minAmbientCoeff || value > maxAmbientCoeff)
    {
        throw BadLightSourceArgument(__FILE__, typeid(*this).name(), __LINE__,
            "Значение коэффициента фонового света должно быть в диапазоне: ["
            + std::to_string(minAmbientCoeff) + "; " + std::to_string(maxAmbientCoeff));
    }
}

void LightSource::checkDiffuse(float value)
{
    if (value < minDiffuseCoeff || value > maxDiffuseCoeff)
    {
        throw BadLightSourceArgument(__FILE__, typeid(*this).name(), __LINE__,
            "Значение коэффициента рассеянного света должно быть в диапазоне: ["
            + std::to_string(minDiffuseCoeff) + "; " + std::to_string(maxDiffuseCoeff) + "]");
    }
}

void LightSource::checkSpecular(float value)
{
    if (value < minSpecularCoeff || value > maxSpecularCoeff)
    {
        throw BadLightSourceArgument(__FILE__, typeid(*this).name(), __LINE__,
            "Значение коэффициента зеркально отраженного света должно быть в диапазоне: ["
            + std::to_string(minSpecularCoeff) + "; " + std::to_string(maxSpecularCoeff) + "]");
    }
}

void LightSource::checkColor(const vec3<> &color)
{
    //TODO add method to fetching color components number
    for (size_t i = 0; i < 3; i++)
    {
        if (color[i] < minColorComponentValue || color[i] > maxColorComponentValue)
        {
            throw BadLightSourceArgument(__FILE__, typeid(*this).name(), __LINE__,
                "Значение компонентов цвета света должно быть в диапазоне: ["
                + std::to_string(minColorComponentValue) + "; " + std::to_string(maxColorComponentValue) + "]");
        }
    }
}
