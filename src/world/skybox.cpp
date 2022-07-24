#include "skybox.hpp"

#include "blocks/cube_vertices.hpp"

#include <SFML/Graphics/Image.hpp>

#include <iostream>
#include <vector>


static sf::Image loadFromFile (const std::string &name) {
    sf::Image image;

    if (!image.loadFromFile(name)) {
        std::cout << "failed loading texture " << name << std::endl;
    }

    return image;
}

Skybox::Skybox (const std::string &vertPath, const std::string &fragPath, const std::string &textureFolder) 
: _shader(vertPath, fragPath) {

    GLuint vbo;
    
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);

    glBindVertexArray(0);
    glDisableVertexAttribArray(0);

    std::vector<std::string> faces = {
        textureFolder + "right.jpg",
        textureFolder + "left.jpg",
        textureFolder + "top.jpg",
        textureFolder + "bottom.jpg",
        textureFolder + "front.jpg",
        textureFolder + "back.jpg",
    };

    glGenTextures(1, &_textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _textureID);

    for (unsigned int i = 0; i < faces.size(); i++) {
        sf::Image image = loadFromFile(faces[i]);

        glTexImage2D(
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, image.getSize().x, 
            image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr()
        );
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void Skybox::update (glm::mat4 view, glm::mat4 projection) {

    view = glm::mat4(glm::mat3(view));

    _shader.use();
    _shader.setMat4("view", view);
    _shader.setMat4("projection", projection);

}

void Skybox::draw (void) const {
    glDepthMask(GL_FALSE);

    _shader.use();
    glBindTexture(GL_TEXTURE_CUBE_MAP, _textureID);

    glBindVertexArray(_vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    glDepthMask(GL_TRUE);
}