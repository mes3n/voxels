#include "print_info.hpp"

#include <iostream>
#include <iomanip>

void print_info (glm::vec3 pos, float fps) {

    std::cout << std::fixed << std::setprecision(2) << "\n";
    
    std::cout << "player position: " << pos.x << ", " << pos.y << ", " << pos.z << "\n";
    std::cout << "fps: " << fps << "\n";

    std::cout << "\u001b[1000D\u001b[3A";

}
