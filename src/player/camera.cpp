#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>


Camera::Camera (glm::vec3 start) {
    position = start;

    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    sensitivity = 1.3f;
    speed = 4.0f;

    yaw = -45.0f;
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

    // yaw = 0;
    // pitch = 0;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

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

void Camera::move (float vx, float vy, float vz, float dt) {
    glm::vec3 velocity;
    if (vx || vz) {
        velocity = glm::normalize(forwards*vx + right*vz) + worldUp*vy;
    }
    else {
        velocity = worldUp*vy;
    }

    position += velocity*speed*dt;
}

void Camera::move (glm::vec3 v, float dt) {
    glm::vec3 velocity;
    if (v.x || v.z) {
        velocity = glm::normalize(forwards*v.x + right*v.z) + worldUp*v.y;
    }
    else {
        velocity = worldUp*v.y;
    }    
    position += velocity*speed*dt;
}

glm::mat4 Camera::getView (void) const {
    return glm::lookAt(position, target(), up);
}