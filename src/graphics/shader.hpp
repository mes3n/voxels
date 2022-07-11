#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

#ifdef unix
#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#endif  // unix

class Shader {
    private:
        GLuint id;
        
    public: 
        Shader(const std::string &vertPath, const std::string &fragPath);
        ~Shader();

        void use(void) const;

        void setBool(const std::string &name, bool value) const;  
        void setInt(const std::string &name, int value) const;   
        void setFloat(const std::string &name, float value) const;
        void setMat4(const std::string &name, glm::mat4 value) const;

};

#endif  // SHADER_HPP