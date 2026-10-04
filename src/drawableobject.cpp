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
    glm::vec3 translation = transform.getTranslation();
    program->setUniform("translation", translation.x, translation.y, translation.z);

    glm::vec3 rotation = transform.getRotation();
    program->setUniform("rotation", rotation.x, rotation.y, rotation.z);

    glm::vec3 scale = transform.getScale();
    program->setUniform("scale", scale.x, scale.y, scale.z);

    glUseProgram(program->getID());

    model->render();

    glUseProgram(0);
}