#include "primitives/framemodel.h"


FrameModel::FrameModel()
    : _details(new Details)
{

}

FrameModel::FrameModel(const std::shared_ptr<Details> &details)
    : _details(details)
{

}

void FrameModel::accept(Visitor &visitor)
{
    visitor.visit(*this);
}

const std::shared_ptr<Details> FrameModel::get_details() const
{
    return _details;
}

void FrameModel::set_details(std::shared_ptr<Details> details)
{
    _details = details;
}

std::shared_ptr<SceneObject> FrameModel::toPolygonModel()
{
    return std::shared_ptr<SceneObject>(new FrameModel(*this));
}
