#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

Camera::Camera (glm::vec3 start) {
    position = start;

    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    speed = 0.05f;

    facing = glm::vec3(0.0f, 0.0f, 1.0f);
    right = setRight();
    up = setUp();

    yaw = -90.0f;
    pitch = 0.0f;
}

glm::vec3 Camera::target (void) const {
    return position + facing;
}
glm::vec3 Camera::setRight (void) const {
    return glm::normalize(glm::cross(facing, worldUp));
}
glm::vec3 Camera::setUp (void) const {
    return glm::normalize(glm::cross(right, facing));
}

void Camera::setFacing (int dx, int dy) {
    const float sensitivity = 0.1f;

    yaw   -= dx * sensitivity;
    pitch += dy * sensitivity;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    facing = glm::normalize(direction);
    right = setRight();
    up = setUp();
}

void Camera::moveForwards (float dt) {
    position += facing*speed*dt;
}
void Camera::moveBackwards (float dt) {
    position -= facing*speed*dt;
}
void Camera::moveRight (float dt) {
    position += right*speed*dt;
}
void Camera::moveLeft (float dt) {
    position -= right*speed*dt;
}

glm::mat4 Camera::view (void) const {
    return glm::lookAt(position, target(), up);
}