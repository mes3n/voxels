#include "chunk.hpp"

#ifdef unix
#include <glm/vec3.hpp>
#endif

#include "blocks/cubeVertices.hpp"

#include <iostream>


Chunk::Chunk () {

    GLuint instanceVBO = generateModelMatrices();

    GLuint cubeVBO;

    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &cubeVBO);

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(1);    
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);
    glVertexAttribDivisor(2, 1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
    // glDisableVertexAttribArray(0);
    // glDisableVertexAttribArray(1);
    // glDisableVertexAttribArray(2);

}

Chunk::~Chunk () {
    glDeleteVertexArrays(1, &_vao);
}


GLuint Chunk::generateModelMatrices (void) {
    int width, height, depth;
    width = 200;
    height = 10;
    depth = 200;

    _amount = width*height*depth;
    unsigned int count = 0;

    glm::vec3* offsets = new glm::vec3[_amount];

    for (int x = (int)-width/2; x < (int)width/2; x++) {
        for (int y = 1-height; y < 1; y++) {
            for (int z = (int)-depth/2; z < (int)depth/2; z++) {

                glm::vec3 offset = glm::vec3(
                    1.0f * x, 1.0f * y, 1.0f * z
                );

                offsets[count++] = offset;

            }
        }
    }

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, _amount * sizeof(glm::vec3), offsets, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    delete[] offsets;

    return vbo;
}

int Chunk::getAmount (void) const {
    return _amount;
}

void Chunk::draw (void) const {
    glBindVertexArray(_vao);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, _amount);
    glBindVertexArray(0);
}
