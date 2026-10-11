/**
 * @file drawableobject.h
 *
 * @brief Declaration of the DrawableObject class, which represents an object consisting of a model, its transformation and a shader program to render it.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H

#include "model.h"
#include "shaderprogram.h"
#include "transform/transformcomponent.h"
#include <memory>

class DrawableObject {
    std::shared_ptr<Model> model;
    std::shared_ptr<ShaderProgram> program;
    std::shared_ptr<TransformComponent> transform;

public:
    DrawableObject(std::shared_ptr<Model> model, std::shared_ptr<ShaderProgram> program,
        std::shared_ptr<TransformComponent> transform);

    std::shared_ptr<TransformComponent> getTransform() const;

    void setTransform(std::shared_ptr<TransformComponent> t);

    std::shared_ptr<ShaderProgram> getProgram() const;

    void setProgram(std::shared_ptr<ShaderProgram> p);

    void update(float deltaTime);

    void draw() const;
};

#endif // DRAWABLEOBJECT_H