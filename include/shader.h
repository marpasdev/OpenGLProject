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

    GLuint getID() const;
};

#endif