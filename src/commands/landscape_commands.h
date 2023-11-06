#ifndef LANDSCAPE_COMMANDS_H
#define LANDSCAPE_COMMANDS_H

#include <cstddef>
#include <string>

#include "enums.h"
#include "commands/basecommand.h"

#include "terrain/generators/dsgenerator.h"
#include "terrain/generators/mdsgenerator.h"
#include "terrain/generators/pngenerator.h"
#include "terrain/grid_savers/file_grid_saver.h"
#include "terrain/terrainblock.h"

#include "painter/gradient.h"


class UpdadeLandscapeCommand : public  BaseCommand
{
public:
    UpdadeLandscapeCommand();

    virtual void execute() override;

protected:
    std::shared_ptr<TerrainBlock> _terrain;
    std::shared_ptr<Scene> _scene;
};

class AddFrameLandscapeCommand : public UpdadeLandscapeCommand
{
public:
    AddFrameLandscapeCommand();

    virtual void execute() override;
};

class AddPolygonLandscapeCommand : public UpdadeLandscapeCommand
{
public:
    AddPolygonLandscapeCommand();

    virtual void execute() override;
};

class FormLandscapeCommand : public  BaseCommand
{
public:
    FormLandscapeCommand(std::size_t height, std::size_t width);

protected:
    std::size_t _width;
    std::size_t _height;
};


class FormMDSLandscapeCommand : public  FormLandscapeCommand
{
public:
    FormMDSLandscapeCommand(std::size_t height, std::size_t width, float roughness, float delta, const CornerHeights &heights);

    virtual void execute() override;

private:
    float _roughness;
    float _delta;
    CornerHeights _heights;
};


class FormPNLandscapeCommand : public  FormLandscapeCommand
{
public:
    FormPNLandscapeCommand(std::size_t height, std::size_t width, std::size_t octavesCnt);

    virtual void execute() override;

private:
    std::size_t _octavesCnt;
};


class FormDSLandscapeCommand : public  FormLandscapeCommand
{
public:
    FormDSLandscapeCommand(std::size_t height, std::size_t width, float roughness, float delta, SurfaceType type, const CornerHeights &heights);

    virtual void execute() override;

private:
    float _roughness;
    float _delta;
    CornerHeights _heights;
    SurfaceType _type;
};

class SaveLandscapeToFile : public  BaseCommand
{
public:
    SaveLandscapeToFile(std::string filename, EImageFileExtension ext);

    virtual void execute() override;

private:
    std::string _filename;
    EImageFileExtension _ext;
};

class LoadLandscapeFromFile : public  BaseCommand
{
public:
    LoadLandscapeFromFile(std::string filename);

    virtual void execute() override;

private:
    std::string _filename;
};

class SetMaxLandscapeHeightCommand : public  BaseCommand
{
public:
    SetMaxLandscapeHeightCommand(float height);

    virtual void execute() override;

private:
    float _height;
};

class SetLandscapeWaterLevelCommand : public  BaseCommand
{
public:
    SetLandscapeWaterLevelCommand(float waterLevel);

    virtual void execute() override;

private:
    float _waterLevel;
};

class SetWaterStateCommand : public  BaseCommand
{
public:
    SetWaterStateCommand(bool isRequired);

    virtual void execute() override;

private:
    bool _isRequired;
};

class SetWaterRenderCommand : public  BaseCommand
{
public:
    SetWaterRenderCommand(bool isEnable);

    virtual void execute() override;

private:
    float _isEnable;
};

class DeformLandscapeCommand : public  BaseCommand
{
public:
    // @value changes from 0.0 to 1.0
    DeformLandscapeCommand(float value);

    virtual void execute() override;

private:
    float _value;
};

class SetLandscapeMaskCommand : public  BaseCommand
{
public:
    SetLandscapeMaskCommand();
    SetLandscapeMaskCommand(size_t kernelRadius, size_t repeatCnt);

protected:
    size_t _kernelRadius { 2 };
    size_t _repeatCnt { 1 };
};

class SetRandomLandscapeMaskCommand : public  SetLandscapeMaskCommand
{
public:
    SetRandomLandscapeMaskCommand();

    virtual void execute() override;
};

class SetTorusLandscapeMaskCommand : public  SetLandscapeMaskCommand
{
public:
    SetTorusLandscapeMaskCommand();

    virtual void execute() override;
};

class SetHillLandscapeMaskCommand : public  SetLandscapeMaskCommand
{
public:
    SetHillLandscapeMaskCommand();

    virtual void execute() override;
};

class SetupLandscapeGradientCommand : public BaseCommand
{
public:
    SetupLandscapeGradientCommand(std::shared_ptr<Gradient> gradient);

    virtual void execute() override;

private:
    std::shared_ptr<Gradient> _gradient;
};


#endif // LANDSCAPE_COMMANDS_H
