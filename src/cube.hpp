#ifndef CUBE_HPP
#define CUBE_HPP

#ifdef unix
#include <GL/glew.h>
#endif  // unix


class Cube {
    private:
        GLuint vbo;
        GLuint vao;
    
    public:
        Cube ();

        void use (void) const;        

};

#endif  // CUBE_HPP