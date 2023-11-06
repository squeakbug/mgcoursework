#include "primitives/camera.h"
#include "primitives/sceneobject.h"

#include <iostream>

Camera::Camera(std::shared_ptr<ClippingSpace> clipSpace, float yaw, float pitch, const vec3<> &pos, const vec3<> up)
{
    _pos = pos;
    _unNormalizedUp = up;
    _yaw = yaw;
    _pitch = pitch;

    _clipSpace = clipSpace;

    updateProjection();
    updateCameraVectors();
}

Camera::Camera(std::shared_ptr<ClippingSpace> clipSpace, const vec3<> &pos, const vec3<> up)
{
    _pos = pos;
    _unNormalizedUp = up;

    _clipSpace = clipSpace;

    updateProjection();
    updateCameraVectors();
}

const std::shared_ptr<ClippingSpace> Camera::getClipSpace()
{
    return _clipSpace;
}

void Camera::setClipSpace(std::shared_ptr<ClippingSpace> clipSpace)
{
    _clipSpace = clipSpace;
    updateProjection();
}

void Camera::setProjMatrix(const mat4<> projMatrix)
{
    _projMatrix = projMatrix;
}

mat4<> Camera::getViewMatrix()
{
    return math<>::lookAt(_pos, _pos + _forward, _up);
}

mat4<> Camera::getProjMatrix()
{
    return _projMatrix;
}

void Camera::processKeywordMovement(CameraMovement direction)
{
    float velocity = _movementSpeed;

    if (direction == CameraMovement::BACKWARD)
        _pos -= _forward * velocity;
    if (direction == CameraMovement::FORWARD)
        _pos += _forward * velocity;
    if (direction == CameraMovement::LEFT)
        _pos -= _right * velocity;
    if (direction == CameraMovement::RIGHT)
        _pos += _right * velocity;
    if (direction == CameraMovement::DOWN)
        _pos -= _up * velocity;
    if (direction == CameraMovement::UP)
        _pos += _up * velocity;
}

void Camera::processKeywordRotation(CameraRotation direction)
{
    const float defaultShift = 10.f;

    if (direction == CameraRotation::UP)
        processMouseMovement(0.f, defaultShift);
    else if (direction == CameraRotation::DOWN)
        processMouseMovement(0.f, -defaultShift);
    else if (direction == CameraRotation::RIGHT)
        processMouseMovement(-defaultShift, 0.f);
    else if (direction == CameraRotation::LEFT)
        processMouseMovement(defaultShift, 0.f);
}

void Camera::processMouseMovement(float xoffset, float yoffset)
{
    xoffset *= _mouseSensitivity;
    yoffset *= _mouseSensitivity;

    _yaw   += xoffset;
    _pitch += yoffset;

    const float maxPitch = 89.f;
    const float minPitch = -89.f;

    if (_pitch > maxPitch)
        _pitch = maxPitch;
    if (_pitch < minPitch)
        _pitch = minPitch;

    updateCameraVectors();
}

void Camera::processMouseScroll(CameraZooming direction)
{
    float offset = direction == CameraZooming::CLOSER ? _mouseScrollSensitivity : -_mouseScrollSensitivity;
    float minFov = _clipSpace->getMinFov();
    float maxFov = _clipSpace->getMaxFov();
    float fov = _clipSpace->getFov();

    if (fov >= minFov && fov <= maxFov)
        fov -= offset;
    if (fov < minFov)
        fov = minFov;
    if (fov > maxFov)
        fov = maxFov;

    _clipSpace->setFov(fov);
    updateProjection();
}

void Camera::accept(Visitor &visitor)
{
    visitor.visit(*this);
}

void Camera::updateCameraVectors()
{
    vec3<> front;
    front.x = cos(math<>::radians(_yaw)) * cos(math<>::radians(_pitch));
    front.y = sin(math<>::radians(_yaw)) * cos(math<>::radians(_pitch));
    front.z = sin(math<>::radians(_pitch));
    _forward = math<>::normalize(front);

    _right = math<>::normalize(math<>::cross(_forward, math<>::normalize(_unNormalizedUp)));
    _up    = math<>::normalize(math<>::cross(_right, _forward));
}

void Camera::updateProjection()
{
    _projMatrix = _clipSpace->getProjMatrix();
}
