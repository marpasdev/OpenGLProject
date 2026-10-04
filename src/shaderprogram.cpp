/**
 * @file shaderprogram.cpp
 *
 * @brief Wraps a compiled shader program consisting of a vertex and a fragment shader.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#include <iostream>

#include "shaderprogram.h"

ShaderProgram::ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader) {
    id = glCreateProgram();

    glAttachShader(id, vertexShader.getID());
    glAttachShader(id, fragmentShader.getID());

    glLinkProgram(id);

    GLint success;
    glGetProgramiv(id, GL_LINK_STATUS, &success);

    if (!success) {
        char infoLog[1024];
        glGetProgramInfoLog(id, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "Shader program linking failed:\n"
                  << infoLog << "\n";
        exit(EXIT_FAILURE);
    }
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(id);
}

void ShaderProgram::use() const {
    glUseProgram(id);
}

GLuint ShaderProgram::getID() const {
    return id;
}

GLint ShaderProgram::getUniform(const std::string& name) const {
    GLint loc = glGetUniformLocation(id, name.c_str());

    if (loc == -1) {
        std::cerr << "Uniform '" << name << "' not found in shader program "
        << id << ". It may be unused or misspelled.\n";
    }

    return loc;
}

void ShaderProgram::setUniform(const std::string& name, GLfloat x) const {
    GLint loc = getUniform(name);
    
    if (loc != -1) {
        glUseProgram(id);

        glUniform1f(loc, x);

        glUseProgram(0);
    }
}

void ShaderProgram::setUniform(const std::string& name, GLfloat x, GLfloat y, GLfloat z) const {
    GLint loc = getUniform(name);

    if (loc != -1) {
        glUseProgram(id);

        glUniform3f(loc, x, y, z);

        glUseProgram(0);
    }
}

void ShaderProgram::setUniform(const std::string& name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const {
    GLint loc = getUniform(name);
    
    if (loc != -1) {
        glUseProgram(id);

        glUniform4f(loc, x, y, z, w);

        glUseProgram(0);
    }
}