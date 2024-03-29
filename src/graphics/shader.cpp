#include "shader.hpp"

#include <fstream>
#include <iostream>
#include <vector>

#include <glm/gtc/type_ptr.hpp>


std::string readFile(const std::string &path) {
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

void loadShader(const std::string &path, GLenum type, GLuint program) {
    GLuint shader = glCreateShader(type);

    std::string shaderStr = readFile(path);
    const char* shaderSrc = shaderStr.c_str();

    int logLength;

    std::cout << "compiling shader " << path << std::endl;
    glShaderSource(shader,1 , &shaderSrc, NULL);
    glCompileShader(shader); 

    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<GLchar> shaderError(logLength > 1 ? logLength : 1);
    glGetShaderInfoLog(shader, logLength, NULL, &shaderError[0]);
    if (shaderError.size() > 1) std::cout << &shaderError[0] << std::endl;

    glAttachShader(program, shader);

    glDeleteShader(shader);

}

Shader::Shader(const std::string &vertPath, const std::string &fragPath) {
    _id = glCreateProgram();
    loadShader(vertPath, GL_VERTEX_SHADER, _id);
    loadShader(fragPath, GL_FRAGMENT_SHADER, _id);
    glLinkProgram(_id);
}

Shader::~Shader() {
    glDeleteProgram(_id);
}

void Shader::use (void) const {
    glUseProgram(_id);
}

void Shader::setBool(const std::string &name, bool value) const {         
    glUniform1i(glGetUniformLocation(_id, name.c_str()), (int)value); 
}
void Shader::setInt(const std::string &name, int value) const { 
    glUniform1i(glGetUniformLocation(_id, name.c_str()), value); 
}
void Shader::setFloat(const std::string &name, float value) const { 
    glUniform1f(glGetUniformLocation(_id, name.c_str()), value); 
} 
void Shader::setMat4(const std::string &name, glm::mat4 value) const {
    glUniformMatrix4fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
