#include "texture.hpp"

#include <iostream>
#include <SFML/Graphics/Image.hpp>


static sf::Image loadFromFile (const std::string &name) {
    sf::Image image;

    if (!image.loadFromFile(name)) {
        std::cout << "failed loading texture " << name << std::endl;
    }

    return image;
}

static GLuint loadFromImage (sf::Image image, GLenum type) {
    GLuint id;
    glGenTextures(1, &id);
    glBindTexture(type, id);

    glTexImage2D(type, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glGenerateMipmap(type);

    return id;
}

Texture::Texture (const std::string &name) {
    sf::Image image = loadFromFile(name);
    _id = loadFromImage(image, GL_TEXTURE_2D);
    
}

Texture::~Texture () {
    glDeleteTextures(1, &_id);
}

void Texture::use (void) const {
    glBindTexture(GL_TEXTURE_2D, _id);
}