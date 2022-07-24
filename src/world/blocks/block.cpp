#include "block.hpp"

Block::Block (std::vector<int> surroundingIndexes, glm::vec3 position) {
    _surroundingIndexes = surroundingIndexes;
    _position = position;
}

std::vector<GLfloat> Block::exposedFaces (void) const {

}