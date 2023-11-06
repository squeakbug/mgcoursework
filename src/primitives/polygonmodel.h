#ifndef POLYGONMODEL_H
#define POLYGONMODEL_H

#include <vector>
#include <memory>

#include "primitives/sceneobject.h"
#include "primitives/ebo_setuper.h"
#include "base_objects/material_property.h"
#include "shaders/fragment_shader.h"

#include "primitives/iframe_transformable.h"

class PolygonModel : public SceneObject, public IFrameTransformable<PolygonModel>
{
public:
    PolygonModel();
    PolygonModel(std::shared_ptr<MaterialProperty> material);

    void accept(Visitor &visitor) override;

    void addVertex(std::shared_ptr<Vertex> vertex);

    void setupEBO(std::shared_ptr<EBOSetuper> setuper);

    const std::vector<std::shared_ptr<Vertex>> &getVBO() const;
    std::vector<std::shared_ptr<Vertex>> &getVBO();
    std::vector<std::size_t> getEBO() const;

    void setMaterial(std::shared_ptr<MaterialProperty> material);
    const std::shared_ptr<MaterialProperty> getMaterial() const;

    void setFragmentShader(std::shared_ptr<FragmentShader> fragmentShader);
    std::shared_ptr<FragmentShader> getFragmentShader();

    std::shared_ptr<SceneObject> toFrameModel() override;

public:
    std::vector<std::shared_ptr<Vertex>> VBO;
    std::vector<std::size_t> EBO;
    std::shared_ptr<MaterialProperty> _material;
    std::shared_ptr<FragmentShader> _fragmentShader;
};

#endif // POLYGONMODEL_H
