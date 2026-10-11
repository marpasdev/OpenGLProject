/**
 * @file transformcomponent.h
 *
 * @brief Declaration of the abstract TransformComponent class.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <glm/mat4x4.hpp>

class TransformComponent {

public:
    virtual ~TransformComponent() = default;
    virtual glm::mat4 getMatrix() const = 0;
    virtual void update(float /*deltaTime*/) {};
};

#endif // TRANSFORMCOMPONENT_H