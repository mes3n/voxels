#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

Camera::Camera (glm::vec3 start) {
    position = start;

    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    sensitivity = 1.3f;
    speed = 4.0f;

    yaw = 0.0f;
    pitch = 0.0f;

    setFacing(0, 0, 0.0f);
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

void Camera::setFacing (int dx, int dy, float dt) {

    yaw   -= dx * sensitivity * dt;
    pitch += dy * sensitivity * dt;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
    
    // glm::vec3 direction(
    //     cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
    //     sin(glm::radians(pitch)),
    //     sin(glm::radians(yaw)) * cos(glm::radians(pitch))
    // );

    facing = glm::normalize(glm::vec3(
        cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
        sin(glm::radians(pitch)),
        sin(glm::radians(yaw)) * cos(glm::radians(pitch))
    ));
    right = setRight();
    up = setUp();

    forwards = glm::vec3(
        cos(glm::radians(yaw)),
        0.0f,
        sin(glm::radians(yaw))
    );
}

void Camera::moveForwards (float dt) {
    position += forwards*speed*dt;
}
void Camera::moveBackwards (float dt) {
    position -= forwards*speed*dt;
}
void Camera::moveRight (float dt) {
    position += right*speed*dt;
}
void Camera::moveLeft (float dt) {
    position -= right*speed*dt;
}
void Camera::moveUp (float dt) {
    position += worldUp*speed*dt;
}
void Camera::moveDown (float dt) {
    position -= worldUp*speed*dt;
}

glm::mat4 Camera::view (void) const {
    return glm::lookAt(position, target(), up);
}