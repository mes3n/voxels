#ifndef CHUNK_HPP
#define CHUNK_HPP

#ifdef unix
#include <GL/glew.h>
#endif


class Chunk {
    private:
        int _amount;
        GLuint _vao;

        // Cube cube;
        GLuint generateModelMatrices (void);
    
    public:
        Chunk ();
        ~Chunk ();

        void draw (void) const;

        int getAmount (void) const;

};

#endif  // CHUNK_HPP