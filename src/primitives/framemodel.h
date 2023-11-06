#ifndef FRAMEMODEL_H
#define FRAMEMODEL_H

#include <memory>

#include "primitives/details.h"
#include "primitives/sceneobject.h"
#include "primitives/ipoly_transformable.h"

class FrameModel : public SceneObject, public IPolyTransformable<FrameModel>
{
public:
    FrameModel();
    FrameModel(const std::shared_ptr<Details> &details);

    virtual void accept(Visitor &visitor) override;

    const std::shared_ptr<Details> get_details() const;
    void set_details(std::shared_ptr<Details> details);

    std::shared_ptr<SceneObject> toPolygonModel() override;

private:
    std::shared_ptr<Details> _details;
};

#endif // FRAMEMODEL_H
