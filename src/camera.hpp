#ifndef CAMERA_HPP
#define CAMERA_HPP

#ifdef unix
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#endif  // unix


class Camera {
    private:
        glm::vec3 position;
        glm::vec3 facing;
        glm::vec3 right;
        glm::vec3 up;

        glm::vec3 worldUp;
        float speed;

        glm::vec3 setRight (void) const;
        glm::vec3 setUp (void) const;

        glm::vec3 target (void) const;

        float yaw, pitch;

    public:
        Camera (glm::vec3 start);

        void setFacing (int dx, int dy);

        void moveForwards (float dt);
        void moveBackwards (float dt);
        void moveRight (float dt);
        void moveLeft (float dt);

        glm::mat4 view (void) const;
};  

#endif  // CAMERA_HPP