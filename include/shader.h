/**
 * @file shader.h
 *
 * @brief Declaration of the Shader class, which wraps a compiled shader.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#ifndef SHADER_H
#define SHADER_H

#include <glad/gl.h>

class Shader {
    GLuint id = 0;

    GLuint createFromFile(GLenum type, const char* shaderFile) const;

public:

    Shader(GLenum type, const char* file);

    Shader(const Shader& other) = delete;

    ~Shader();

    Shader& operator=(const Shader& other) = delete;

    void attachTo(GLuint program) const;
};

#endif // SHADER_H