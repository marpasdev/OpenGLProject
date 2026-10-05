/**
 * @file shader.cpp
 *
 * @brief Wraps a compiled shader.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#include <iostream>
#include <fstream>

#include "shader.h"

GLuint Shader::createFromFile(GLenum shaderType, const char* shaderFile) const {
    GLuint shaderID = glCreateShader(shaderType);

    if (shaderID == 0) {
        std::cerr << "Unable to create shader\n";
        exit(EXIT_FAILURE);
    }

    std::ifstream file(shaderFile);
    if (!file.is_open()) {
        std::cerr << "Unable to open file " << shaderFile << '\n';
        glDeleteShader(shaderID);
        exit(-1);
    }
    std::string shaderCode((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    const char* source = shaderCode.c_str();
    glShaderSource(shaderID, 1, &source, nullptr);

    glCompileShader(shaderID);

    GLint success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetShaderInfoLog(shaderID, sizeof(infoLog), nullptr, infoLog);
        std::cerr
            << "Shader compilation failed:\n"
            << infoLog << "\n";
        glDeleteShader(shaderID);
        exit(EXIT_FAILURE);
    }

    return shaderID;
}

Shader::Shader(GLenum type, const char* file) {
    id = createFromFile(type, file);
}

Shader::~Shader() {
    glDeleteShader(id);
}

void Shader::attachTo(GLuint program) const {
    glAttachShader(program, id);
}