#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "primitives/sceneobject.h"
#include "base_objects/vector3f.h"

const float minAmbientCoeff = 0.f;
const float maxAmbientCoeff = 1.f;
const float minDiffuseCoeff = 0.f;
const float maxDiffuseCoeff = 1.f;
const float minSpecularCoeff = 0.f;
const float maxSpecularCoeff = 1.f;
const float minColorComponentValue = 0.f;
const float maxColorComponentValue = 1.f;

class LightSource : public SceneObject
{
public:
    LightSource();
    LightSource(float ambient, float diffuse, float specular, const vec3<> &color, bool isEnabled = false);
    virtual ~LightSource() = 0;

    virtual void accept(Visitor &visitor) override;

    float getAmbient() const;
    float getDiffuse() const;
    float getSpecular() const;
    const vec3<> &getColor() const;

    void setAmbient(float ambient);
    void setDiffuse(float diffuse);
    void setSpecular(float specular);
    void setColor(const vec3<> &color);

private:
    void checkAmbient(float value);
    void checkDiffuse(float value);
    void checkSpecular(float value);
    void checkColor(const vec3<> &color);

private:
    float _ambient;
    float _diffuse;
    float _specular;
    vec3<> _color;
};

#endif // LIGHTSOURCE_H