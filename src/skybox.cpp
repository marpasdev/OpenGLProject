/**
 * @file skybox.cpp
 *
 * @brief 
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#include "skybox.h"
#include "stb_image.h"
#include <iostream>
#include <utility>

Skybox::Skybox(const std::shared_ptr<ShaderProgram>& program,
    const std::array<std::string, 6>& facePaths, const std::shared_ptr<Model>& model)
        : program(program), model(model) {
    
    glGenTextures(1, &this->texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->texture);
    stbi_set_flip_vertically_on_load(false);
    for (size_t i = 0; i < 6; ++i) {
        int width;
        int height;
        int channels;

        stbi_uc* data = stbi_load(("assets/textures/" + facePaths[i]).c_str(), &width, &height, &channels, 3);
    
        if (!data) {
            std::cerr << "Skybox texture failed to load.\n";
            continue;
        }

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0,
            GL_RGB, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
        }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

Skybox::~Skybox() {
    glDeleteTextures(1, &this->texture);
}

Skybox::Skybox(Skybox&& other) noexcept
    : texture(std::exchange(other.texture, 0)),
    program(std::move(other.program)),
    model(std::move(other.model)) {
}

Skybox& Skybox::operator=(Skybox&& other) noexcept {
    std::swap(texture, other.texture);
    std::swap(program, other.program);
    std::swap(model, other.model);
    return *this;
}

void Skybox::draw() const {

    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_FALSE);

    program->use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

    model->render();

    program->stopUsing();

    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
}