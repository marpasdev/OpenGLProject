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