#ifndef CHUNK_HPP
#define CHUNK_HPP

#ifdef unix
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#endif

#include "blocks/cube.hpp"

#include <vector>

class Chunk {
    private:
        int amount;
        GLuint vao;

        // Cube cube;
        GLuint generateModelMatrices (void);
    
    public:
        Chunk ();
        ~Chunk ();

        void use (void) const;

        int getAmount (void) const;

};

#endif  // CHUNK_HPP