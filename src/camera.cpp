#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

Camera::Camera (glm::vec3 start) {
    position = start;

    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    sensitivity = 0.1f;
    speed = 0.05f;

    yaw = 0.0f;
    pitch = 80.0f;

    setFacing(0, 0);

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

    yaw   -= dx * sensitivity;
    pitch += dy * sensitivity;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
    
    std::cout << yaw << pitch << std::endl;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    facing = glm::normalize(direction);
    right = setRight();
    up = setUp();

    // forwards = glm::normalize(direction - direction.y);
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
void Camera::moveUp (float dt) {
    position += worldUp*speed*dt;
}
void Camera::moveDown (float dt) {
    position -= worldUp*speed*dt;
}

glm::mat4 Camera::view (void) const {
    return glm::lookAt(position, target(), up);
}