#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <glad/gl.h>
#include <vector>
#include "shader.h"

class ShaderProgram {
    GLuint id = 0;

public:
    ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader);

    ShaderProgram(const ShaderProgram& other) = delete;
    
    ~ShaderProgram();

    ShaderProgram& operator=(const ShaderProgram& other) = delete;

    void use() const;

    GLuint getID() const;
};

#endif