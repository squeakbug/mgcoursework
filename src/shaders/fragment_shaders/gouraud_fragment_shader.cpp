#include "gouraud_fragment_shader.h"

vec3<> GouraudFragmentShader::shade(const Vertex &a, const Vertex &b, const Vertex &c, const vec3<> &pos)
{
    //TODO убрать проверку и сделать отдельные шейдеры, которые используют lightmaps
    vec3<> aColor, bColor, cColor;
    if (!_isLightmapUsing)
    {
        aColor = calculateIntencity(a.color, a.normal);
        bColor = calculateIntencity(b.color, b.normal);
        cColor = calculateIntencity(c.color, c.normal);
    }
    else
    {
        aColor = (*_lightmap)[std::size_t(a.texCoords.y * _lightmap->height())][std::size_t(a.texCoords.x * _lightmap->width())];
        bColor = (*_lightmap)[std::size_t(b.texCoords.y * _lightmap->height())][std::size_t(b.texCoords.x * _lightmap->width())];
        cColor = (*_lightmap)[std::size_t(c.texCoords.y * _lightmap->height())][std::size_t(c.texCoords.x * _lightmap->width())];
    }

    vec3<> interpolatedColor = math<>::barycentricInterpolation(aColor, bColor, cColor, pos);

    if (_isShadowmapUsing)
    {
        bool isShadowed = true;
        vec4<> imagePos = math<>::barycentricInterpolation(a.position, b.position, c.position, pos);
        vec4<> globalPos = _fromClipToGlobalMatrix * _fromImageToClipMatrix * imagePos;
        globalPos = globalPos / globalPos.w;
        
        double ambientSum = 0.0;
        for (size_t i = 0; isShadowed == true && i < _directSources.size(); i++)
        {
            std::shared_ptr<DirectLightSource> curSrc = _directSources[i];
            std::shared_ptr<ZBuffer> shadowmap = _shadowmapPool->getShadowmap(curSrc->getId());
            size_t smWidth = shadowmap->width();
            size_t smHeight = shadowmap->height();

            vec4<> vInShadowBuffer = math<>::image(smWidth, smHeight) * curSrc->getProjMatrix() * curSrc->getViewMatrix() * globalPos;

            if (size_t(vInShadowBuffer.x) < smWidth - 1 && size_t(vInShadowBuffer.x) > 0 
                && size_t(vInShadowBuffer.y) < smHeight - 1 && size_t(vInShadowBuffer.y) > 0)
            {
                if ((*shadowmap)[size_t(vInShadowBuffer.y)][size_t(vInShadowBuffer.x)] + 0.001 > vInShadowBuffer.z)  // magic coefficient
                    isShadowed = false;
            }
            else
            {
                isShadowed = false;
            }

            ambientSum += _directSources[i]->getAmbient();
        }

        if (isShadowed)
            interpolatedColor *= math<>::clamp(ambientSum, 0.0, 1.0);
    }

    return interpolatedColor;
}

vec3<> GouraudFragmentShader::calculateIntencity(const vec3<> &objectColor, const vec3<> &outNormal)
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
