#ifndef WORLD_HPP
#define WORLD_HPP

#include "chunk.hpp"

#include "../graphics/shader.hpp"
#include "../graphics/texture.hpp"

#ifdef unix
#include <GL/glew.h>
#include <glm/vec3.hpp>
#endif  // unix

#include <vector>

class Terrain {
    private:
        unsigned int _amount;
        GLuint _instanceVBO;
        GLuint _vao;

        const Shader* _shader;
        const Texture* _texture;

        void bindModelMatrices (std::vector<glm::vec3> offsets);

    public:
        Terrain (const Shader* shader, const Texture* texture, std::vector<glm::vec3> offsets);
        ~Terrain ();

        void draw (void) const;

};

#endif  // WORLD_HPP
