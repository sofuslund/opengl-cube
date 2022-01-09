#include "Shader.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <streambuf>

Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath)
{
    // Get the vertex and fragment shader sources
    std::string sVertexShaderSource = loadFromFile(vertexShaderPath);
    std::string sFragmentShaderSource = loadFromFile(fragmentShaderPath);
    const GLchar* vertexShaderSource = sVertexShaderSource.c_str();
    const GLchar* fragmentShaderSource = sFragmentShaderSource.c_str();

    GLint success = 0;

    // Compile the shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    // Check for errors in the compiling
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLint maxLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
        
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &errorLog[0]);

        std::cout << &errorLog[0] << std::endl;
    }
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLint maxLength = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &errorLog[0]);

        std::cout << &errorLog[0] << std::endl;
    }

    // Link the shaders
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    // Check for link errors
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLint maxLength = 0;
        glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &maxLength);
        
        std::vector<GLchar> errorLog(maxLength);
        glGetProgramInfoLog(ID, maxLength, &maxLength, &errorLog[0]);
        std::cout << &errorLog[0] << std::endl;
    }

    // Cleanup
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDetachShader(ID, vertexShader);
    glDetachShader(ID, fragmentShader);
}
std::string Shader::loadFromFile(std::string path)
{
    std::ifstream file;

    // Open the file
    file.open(path);
    if(!file)std::cout << "No such file" << std::endl;
    std::string contents;
    std::string line;
    while (getline(file, line))
    {
        contents.append(line);
        contents.append("\n");
    }
    // Close the file
    file.close();
    
    return contents;
}
GLint Shader::getUniformLoc(const GLchar* name) const
{
    GLint loc = glGetUniformLocation(ID, name);
    if (loc == -1)
    {
        std::cout << "Failed to find uniform " << name << std::endl;
    }
    return loc;
}
void Shader::use()
{
    glUseProgram(ID);
}
void Shader::set(const GLchar* name, float value) const
{
    glUniform1f(getUniformLoc(name), value);
}
void Shader::set(const GLchar* name, float val1, float val2) const
{
    glUniform2f(getUniformLoc(name), val1, val2);
}
void Shader::set(const GLchar* name, float val1, float val2, float val3) const
{
    glUniform3f(getUniformLoc(name), val1, val2, val3);
}
void Shader::set(const GLchar* name, float val1, float val2, float val3, float val4) const
{
    glUniform4f(getUniformLoc(name), val1, val2, val3, val4);
}
void Shader::set(const GLchar* name, GLfloat* mat)
{
    glUniformMatrix4fv(getUniformLoc(name), 1, GL_FALSE, mat);
}
Shader::~Shader()
{
    glDeleteProgram(ID);
}