#ifndef CAMERA_HPP
#define CAMERA_HPP

#ifdef unix
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#endif  // unix


class Camera {
    private:
        glm::vec3 _position;
        glm::vec3 _facing;  // pitch and yaw rotation
        glm::vec3 _forwards;  // yaw rotation
        glm::vec3 _right;
        glm::vec3 _up;
        
        const glm::vec3 _worldUp;
        float _sensitivity;
        float _speed;

        float _yaw, _pitch;

        glm::vec3 setRight (void) const;
        glm::vec3 setUp (void) const;

        glm::vec3 target (void) const;
        
    public:
        Camera (glm::vec3 origin);

        void setFacing (int dx, int dy, float dt);

        void move (float vx, float vy, float vz, float dt);
        void move (glm::vec3 v, float dt);

        glm::mat4 getView (void) const;
        glm::vec3 getPosition (void) const;

};  

#endif  // CAMERA_HPP