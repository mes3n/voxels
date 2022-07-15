#ifndef PRINT_INFO_HPP
#define PRINT_INFO_HPP

#ifdef unix
#include <glm/vec3.hpp>
#endif  // unix

#include <string>

void print_info (glm::vec3 pos, float fps);

#endif  // PRINT_INFO_HPP
