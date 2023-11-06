#include <memory>

#include "visitors/shadow_generator.h"
#include "scene/scene.h"
#include "primitives/polygonmodel.h"
#include "shaders/fragment_shader.h"
#include "shaders/vertex_shader.h"
#include "math/math.h"
#include "errors/runtime_exceptions.h"

const size_t defaultShadowmapWidth= 720;
const size_t defaultShadowmapHeight= 480;

void ShadowGenerator::visit(Scene &scene)
{
    std::shared_ptr<BaseDrawer> _shadow_drawer = _drawer.lock();
    if (_shadow_drawer == nullptr)
        throw NoDrawerException(__FILE__, typeid(*this).name(), __LINE__);

    _shadow_drawer->clearZBuffer();

    for (auto &obj : scene)
        obj->accept(*this);

    _shadowmap = std::shared_ptr<ZBuffer>(new ZBuffer(*_shadow_drawer->getZBuffer()));
}

void ShadowGenerator::visit(PolygonModel &model)
{
    std::vector<std::shared_ptr<Vertex>> VBO = model.getVBO();
    std::vector<std::size_t> EBO = model.getEBO();

    std::shared_ptr<BaseDrawer> _shadow_drawer = _drawer.lock();
    if (_shadow_drawer == nullptr)
        throw NoDrawerException(__FILE__, typeid(*this).name(), __LINE__);

    VertexShader vertexShader;
    //TODO проверка на существование менеджера
    std::shared_ptr<MaterialProperty> material = model.getMaterial();
    std::shared_ptr<FragmentShader> fragmentShader = model.getFragmentShader();
    fragmentShader->setShadowmapUsing(false);
    fragmentShader->setMaterial(material);
    _shadow_drawer->setFragmentShader(fragmentShader);

    mat4<> modelMatrix(1.f);
    mat4<> projViewModelMatrix = _currentLightSource->getProjMatrix() *  _currentLightSource->getViewMatrix() * modelMatrix;

    const size_t VERTICES_IN_TRIANGLES = 3;
    size_t verticesCnt = EBO.size();
    for (size_t i = 0; i < verticesCnt; i += VERTICES_IN_TRIANGLES)
    {
        Vertex v1 = vertexShader.calculate(*VBO[EBO[i]], projViewModelMatrix, modelMatrix);
        Vertex v2 = vertexShader.calculate(*VBO[EBO[i + 1]], projViewModelMatrix, modelMatrix);
        Vertex v3 = vertexShader.calculate(*VBO[EBO[i + 2]], projViewModelMatrix, modelMatrix);

        _shadow_drawer->drawTriangle(v1, v2, v3);
    }
}

ShadowGenerator::ShadowGenerator()
    : _shadowmap(new ZBuffer(defaultShadowmapHeight, defaultShadowmapWidth))
{
    
}

const std::shared_ptr<ZBuffer> ShadowGenerator::getShadowmap() const
{
    return _shadowmap;
}

void ShadowGenerator::clearShadowmap()
{
    _shadowmap->clearBuffer();
}

void ShadowGenerator::setCurrentLightSource(std::shared_ptr<DirectLightSource> source)
{
    _currentLightSource = source;
}

const std::shared_ptr<DirectLightSource> ShadowGenerator::getCurrentLightSource() const
{
    return _currentLightSource;
}

void ShadowGenerator::set_drawer(std::shared_ptr<BaseDrawer> drawer)
{
    _drawer = drawer;
}
