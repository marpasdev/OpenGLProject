/**
 * @file skybox.h
 *
 * @brief Declaration of the Skybox class.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#ifndef SKYBOX_H
#define SKYBOX_H

#include <array>
#include <string>
#include <memory>
#include "shaderprogram.h"
#include "model.h"
#include <glm/mat4x4.hpp>

#include <glad/gl.h>

class Skybox {
    std::shared_ptr<ShaderProgram> program;
    std::shared_ptr<Model> model;
    GLuint texture;

public:

    explicit Skybox(const std::shared_ptr<ShaderProgram>& program,
        const std::array<std::string, 6>& facePaths, const std::shared_ptr<Model>& model);

    ~Skybox();

    Skybox(const Skybox&) = delete;

    Skybox& operator=(const Skybox&) = delete;

    Skybox(Skybox&& other) noexcept;

    Skybox& operator=(Skybox&& other) noexcept;

    void draw() const;
};

#endif // SKYBOX_H