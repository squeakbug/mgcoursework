#include "material_property.h"

MaterialProperty::MaterialProperty(const vec3<> &ambientReflectivity, const vec3<> &diffuseReflectivity, const vec3<> &specularReflectivity)
    : _ambientReflectivity(ambientReflectivity),
    _diffuseReflectivity(diffuseReflectivity),
    _specularReflectivity(specularReflectivity)
{

}

const vec3<> &MaterialProperty::getAmbientReflectivity() const
{
    return _ambientReflectivity;
}

const vec3<> &MaterialProperty::getDiffuseReflectivity() const
{
    return _diffuseReflectivity;
}

const vec3<> &MaterialProperty::getSpecularReflectivity() const
{
    return _specularReflectivity;
}

void MaterialProperty::setAmbientReflectivity(const vec3<> &value)
{
    checkAmbientReflectivity(value);

    _ambientReflectivity = value;
}

void MaterialProperty::setDiffuseReflectivity(const vec3<> &value)
{
    checkDiffuseReflectivity(value);

    _diffuseReflectivity = value;
}

void MaterialProperty::setSpecularReflectivity(const vec3<> &value)
{
    checkSpecularReflectivity(value);

    _specularReflectivity = value;
}

void MaterialProperty::checkAmbientReflectivity(const vec3<> &value)
{
    for (size_t i = 0; i < value.getDimension(); i++)
    {
        if (value[i] < minAmbientReflectivity || value[i] > maxAmbientReflectivity)
        {
            throw BadMaterialPropertyArgument(__FILE__, typeid(*this).name(), __LINE__,
                "Значение коэффициента рассеянного света должно быть в диапазоне: ["
                + std::to_string(minAmbientReflectivity) + "; " + std::to_string(maxAmbientReflectivity) + "]");
        }
    }
}

void MaterialProperty::checkDiffuseReflectivity(const vec3<> &value)
{
    for (size_t i = 0; i < value.getDimension(); i++)
    {
        if (value[i] < minDiffuseReflectivity || value[i] > maxDiffuseReflectivity)
        {
            throw BadMaterialPropertyArgument(__FILE__, typeid(*this).name(), __LINE__,
                "Значение коэффициента рассеянного света должно быть в диапазоне: ["
                + std::to_string(minDiffuseReflectivity) + "; " + std::to_string(maxDiffuseReflectivity) + "]");
        }
    }
}

void MaterialProperty::checkSpecularReflectivity(const vec3<> &value)
{
    for (size_t i = 0; i < value.getDimension(); i++)
    {
        if (value[i] < minSpecularReflectivity || value[i] > maxSpecularReflectivity)
        {
            throw BadMaterialPropertyArgument(__FILE__, typeid(*this).name(), __LINE__,
                "Значение коэффициента рассеянного света должно быть в диапазоне: ["
                + std::to_string(minSpecularReflectivity) + "; " + std::to_string(maxSpecularReflectivity) + "]");
        }
    }
}