#pragma once
#include <glad/glad.h>
#include <string>

class Shader
{
private:
    unsigned int ID;
    std::string loadFromFile(std::string path);
    GLint getUniformLoc(const GLchar* name) const;
public:
    Shader(std::string vertexPath, std::string fragmentPath);
    void use();
    void set(const GLchar* name, float value) const;
    void set(const GLchar* name, float val1, float val2) const;
    void set(const GLchar* name, float val1, float val2, float val3) const;
    void set(const GLchar* name, float val1, float val2, float val3, float val4) const;
    void set(const GLchar* name, GLfloat* mat);
    ~Shader();
};