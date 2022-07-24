#ifndef CHUNK_HPP
#define CHUNK_HPP

#ifdef unix
#include <GL/glew.h>
#include <glm/vec3.hpp>
#endif

#include "../graphics/shader.hpp"
#include "../graphics/texture.hpp"

#include "blocks/block.hpp"

#include <vector>


class Chunks {
    private:

        std::vector<std::vector<std::vector<int>>> _allPositions;

        std::vector<GLfloat> _drawnVertices;
        std::vector<glm::vec3> _drawnPositions;

        void createMesh (void);
    
    public:
        Chunks ();

        std::vector<glm::vec3> getPositions (void) const;

};

#endif  // CHUNK_HPP