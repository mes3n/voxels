#include <fstream>
#include <string>
#include <iostream>
#include <vector>

#include <GL/glew.h>


std::string readFile(const char* path) {
    std::string content;
    std::fstream file(path, std::ios::in);

    if (!file.is_open()) {
        std::cerr << "Could not read file " << path << ". File does not exist." << std::endl;
        return "";
    }
    std::string line = "";
    while (!file.eof()) {
        std::getline(file, line);
        content.append(line + "\n");
    }

    file.close();
    return content;
}

void loadShader(const char* path, GLenum type, GLuint program) {
    GLuint shader = glCreateShader(type);

    std::string shaderStr = readFile(path);
    const char* shaderSrc = shaderStr.c_str();

    GLint result = GL_FALSE;
    int logLength;

    std::cout << "compiling shader " << path << std::endl;
    glShaderSource(shader,1 , &shaderSrc, NULL);
    glCompileShader(shader); 

    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<GLchar> shaderError((logLength > 1) ? logLength : 1);
    glGetShaderInfoLog(shader, logLength, NULL, &shaderError[0]);
    std::cout << &shaderError[0] << std::endl;

    glAttachShader(program, shader);

    glDeleteShader(shader);

}