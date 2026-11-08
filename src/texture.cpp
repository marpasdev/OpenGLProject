/**
 * @file texture.cpp
 *
 * @brief 
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#include <glad/gl.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

#include "texture.h"

Texture::Texture(const std::string& path) {
	stbi_set_flip_vertically_on_load(true);

    this->data = stbi_load(path.c_str(), &this->width, &this->height,
        &this->channels, STBI_rgb_alpha);

    if (!data) {
        std::cerr << "Error loading texture: " << path << "\n";
    }

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &this->id);
	glBindTexture(GL_TEXTURE_2D, this->id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(this->data);
}

Texture::~Texture() {
    glDeleteTextures(1, &this->id);
}

void Texture::bind() {
    glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->id);
}