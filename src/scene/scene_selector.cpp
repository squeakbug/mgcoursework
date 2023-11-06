#include "scene_selector.h"

std::vector<std::shared_ptr<DirectLightSource>> SceneSelector::selectEnabledDirectLightSources(const std::shared_ptr<Scene> &scene)
{
    std::vector<std::shared_ptr<DirectLightSource>> output;

    for (auto &obj : *scene)
    {
        std::shared_ptr<DirectLightSource> src = std::dynamic_pointer_cast<DirectLightSource>(obj);
        if (src != nullptr && src->isEnabled())
            output.push_back(std::static_pointer_cast<DirectLightSource>(obj));
    }

    return output;
}