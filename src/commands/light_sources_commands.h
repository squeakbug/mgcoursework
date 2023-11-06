#ifndef LIGHT_SOURCE_COMMANDS_H
#define LIGHT_SOURCE_COMMANDS_H

#include "base_objects/vector3f.h"
#include "commands/basecommand.h"

class AddNewLightSourceCommand : public BaseCommand
{
public:
    AddNewLightSourceCommand(vec3<> color, float ambient, float diffuse, float specular, bool state);

protected:
    vec3<> _color;
    float _ambient;
    float _diffuse;
    float _specular;
    bool _state;
};

class AddNewDirectLightSourceCommand : public AddNewLightSourceCommand
{
public:
    AddNewDirectLightSourceCommand(vec3<> color, float ambient, float diffuse, float specular, bool state, vec3<> direction);

    virtual void execute() override;

private:
    vec3<> _direction;
};

class EditLightSourceCommand : public BaseCommand
{
public:
    EditLightSourceCommand(vec3<> newColor, float newAmbient, float newDiffuse, float newSpecular, size_t indx);

protected:
    vec3<> _color;
    float _ambient;
    float _diffuse;
    float _specular;
    size_t _indx;
};

class EditLightSourceColorCommand : public BaseCommand
{
public:
    EditLightSourceColorCommand(vec3<> newColor, size_t indx);

    virtual void execute() override;

protected:
    vec3<> _color;
    size_t _indx;
};

class EditDirectLightSourceCommand : public EditLightSourceCommand
{
public:
    EditDirectLightSourceCommand(float newAmbient, float newDiffuse, float newSpecular, size_t indx, vec3<> newDirection);
    EditDirectLightSourceCommand(vec3<> newColor, float newAmbient, float newDiffuse, float newSpecular, size_t indx, vec3<> newDirection);

    virtual void execute() override;

private:
    bool _isColorEdit;
    vec3<> _direction;
};

class RemoveLightSourceCommand : public BaseCommand
{
public:
    RemoveLightSourceCommand(size_t indx);

    virtual void execute() override;

private:
    size_t _indx;
};

class EnableLightSourceCommand : public BaseCommand
{
public:
    EnableLightSourceCommand(size_t indx);

    virtual void execute() override;

private:
    size_t _indx;
};

class DisableLightSourceCommand : public BaseCommand
{
public:
    DisableLightSourceCommand(size_t indx);

    virtual void execute() override;

private:
    size_t _indx;
};

class SelectLightSourceDataCommand : public BaseCommand
{
public:
    SelectLightSourceDataCommand(size_t indx, vec3<> &color, float &ambient, float &diffuse, float &specular);

protected:
    size_t _indx;
    vec3<> &_color;
    float &_ambient;
    float &_diffuse;
    float &_specular;
};

class SelectDirectLightSourceDataCommand : public SelectLightSourceDataCommand
{
public:
    SelectDirectLightSourceDataCommand(size_t indx, vec3<> &color, float &ambient, float &diffuse, float &specular, vec3<> &direction);

    virtual void execute() override;

private:
    vec3<> &_direction;
};

class UpdateFragmentShadersLightMapSourcesCommand : public BaseCommand
{
public:
    UpdateFragmentShadersLightMapSourcesCommand();

    virtual void execute() override;
};

class UpdateShadowmapPoolCommand : public BaseCommand
{
public:
    UpdateShadowmapPoolCommand();

    virtual void execute() override;
};

#endif