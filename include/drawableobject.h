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

#include <glad/gl.h>

#include "model.h"
#include "shaderprogram.h"
#include "transform/transformcomponent.h"

#include <memory>
#include <variant>
#include <unordered_map>
#include <string>

using UniformValue = std::variant<GLfloat, glm::vec3, glm::vec4, glm::mat4>;

class DrawableObject {
    std::shared_ptr<Model> model;
    std::shared_ptr<ShaderProgram> program;
    std::shared_ptr<TransformComponent> transform;
    std::unordered_map<std::string, UniformValue> uniforms;

    void setUniforms() const;
    
public:
    DrawableObject(std::shared_ptr<Model> model, std::shared_ptr<ShaderProgram> program,
        std::shared_ptr<TransformComponent> transform);

    std::shared_ptr<TransformComponent> getTransform() const;

    void setTransform(std::shared_ptr<TransformComponent> t);

    std::shared_ptr<ShaderProgram> getProgram() const;

    void setProgram(std::shared_ptr<ShaderProgram> p);

    void setUniform(const std::string& name, const UniformValue& value);

    void update(float deltaTime);

    void draw() const;
};

#endif // DRAWABLEOBJECT_H