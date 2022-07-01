#ifndef SHADER_H
#define SHADER_H

#ifdef unix
#include <GL/glew.h>
#endif  // unis

void loadShader(const char* path, GLenum type, GLuint program);

#endif  // SHADER_H