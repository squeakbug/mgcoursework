#include "primitives/polygonmodel.h"

PolygonModel::PolygonModel()
    : PolygonModel(std::shared_ptr<MaterialProperty>(new MaterialProperty()))
{

}

PolygonModel::PolygonModel(std::shared_ptr<MaterialProperty> material)
{
    _material = material;
}

void PolygonModel::addVertex(std::shared_ptr<Vertex> vertex)
{
    VBO.push_back(vertex);
}

void PolygonModel::setupEBO(std::shared_ptr<EBOSetuper> setuper)
{
    setuper->setupEBO(EBO);
}

void PolygonModel::setMaterial(std::shared_ptr<MaterialProperty> material)
{
    _material = material;
}

void PolygonModel::setFragmentShader(std::shared_ptr<FragmentShader> fragmentShader)
{
    _fragmentShader = fragmentShader;
}

std::shared_ptr<FragmentShader> PolygonModel::getFragmentShader()
{
    return _fragmentShader;
}

void PolygonModel::accept(Visitor &visitor)
{
    visitor.visit(*this);
}

const std::vector<std::shared_ptr<Vertex>> &PolygonModel::getVBO() const
{
    return VBO;
}

std::vector<std::shared_ptr<Vertex>> &PolygonModel::getVBO()
{
    return VBO;
}

std::vector<std::size_t> PolygonModel::getEBO() const
{
    return EBO;
}

const std::shared_ptr<MaterialProperty> PolygonModel::getMaterial() const
{
    return _material;
}

std::shared_ptr<SceneObject> PolygonModel::toFrameModel()
{
    return std::shared_ptr<SceneObject>(new PolygonModel(*this));
}
