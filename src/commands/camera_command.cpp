#include <memory>

#include "commands/camera_command.h"

#include "managers/drawmanager.h"
#include "managers/scenemanager.h"

#include "errors/logicexceptions.h"

#include "primitives/clipping_spaces/piramid_clipping_space.h"
#include "primitives/clipping_spaces/rect_clipping_space.h"


CameraCommand::CameraCommand()
{

}

MoveCameraCommand::MoveCameraCommand(CameraMovement dir)
{
    _dir = dir;
}

void MoveCameraCommand::execute()
{
    std::shared_ptr<Scene> scene = SceneManager::instance()->get_scene();
    std::shared_ptr<Camera> camera = scene->get_camera();

    if (camera == nullptr)
        throw NoSceneCameraException(__FILE__, typeid(*this).name(), __LINE__);

    camera->processKeywordMovement(_dir);
}

RotateCameraCommand::RotateCameraCommand(CameraRotation dir)
{
    _dir = dir;
}

void RotateCameraCommand::execute()
{
    std::shared_ptr<Scene> scene = SceneManager::instance()->get_scene();
    std::shared_ptr<Camera> camera = scene->get_camera();

    if (camera == nullptr)
        throw NoSceneCameraException(__FILE__, typeid(*this).name(), __LINE__);

    camera->processKeywordRotation(_dir);
}

ZoomCameraCommand::ZoomCameraCommand(CameraZooming dir)
{
    _dir = dir;
}

void ZoomCameraCommand::execute()
{
    std::shared_ptr<Scene> scene = SceneManager::instance()->get_scene();
    std::shared_ptr<Camera> camera = scene->get_camera();

    if (camera == nullptr)
        throw NoSceneCameraException(__FILE__, typeid(*this).name(), __LINE__);

    camera->processMouseScroll(_dir);
}

SetProjectionCommand::SetProjectionCommand(ClipSpaceType type, std::shared_ptr<BaseDrawer> drawer)
{
    _type = type;
    _drawer = drawer;
}

void SetProjectionCommand::execute()
{
    std::shared_ptr<Scene> scene = SceneManager::instance()->get_scene();
    std::shared_ptr<Camera> cameraPtr = scene->get_camera();

    float aspectRatio = float(_drawer->getSceneWidth()) / _drawer->getSceneHeight();
    const float left = -75.f;
    const float right = 75.f;
    const float top = right / aspectRatio;
    const float down = left / aspectRatio;
    const float near = 0.1f;
    const float far = 500.f;

    float oldFov = cameraPtr->getClipSpace()->getFov();
    if (cameraPtr != nullptr)
    {
        std::shared_ptr<ClippingSpace> clipSpace;
        if (_type == ClipSpaceType::PERSPECTIVE)
            clipSpace = std::shared_ptr<ClippingSpace>(new PiramidClippingSpace(oldFov, aspectRatio, near, far));
        else if (_type == ClipSpaceType::ORTHO)
            clipSpace = std::shared_ptr<ClippingSpace>(new RectClippingSpace(left, right, down, top, near, far, oldFov));

        cameraPtr->setClipSpace(clipSpace);
        scene->set_camera(cameraPtr);
    }
}

RespawnCameraCommand::RespawnCameraCommand(ClipSpaceType clipSpaceType, std::shared_ptr<BaseDrawer> drawer)
{
    _clipSpaceType = clipSpaceType;
    _drawer = drawer;
}

void RespawnCameraCommand::execute()
{
    std::shared_ptr<Scene> scene = SceneManager::instance()->get_scene();

    float aspectRatio = float(_drawer->getSceneWidth()) / _drawer->getSceneHeight();
    const float left = -75.f;
    const float right = 75.f;
    const float top = right / aspectRatio;
    const float down = left / aspectRatio;
    const float near = 0.1f;
    const float far = 500.f;

    std::shared_ptr<Camera> cameraPtr = scene->get_camera();
    std::shared_ptr<ClippingSpace> clipSpace;
    if (_clipSpaceType == ClipSpaceType::PERSPECTIVE)
        clipSpace = std::shared_ptr<ClippingSpace>(new PiramidClippingSpace(math<>::radians(45.f), aspectRatio, near, far));
    else if (_clipSpaceType == ClipSpaceType::ORTHO)
        clipSpace = std::shared_ptr<ClippingSpace>(new RectClippingSpace(left, right, down, top, near, far, math<>::radians(45.f)));

    cameraPtr = std::shared_ptr<Camera>(new Camera(clipSpace, vec3<>(-30.f, -30.f, 25.f), vec3<>(0.f, 0.f, 1.0f)));
    scene->set_camera(cameraPtr);
}