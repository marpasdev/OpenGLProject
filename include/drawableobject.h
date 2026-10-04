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
#include "transformation.h"

class DrawableObject {
    Model* model;
    ShaderProgram* program;
    Transformation transform;

public:
    DrawableObject(Model* model, ShaderProgram* program,
        Transformation transform = Transformation());

    Transformation getTransform() const;

    void setTransform(const Transformation& t);

    ShaderProgram* getProgram() const;

    void setProgram(ShaderProgram* p);

    void draw() const;
};

#endif // DRAWABLEOBJECT_H