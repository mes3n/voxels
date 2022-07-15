#ifndef CHUNK_HPP
#define CHUNK_HPP

#ifdef unix
#include <GL/glew.h>
#endif

#include "../graphics/shader.hpp"
#include "../graphics/texture.hpp"


class Chunk {
    private:
        int _amount;
        GLuint _vao;

        const Shader* _shader;
        const Texture* _texture;

        GLuint generateModelMatrices (void);
    
    public:
        Chunk (const Shader* shader, const Texture* texture);
        ~Chunk ();

        void draw (void) const;

};

#endif  // CHUNK_HPP