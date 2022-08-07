#include "chunk.hpp"

#include "blocks/cube_vertices.hpp"

#include <iostream>

typedef long unsigned int luint;


Chunk::Chunk (const Shader* shader, const Texture* texture) 
: _positions(CHUNK_WIDTH, std::vector<std::vector<int>> (CHUNK_HEIGHT, std::vector<int> (CHUNK_DEPTH, 0))),
_shader(shader), _texture(texture) { 

    for (luint x = 0; x < CHUNK_WIDTH; x++) {
        for (luint y = 0; y < CHUNK_HEIGHT; y++) {
            for (luint z = 0; z < CHUNK_DEPTH; z++) {
                _positions[x][y][z] = 1;
            }
        }
    }

    _amount = 0;
    createMesh();

    GLuint vbo;
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, _vertices.size()*sizeof(GLfloat), &_vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(1);    
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

}

Chunk::~Chunk () {
    glDeleteVertexArrays(1, &_vao);
}

void Chunk::draw (void) const {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(3.0f);

    _shader->use();
    _texture->use();
    
    glBindVertexArray(_vao);
    glDrawArrays(GL_TRIANGLES, 0, _amount);
    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D, 0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Chunk::createMesh (void) {
    for (luint x = 0; x < CHUNK_WIDTH; x++) {
        for (luint y = 0; y < CHUNK_HEIGHT; y++) {
            for (luint z = 0; z < CHUNK_DEPTH; z++) {
                std::cout << x << ", " << y << ", " << z << ": " << std::flush;

                if (_positions[x][y][z]) {
                    std::vector<unsigned int> faces;
                    if (y <= 0) 
                        faces.push_back(BOTTOM);
                    else if (_positions[x][y-1][z] == 0)                 
                        faces.push_back(BOTTOM);

                    if (y >= CHUNK_HEIGHT - 1) 
                        faces.push_back(TOP);
                    else if (_positions[x][y+1][z] == 0)                 
                        faces.push_back(TOP);

                    if (x <= 0) 
                        faces.push_back(LEFT);
                    else if (_positions[x-1][y][z] == 0)                 
                        faces.push_back(LEFT);

                    if (x >= CHUNK_WIDTH - 1) 
                        faces.push_back(RIGHT);
                    else if (_positions[x+1][y][z] == 0)                 
                        faces.push_back(RIGHT);

                    if (z <= 0) 
                        faces.push_back(BACK);
                    else if (_positions[x][y][z-1] == 0)                 
                        faces.push_back(BACK);

                    if (z >= CHUNK_DEPTH - 1) 
                        faces.push_back(FRONT);
                    else if (_positions[x][y][z+1] == 0)                 
                        faces.push_back(FRONT);

                    for (unsigned int face : faces) {
                        std::cout << face << ", ";
                        for (luint i = 0; i < 30; i++) {
                            if (i % 5 == 0)
                                _vertices.push_back(texturedCubeFaces[face][i] + (GLfloat)x);
                            else if (i % 5 == 1)
                                _vertices.push_back(texturedCubeFaces[face][i] + (GLfloat)y);
                            else if (i % 5 == 2)
                                _vertices.push_back(texturedCubeFaces[face][i] + (GLfloat)z);
                            else
                                _vertices.push_back(texturedCubeFaces[face][i]);
                        }
                        _amount += 6;
                    }

                    std::cout << std::endl;
                }
            }
        }
    }
    std::cout << _amount << ", " << _vertices.size() << std::endl;

}
