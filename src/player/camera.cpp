#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>


Camera::Camera (glm::vec3 origin) 
: _worldUp(glm::vec3(0.0f, 1.0f, 0.0f)) {
    _position = origin;

    _sensitivity = 1.3f;
    _speed = 4.0f;

    _yaw = 0.0f;
    _pitch = 0.0f;

    setFacing(0, 0, 0.0f);
}

glm::vec3 Camera::target (void) const {
    return _position + _facing;
}
glm::vec3 Camera::setRight (void) const {
    return glm::normalize(glm::cross(_facing, _worldUp));
}
glm::vec3 Camera::setUp (void) const {
    return glm::normalize(glm::cross(_right, _facing));
}

void Camera::setFacing (int dx, int dy, float dt) {

    _yaw   -= dx * _sensitivity * dt;
    _pitch += dy * _sensitivity * dt;

    if (_pitch > 89.0f)
        _pitch = 89.0f;
    if (_pitch < -89.0f)
        _pitch = -89.0f;

    _facing = glm::normalize(glm::vec3(
        cos(glm::radians(_yaw)) * cos(glm::radians(_pitch)),
        sin(glm::radians(_pitch)),
        sin(glm::radians(_yaw)) * cos(glm::radians(_pitch))
    ));
    _right = setRight();
    _up = setUp();

    _forwards = glm::vec3(
        cos(glm::radians(_yaw)),
        0.0f,
        sin(glm::radians(_yaw))
    );
}

void Camera::move (float vx, float vy, float vz, float dt) {
    glm::vec3 velocity;
    if (vx || vz) {
        velocity = glm::normalize(_forwards*vx + _right*vz) + _worldUp*vy;
    }
    else {
        velocity = _worldUp*vy;
    }

    _position += velocity*_speed*dt;
}

void Camera::move (glm::vec3 v, float dt) {
    glm::vec3 velocity;
    if (v.x || v.z) {
        velocity = glm::normalize(_forwards*v.x + _right*v.z) + _worldUp*v.y;
    }
    else {
        velocity = _worldUp*v.y;
    }    
    _position += velocity*_speed*dt;
}

glm::mat4 Camera::getView (void) const {
    return glm::lookAt(_position, target(), _up);
}

glm::vec3 Camera::getPosition (void) const {
    return _position;
}