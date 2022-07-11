#include "texture.hpp"

#include <iostream>


sf::Image loadFromFile (const std::string &name) {
    sf::Image image;

    if (!image.loadFromFile(name)) {
        std::cout << "failed loading texture" << std::endl;
    }

    return image;
}

GLuint loadFromImage (sf::Image image, GLenum type) {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(type, texture);
    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(type, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
    glGenerateMipmap(type);

    return texture;
}

Texture::Texture (const std::string &name, GLenum type) {
    sf::Image image = loadFromFile(name);
    _texture = loadFromImage(image, type);
    _target = type;
    
}

Texture::~Texture () {
    glDeleteTextures(1, &_texture);
}

void Texture::use (void) const {
    glBindTexture(_target, _texture);
}