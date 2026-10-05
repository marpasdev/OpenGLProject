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

DrawableObject::DrawableObject(Model* model, ShaderProgram* program, Transformation transform)
    : model(model), program(program), transform(transform) {}

Transformation DrawableObject::getTransform() const {
    return transform;
}

void DrawableObject::setTransform(const Transformation& t) {
    transform = t;
}

ShaderProgram* DrawableObject::getProgram() const {
    return program;
}

void DrawableObject::setProgram(ShaderProgram* p) {
    program = p;
}

void DrawableObject::draw() const {
    glm::mat4 modelMatrix = transform.getScale() * transform.getRotation() * transform.getTranslation();
    program->setUniform("modelMatrix", modelMatrix);

    program->use();

    model->render();

    program->stopUsing();
}