#ifndef DRAWCOMMAND_H
#define DRAWCOMMAND_H

#include "commands/basecommand.h"

#include "graphics/graphicsfactory.h"
#include "primitives/clipping_space.h"
#include "shaders/shader_types.h"

class BaseDrawCommand : public BaseCommand
{
public:
    BaseDrawCommand(std::shared_ptr<BaseDrawer> drawer);

protected:
    std::shared_ptr<BaseDrawer> _drawer;
};

class UpdateScreenCommand : public BaseDrawCommand
{
public:
    UpdateScreenCommand(std::shared_ptr<BaseDrawer> drawer);

    virtual void execute() override;
};


class MainDrawCommand : public BaseDrawCommand
{
public:
    MainDrawCommand(std::shared_ptr<BaseDrawer> drawer, ClipSpaceType clipSpaceType);

    virtual void execute() override;

private:
    ClipSpaceType _clipSpaceType;
};

class SetupShadowDrawCommand : public BaseDrawCommand
{
public:
    SetupShadowDrawCommand(std::shared_ptr<BaseDrawer> drawer);

    virtual void execute() override;
};

class LightmapDrawCommand : public BaseDrawCommand
{
public:
    LightmapDrawCommand(std::shared_ptr<BaseDrawer> drawer);

    virtual void execute() override;
};


class HeightmapDrawCommand : public BaseDrawCommand
{
public:
    HeightmapDrawCommand(std::shared_ptr<BaseDrawer> drawer);

    virtual void execute() override;
};


class CloseViewportCommand : public BaseDrawCommand
{
public:
    CloseViewportCommand(std::shared_ptr<BaseDrawer> drawer);

    virtual void execute() override;
};

class SetFragmentShaderCommand : public BaseDrawCommand
{
public:
    SetFragmentShaderCommand(std::shared_ptr<BaseDrawer> drawer, ShaderType shaderType);

    virtual void execute() override;

private:
    ShaderType _shaderType;
};

class ResizeDrawerCommand : public BaseDrawCommand
{
public:
    ResizeDrawerCommand(std::shared_ptr<BaseDrawer> drawer, size_t width, size_t height);

    virtual void execute() override;

private:
    size_t _width, _height;
};

class SetBackgroundColorCommand : public BaseDrawCommand
{
public:
    SetBackgroundColorCommand(std::shared_ptr<BaseDrawer> drawer, vec3<> color);

    virtual void execute() override;

private:
    vec3<> _color;
};

class SetDefaultLinesColorCommand : public BaseDrawCommand
{
public:
    SetDefaultLinesColorCommand(std::shared_ptr<BaseDrawer> drawer, vec3<> color);

    virtual void execute() override;

private:
    vec3<> _color;
};

#endif // DRAWCOMMAND_H
