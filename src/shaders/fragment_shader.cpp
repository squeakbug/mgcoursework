#include <algorithm>
#include <utility>

#include "shaders/fragment_shader.h"
#include "math/math.h"

FragmentShader::~FragmentShader()
{

}


void FragmentShader::setDirectSources(std::vector<std::shared_ptr<DirectLightSource>> &&src)
{
    _directSources = std::forward<std::vector<std::shared_ptr<DirectLightSource>>>(src);
}

void FragmentShader::setMaterial(std::shared_ptr<MaterialProperty> material)
{
    _material = material;
}

void FragmentShader::setViewPositon(const vec3<> &viewPosition)
{
    _viewPosition = viewPosition;
}

vec3<> FragmentShader::calculateIntencityForLightmap(const vec3<> &objectColor, const vec3<> &outNormal)
{
    vec3<> result = vec3<>(0.0f);
    vec3<> normal = math<>::normalize(outNormal);

    for (size_t i = 0; i < _directSources.size(); i++)
    {
        vec3<> ambient = _material->getAmbientReflectivity() * _directSources[i]->getAmbient();

        vec3<> lightDir = math<>::normalize(-_directSources[i]->getDirection());
        double diff = std::max(math<>::dot(lightDir, normal), 0.0);
        vec3<> diffuse = _material->getDiffuseReflectivity() * diff * _directSources[i]->getDiffuse();

        result += (ambient + diffuse) * objectColor * _directSources[i]->getColor() / 2;
    }

    result.r = math<>::clamp(result.r, 0.0, 1.0);
    result.g = math<>::clamp(result.g, 0.0, 1.0);
    result.b = math<>::clamp(result.b, 0.0, 1.0);

    return result;
}

void FragmentShader::setLightmapUsing(bool isUsing)
{
    _isLightmapUsing = isUsing;
}

void FragmentShader::setLightmap(std::shared_ptr<FrameBuffer> lightmap)
{
    _lightmap = lightmap;
}

void FragmentShader::setShadowmapUsing(bool isUsing)
{
    _isShadowmapUsing = isUsing;
}

void FragmentShader::setShadowmapPool(std::shared_ptr<ShadowmapPool> shadowmapPool)
{
    _shadowmapPool = shadowmapPool;
}

void FragmentShader::setFromImageToClipMatrix(mat4<> matrix)
{
    _fromImageToClipMatrix = matrix;
}

void FragmentShader::setClipToGlobalMatrix(mat4<> matrix)
{
    _fromClipToGlobalMatrix = matrix;
}
