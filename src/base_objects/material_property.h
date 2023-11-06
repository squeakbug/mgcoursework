#ifndef MATERIAL_PROPERTY_H
#define MATERIAL_PROPERTY_H

#include "base_objects/vector3f.h"

const float minAmbientReflectivity = 0.f;
const float maxAmbientReflectivity = 1.f;
const float minDiffuseReflectivity = 0.f;
const float maxDiffuseReflectivity = 1.f;
const float minSpecularReflectivity = 0.f;
const float maxSpecularReflectivity = 1.f;

const vec3<> defaultAmbientReflectivity = { 0.f, 0.f, 0.f };
const vec3<> defaultDiffuseReflectivity = { 0.f, 0.f, 0.f };
const vec3<> defaultSpecularReflectivity = { 0.f, 0.f, 0.f };

class MaterialProperty
{
public:
    MaterialProperty(const vec3<> &ambientReflectivity = defaultAmbientReflectivity,
        const vec3<> &diffuseReflectivity = defaultDiffuseReflectivity,
        const vec3<> &specularReflectivity = defaultSpecularReflectivity);

    const vec3<> &getAmbientReflectivity() const;
    const vec3<> &getDiffuseReflectivity() const;
    const vec3<> &getSpecularReflectivity() const;

    void setAmbientReflectivity(const vec3<> &value);
    void setDiffuseReflectivity(const vec3<> &value);
    void setSpecularReflectivity(const vec3<> &value);

private:
    void checkAmbientReflectivity(const vec3<> &value);
    void checkDiffuseReflectivity(const vec3<> &value);
    void checkSpecularReflectivity(const vec3<> &value);

private:
    vec3<> _ambientReflectivity;
    vec3<> _diffuseReflectivity ;
    vec3<> _specularReflectivity ;
};

#endif