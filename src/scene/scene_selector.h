#ifndef SCENE_SELECTOR
#define SCENE_SELECTOR

#include <memory>

#include "scene/scene.h"
#include "primitives/light_types/direct_light_source.h"

class SceneSelector
{
public:
    static std::vector<std::shared_ptr<DirectLightSource>> selectEnabledDirectLightSources(const std::shared_ptr<Scene> &scene);
};

#endif