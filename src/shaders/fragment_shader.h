#ifndef FRAGMENT_SHADER_H
#define FRAGMENT_SHADER_H

#include <vector>
#include <memory>

#include "base_objects/vertex.h"
#include "base_objects/material_property.h"
#include "math/math.h"
#include "primitives/light_types/direct_light_source.h"
#include "frame_buffers/frame_buffer.h"
#include "frame_buffers/z_buffer.h"
#include "shadowmap/shadowmap_pool.h"

class FragmentShader
{
public:
    virtual vec3<> shade(const Vertex &a, const Vertex &b, const Vertex &c, const vec3<> &pos) = 0;
    virtual ~FragmentShader() = 0;

    void setDirectSources(std::vector<std::shared_ptr<DirectLightSource>> &&src);
    void setMaterial(std::shared_ptr<MaterialProperty> material);
    void setViewPositon(const vec3<> &viewPosition);

    virtual vec3<> calculateIntencityForLightmap(const vec3<> &objectColor, const vec3<> &outNormal);

    void setLightmapUsing(bool isUsing);
    void setLightmap(std::shared_ptr<FrameBuffer> lightmap);

    void setShadowmapUsing(bool isUsing);
    void setShadowmapPool(std::shared_ptr<ShadowmapPool> shadowmapPool);

    void setFromImageToClipMatrix(mat4<> matrix);
    void setClipToGlobalMatrix(mat4<> matrix);

protected:
    std::vector<std::shared_ptr<DirectLightSource>> _directSources;

    std::shared_ptr<MaterialProperty> _material;
    vec3<> _viewPosition;

    bool _isLightmapUsing;
    std::shared_ptr<FrameBuffer> _lightmap;

    mat4<> _fromImageToClipMatrix;
    mat4<> _fromClipToGlobalMatrix;

    bool _isShadowmapUsing;
    std::shared_ptr<ShadowmapPool> _shadowmapPool;
};

#endif // FRAGMENT_SHADER_H
