#ifndef SCENE_COMMANDS_H
#define SCENE_COMMANDS_H

#include "basecommand.h"

class ConvertSceneObjectsToFrameCommand : public BaseCommand
{
public:
    ConvertSceneObjectsToFrameCommand();

    virtual void execute() override;
};

class ConvertSceneObjectsToPolygonCommand : public BaseCommand
{
public:
    ConvertSceneObjectsToPolygonCommand();

    virtual void execute() override;
};

class UpdateTerrainObjectsCommand : public BaseCommand
{
public:
    UpdateTerrainObjectsCommand();

    virtual void execute() override;
};

class GenerateLightmapsCommand : public BaseCommand
{
public:
    GenerateLightmapsCommand();

    virtual void execute() override;
};

class RemoveTerrainCommand : public BaseCommand
{
public:
    RemoveTerrainCommand();

    virtual void execute() override;
};

class NextLightMapCommand : public BaseCommand
{
public:
    NextLightMapCommand();

    virtual void execute() override;
};

class RemoveTerrainLightmapCommand : public BaseCommand
{
public:
    RemoveTerrainLightmapCommand();

    virtual void execute() override;
};

class SetupLightmapUsingCommand : public BaseCommand
{
public:
    SetupLightmapUsingCommand(bool isUsing);

    virtual void execute() override;

private:
    bool _isUsing;
};

class SetShadowmapUsingCommand : public BaseCommand
{
public:
    SetShadowmapUsingCommand(bool isUsing);

    virtual void execute() override;

private:
    bool _isUsing;
};

#endif