/**
 * @file texture.h
 *
 * @brief Declaration of the Texture class.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/gl.h>

#include <string>

class Texture {
    int width;
    int height;
    int channels;
    unsigned char* data;
    GLuint id;

public:

    Texture(const std::string& path);
    ~Texture();

    void bind();
};

#endif // TEXTURE_H