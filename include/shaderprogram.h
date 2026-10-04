/**
 * @file shaderprogram.h
 *
 * @brief Declaration of the ShaderProgram class, which wraps a compiled shader program consisting of a vertex and a fragment shader.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <glad/gl.h>

#include <string>

#include "shader.h"

class ShaderProgram {
    GLuint id = 0;

    GLint getUniform(const std::string& name) const;

public:
    ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader);

    ShaderProgram(const ShaderProgram& other) = delete;
    
    ~ShaderProgram();

    ShaderProgram& operator=(const ShaderProgram& other) = delete;

    void use() const;

    GLuint getID() const;

    void setUniform(const std::string& name, GLfloat x) const;

    void setUniform(const std::string& name, GLfloat x, GLfloat y, GLfloat z) const;
    
    void setUniform(const std::string& name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const;
};

#endif // SHADERPROGRAM_H