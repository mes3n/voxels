#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

#ifdef unix
#include <GL/glew.h>
#endif  // unix


class Texture {
    private:
        GLuint _id;
    
    public:
        Texture (const std::string &name);
        ~Texture ();

        void use (void) const;
};

#endif  // TEXTURE_HPP