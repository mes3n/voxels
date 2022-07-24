#include "world.hpp"

#include "blocks/cube_vertices.hpp"

Terrain::Terrain (const Shader* shader, const Texture* texture, std::vector<glm::vec3> offsets) 
: _shader(shader), _texture(texture) {


    GLuint cubeVBO;

    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &cubeVBO);

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(texturedCubeVertices), texturedCubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(1);    
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    bindModelMatrices(offsets);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

Terrain::~Terrain () {
    glDeleteVertexArrays(1, &_vao);
}


void Terrain::bindModelMatrices (std::vector<glm::vec3> offsets) {

    _amount = offsets.size();

    glBindVertexArray(_vao);

    glGenBuffers(1, &_instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, _instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, _amount * sizeof(glm::vec3), &offsets[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(2, 1);

    glBindVertexArray(0);

}

void Terrain::draw (void) const {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(3.0f);

    _shader->use();
    _texture->use();

    glBindVertexArray(_vao);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, _amount);
    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D, 0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}