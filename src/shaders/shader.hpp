#ifndef SHADER_H
#define SHADER_H

#include <string>

#ifdef unix
#include <GL/glew.h>
#endif  // unix

class Shader {
public: 
    GLuint ID;

    Shader(const char* vertPath, const char* fragPath);

    void use(void);

    void setBool(const std::string &name, bool value) const;  
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;

};

#endif  // SHADER_H