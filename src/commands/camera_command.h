#ifndef CAMERA_COMMAND_H
#define CAMERA_COMMAND_H

#include "commands/basecommand.h"
#include "primitives/camera.h"
#include "graphics/graphicsfactory.h"

class CameraCommand : public BaseCommand
{
public:
    CameraCommand();
};

class MoveCameraCommand : public CameraCommand
{
public:
    MoveCameraCommand(CameraMovement dir);

    void execute() override;

private:
    CameraMovement _dir;
};

class RotateCameraCommand : public CameraCommand
{
public:
    RotateCameraCommand(CameraRotation dir);

    void execute() override;

private:
    CameraRotation _dir;
};

class ZoomCameraCommand : public CameraCommand
{
public:
    ZoomCameraCommand(CameraZooming dir);

    void execute() override;

private:
    CameraZooming _dir;
};

class SetProjectionCommand : public CameraCommand
{
public:
    SetProjectionCommand(ClipSpaceType type, std::shared_ptr<BaseDrawer> drawer);

    void execute() override;

private:
    ClipSpaceType _type;
    std::shared_ptr<BaseDrawer> _drawer;
};

class RespawnCameraCommand : public CameraCommand
{
public:
    RespawnCameraCommand(ClipSpaceType clipSpaceType, std::shared_ptr<BaseDrawer> drawer);

    virtual void execute() override;

private:
    ClipSpaceType _clipSpaceType;
    std::shared_ptr<BaseDrawer> _drawer;
};

#endif // CAMERA_COMMAND_H
