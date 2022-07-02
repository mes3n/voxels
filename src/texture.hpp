#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

#ifdef unix
#include <GL/glew.h>
#endif  // unix

#include <SFML/Graphics/Image.hpp>

class Texture {
    private:
        GLuint texture;
        GLenum target;
    
    public:
        Texture (const std::string &name, GLenum);
        void use (void) const;
};

#endif  // TEXTURE_HPP