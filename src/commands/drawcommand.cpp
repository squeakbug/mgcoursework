#include "commands/drawcommand.h"

#include "terrain/terrainblock.h"

#include "managers/scenemanager.h"
#include "managers/drawmanager.h"
#include "managers/terrainmanager.h"

#include "scene/scene_selector.h"

#include "primitives/clipping_spaces/piramid_clipping_space.h"
#include "primitives/clipping_spaces/rect_clipping_space.h"

#include "shaders/fragment_shaders/gouraud_fragment_shader.h"
#include "shaders/fragment_shaders/simple_fragment_shader.h"

#include "visitors/shadow_generator.h"


BaseDrawCommand::BaseDrawCommand(std::shared_ptr<BaseDrawer> drawer)
    : _drawer(drawer)
{

}


MainDrawCommand::MainDrawCommand(std::shared_ptr<BaseDrawer> drawer, ClipSpaceType clipSpaceType)
    : BaseDrawCommand(drawer)
{
    _clipSpaceType = clipSpaceType;
}

/* TODO Должна создаваться камера. Кем должна создаваться камера??? на основе чего она должна создаться */
/* TODO Убрать эти магические числа */
/* TODO Зачем каждый раз создавать визитера??? */
void MainDrawCommand::execute()
{
    std::shared_ptr<DrawManager> drawManager = DrawManager::instance();
    std::shared_ptr<DrawVisitor> visitor(new DrawVisitor(drawManager));
    std::shared_ptr<LightmapPool> pool = LightmapPool::instance();
    _drawer->initScene();
    visitor->set_drawer(_drawer);
    drawManager->set_main_visitor(visitor);
    drawManager->setLightmapPool(pool);

    float aspectRatio = float(_drawer->getSceneWidth()) / _drawer->getSceneHeight();
    const float left = -75.f;
    const float right = 75.f;
    const float top = right / aspectRatio;
    const float down = left / aspectRatio;
    const float near = 0.1f;
    const float far = 500.f;

    std::shared_ptr<Scene> scene = SceneManager::instance()->get_scene();
    std::shared_ptr<Camera> cameraPtr = scene->get_camera();
    if (cameraPtr == nullptr)
    {
        std::shared_ptr<ClippingSpace> clipSpace;
        if (_clipSpaceType == ClipSpaceType::PERSPECTIVE)
            clipSpace = std::shared_ptr<ClippingSpace>(new PiramidClippingSpace(math<>::radians(45.f), aspectRatio, near, far));
        else if (_clipSpaceType == ClipSpaceType::ORTHO)
            clipSpace = std::shared_ptr<ClippingSpace>(new RectClippingSpace(left, right, down, top, near, far,  math<>::radians(45.f)));

        cameraPtr = std::shared_ptr<Camera>(new Camera(clipSpace, vec3<>(-30.f, -30.f, 25.f), vec3<>(0.f, 0.f, 1.0f)));
        scene->set_camera(cameraPtr);
    }
}

SetupShadowDrawCommand::SetupShadowDrawCommand(std::shared_ptr<BaseDrawer> drawer)
    : BaseDrawCommand(drawer)
{

}

void SetupShadowDrawCommand::execute()
{
    std::shared_ptr<DrawManager> drawManager = DrawManager::instance();
    auto shadowmapPool = ShadowmapPool::instance();
    auto shadowmapGenerator = std::make_shared<ShadowGenerator>();
    shadowmapGenerator->set_drawer(_drawer);
    shadowmapPool->setGenerator(shadowmapGenerator);
    drawManager->setShadowmapPool(shadowmapPool);
}

LightmapDrawCommand::LightmapDrawCommand(std::shared_ptr<BaseDrawer> drawer)
    : BaseDrawCommand(drawer)
{

}


void LightmapDrawCommand::execute()
{
    std::shared_ptr<DrawManager> drawManager = DrawManager::instance();
    std::shared_ptr<SceneManager> scene_manager = SceneManager::instance();
    std::shared_ptr<Scene> scene = scene_manager->get_scene();
    static std::shared_ptr<DrawVisitor> visitor(new DrawVisitor(drawManager));
    _drawer->initScene();
    visitor->set_drawer(_drawer);

    if (scene != nullptr)
    {
        std::shared_ptr<LightmapPool> pool = LightmapPool::instance();
        pool->accept(*visitor);
    }
}


HeightmapDrawCommand::HeightmapDrawCommand(std::shared_ptr<BaseDrawer> drawer)
    : BaseDrawCommand(drawer)
{

}

/* Камеры в визитере не должно быть, так как не для всех окон требуется камера. Например для отрисовки карты */
void HeightmapDrawCommand::execute()
{
    std::shared_ptr<DrawManager> draw_manager = DrawManager::instance();
    static std::shared_ptr<DrawVisitor> visitor(new DrawVisitor(draw_manager));
    _drawer->initScene();
    visitor->set_drawer(_drawer);

    std::shared_ptr<TerrainBlock> terrain = TerrainManager::instance()->get_terrain_block();
    draw_manager->set_heightmap_visitor(visitor);
    draw_manager->draw_heightmap(terrain);
}

UpdateScreenCommand::UpdateScreenCommand(std::shared_ptr<BaseDrawer> drawer)
    : BaseDrawCommand(drawer)
{

}

void UpdateScreenCommand::execute()
{
    std::shared_ptr<DrawManager> drawManager = DrawManager::instance();
    std::shared_ptr<Scene> scene = SceneManager::instance()->get_scene();
    std::shared_ptr<DrawVisitor> visitor = drawManager->getMainVisitor();

    if (scene != nullptr && visitor != nullptr)
    {
        std::shared_ptr<Camera> cameraPtr = scene->get_camera();
        drawManager->set_cam(cameraPtr);
        scene->accept(visitor);
    }
}

CloseViewportCommand::CloseViewportCommand(std::shared_ptr<BaseDrawer> drawer)
    : BaseDrawCommand(drawer)
{

}

void CloseViewportCommand::execute()
{
    _drawer->terminateScene();
}

SetFragmentShaderCommand::SetFragmentShaderCommand(std::shared_ptr<BaseDrawer> drawer, ShaderType shaderType)
    : BaseDrawCommand(drawer),
    _shaderType(shaderType)
{

}

void SetFragmentShaderCommand::execute()
{
    std::shared_ptr<FragmentShader> fragmentShader;
    std::shared_ptr<Scene> scene = SceneManager::instance()->get_scene();

    switch (_shaderType)
    {
    case ShaderType::FRAG_GOURAUD:
        fragmentShader = std::shared_ptr<FragmentShader>(new GouraudFragmentShader());
        break;
    case ShaderType::FRAG_SIMPLE:
        fragmentShader = std::shared_ptr<FragmentShader>(new SimpleFragmentShader());
        break;
    
    //TODO call exception
    default:
        return ;
    }

    for (auto &object : *scene)
    {
        if (std::dynamic_pointer_cast<PolygonModel>(object) != nullptr)
            std::dynamic_pointer_cast<PolygonModel>(object)->setFragmentShader(fragmentShader);
    }
    
}

ResizeDrawerCommand::ResizeDrawerCommand(std::shared_ptr<BaseDrawer> drawer, size_t width, size_t height)
    : BaseDrawCommand(drawer)
{
    _width = width;
    _height = height;
}

void ResizeDrawerCommand::execute()
{
    _drawer->resizeScene(_height, _width);
}

SetBackgroundColorCommand::SetBackgroundColorCommand(std::shared_ptr<BaseDrawer> drawer, vec3<> color)
    : BaseDrawCommand(drawer)
{
    _drawer = drawer;
    _color = color;
}

void SetBackgroundColorCommand::execute()
{
    _drawer->setBackgroundColor(_color);
}

SetDefaultLinesColorCommand::SetDefaultLinesColorCommand(std::shared_ptr<BaseDrawer> drawer, vec3<> color)
    : BaseDrawCommand(drawer)
{
    _drawer = drawer;
    _color = color;
}

void SetDefaultLinesColorCommand::execute()
{
    _drawer->setDefaultLinesColor(_color);
}

