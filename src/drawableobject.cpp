/**
 * @file drawableobject.cpp
 *
 * @brief Represents an object consisting of a model, its transformation and a shader program to render it.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#include <glm/gtc/matrix_transform.hpp>

#include "drawableobject.h"

DrawableObject::DrawableObject(std::shared_ptr<Model> model, std::shared_ptr<ShaderProgram> program,
    std::shared_ptr<TransformComponent> transform)
    : model(std::move(model)), program(std::move(program)), transform(std::move(transform)) {}

std::shared_ptr<TransformComponent> DrawableObject::getTransform() const {
    return transform;
}

void DrawableObject::setTransform(std::shared_ptr<TransformComponent> t) {
    transform = t;
}

std::shared_ptr<ShaderProgram> DrawableObject::getProgram() const {
    return program;
}

void DrawableObject::setProgram(std::shared_ptr<ShaderProgram> p) {
    program = p;
}

void DrawableObject::draw() const {
    glm::mat4 modelMatrix = transform->getMatrix();
    program->setUniform("modelMatrix", modelMatrix);

    program->use();

    model->render();

    program->stopUsing();
}