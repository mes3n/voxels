#ifndef CHUNK_HPP
#define CHUNK_HPP

#ifdef unix
#include <GL/glew.h>
#include <glm/vec3.hpp>
#endif

#include "../graphics/shader.hpp"
#include "../graphics/texture.hpp"

#include "blocks/block.hpp"

#include <vector>

#define CHUNK_HEIGHT 16
#define CHUNK_WIDTH  16
#define CHUNK_DEPTH  16

class Chunk {
    private:
        GLuint _vao;
        int _amount;

        const Shader* _shader;
        const Texture* _texture;

        std::vector<std::vector<std::vector<int>>> _positions;
        std::vector<GLfloat> _vertices;

        void createMesh (void);
    
    public:
        Chunk (const Shader* shader, const Texture* texture);
        ~Chunk ();

        void draw (void) const;

};

#endif  // CHUNK_HPP