#include "chunk.hpp"

#include "blocks/cube_vertices.hpp"

#include <iostream>

typedef long unsigned int luint;

static bool inside(glm::vec3 normalCube, glm::vec3 position) {
    static const float cubeSide = 0.5f;

    glm::vec3 offset = position - normalCube;

    if (!(-cubeSide < offset.x && offset.x < cubeSide))
        return false;
    if (!(-cubeSide < offset.y && offset.y < cubeSide))
        return false;
    if (!(-cubeSide < offset.z && offset.z < cubeSide))
        return false;
    return true;
}

Chunks::Chunks () 
: _allPositions(256, std::vector<std::vector<int>> (16, std::vector<int> (16, 0))) { 

    for (luint y = 0; y < 16; y++) {
        for (luint x = 0; x < 16; x++) {
            for (luint z = 0; z < 16; z++) {
                _allPositions[y][x][z] = 1;
            }
        }
    }
    createMesh();
}

void Chunks::createMesh (void) {
    std::vector<glm::vec3> surrounding = {
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, -1.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(-1.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
    };

    for (luint y = 0; y < _allPositions.size(); y++) {
        for (luint x = 0; x < _allPositions[y].size(); x++) {
            for (luint z = 0; z < _allPositions[y][x].size(); z++) {
                if (_allPositions[y][x][z]) {                    
                    _drawnPositions.push_back(glm::vec3(x, y, z));
                }
            }
        }
    }
}

std::vector<glm::vec3> Chunks::getPositions(void) const {
    return _drawnPositions;
}
