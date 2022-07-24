#ifndef BLOCK_HPP
#define BLOCK_HPP

#ifdef unix
#include <GL/glew.h>
#include <glm/vec3.hpp>
#endif  // unix

#include <vector>


class Block {
    private:
        std::vector<int> _surroundingIndexes;
        glm::vec3 _position;

    public:
        Block (std::vector<int> surroundingIndexes, glm::vec3 position);

        std::vector<GLfloat> exposedFaces (void) const;

};

#endif  // BLOCK_HPP
