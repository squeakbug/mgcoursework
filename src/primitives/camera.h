#ifndef CAMERA_H
#define CAMERA_H

#include <memory>

#include "primitives/sceneobject.h"
#include "primitives/clipping_space.h"

enum class CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    DOWN,
    UP
};

enum class CameraRotation
{
    LEFT,
    RIGHT,
    DOWN,
    UP
};

enum class CameraZooming
{
    CLOSER,
    FURTHER
};

class Camera : public SceneObject
{
public:
    /* Что это за магические числа??? */
    Camera(std::shared_ptr<ClippingSpace> clipSpace, float yaw, float pitch, const vec3<> &pos = vec3<>(0.f, 0.f, 0.f),
           const vec3<> up = vec3<>(0.0f, 0.f, 0.f));

    /* Что это за магические числа??? */
    Camera(std::shared_ptr<ClippingSpace> clipSpace, const vec3<> &pos = vec3<>(0.f, 0.f, 0.f),
           const vec3<> up = vec3<>(0.f, 0.f, 0.f));

    const std::shared_ptr<ClippingSpace> getClipSpace();
    void setClipSpace(std::shared_ptr<ClippingSpace> clipSpace);
    void setProjMatrix(const mat4<> projMatrix);

    mat4<> getViewMatrix();
    mat4<> getProjMatrix();

    void processKeywordMovement(CameraMovement direction);
    void processKeywordRotation(CameraRotation direction);
    void processMouseScroll(CameraZooming direction);

    void accept(Visitor &visitor) override;

private:
    void updateCameraVectors();
    void updateProjection();

    void processMouseMovement(float xoffset, float yoffset);

public:
    vec3<> _pos;
    vec3<> _forward;
    vec3<> _unNormalizedUp;
    vec3<> _up;
    vec3<> _right;

    mat4<> _projMatrix;
    std::shared_ptr<ClippingSpace> _clipSpace;

    float _mouseScrollSensitivity   = { 0.01f };
    float _mouseSensitivity         = { 0.1f };
    float _movementSpeed            = { 2.5f };
    float _yaw                      = { 45.f };    // Рысканье
    float _pitch                    = { -45.f };   // Тангаж
};

#endif // CAMERA_H
