#pragma once

#include <glad/glad.h> 
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include<glm.hpp>

// Bind and set shaders
// Gets shader from file location
class Shader
{
public:
    // the program ID
    unsigned int ID;

    // constructor reads and builds the shader
    // @param vertexPath: Vertex Shader file location
    // @param fragmentPath: Fragment Shader file location
    Shader(const char* vertexPath, const char* fragmentPath);

    // use the shader
    void Use();

    // utility uniform function
    // @param value: float to be inputed into uniform for shader
    void SetUniform(const std::string& name, float value);
    // utility uniform function
    // @param value: int to be inputed into uniform for shader
    void SetUniform(const std::string& name, int value);
    // utility uniform function
    // @param value: bool to be inputed into uniform for shader
    void SetUniform(const std::string& name, bool value);
    // utility uniform function
    // @param value: vec4 to be inputed into uniform for shader
    void SetUniform(const std::string& name, glm::vec4 value);
};
