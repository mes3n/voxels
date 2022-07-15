#ifndef SKYBOX_HPP
#define SKYBOX_HPP

#include "../graphics/shader.hpp"

#ifdef unix
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#endif  // unix

#include <string>

class Skybox {
    private:
        GLuint _vao;

        GLuint _textureID;
        Shader _shader;

    public:
        Skybox (const std::string &vertPath, const std::string &fragPath, const std::string &textureFolder);

        void update (glm::mat4 view, glm::mat4 projection);
        void draw (void) const;
};

#endif  // SKYBOX_HPP
