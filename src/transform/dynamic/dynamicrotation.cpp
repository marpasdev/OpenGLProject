/**
 * @file dynamicrotation.cpp
 *
 * @brief Represents a rotation that can change in time.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#include "transform/dynamic/dynamicrotation.h"
#include <glm/gtc/matrix_transform.hpp>

DynamicRotation::DynamicRotation(const glm::vec3& axis, float angleSpeed)
    : Rotation(0.0f, axis), angleSpeed(angleSpeed), axis(axis) {}

DynamicRotation::DynamicRotation(float startAngle, const glm::vec3& axis, float angleSpeed)
    : Rotation(startAngle, axis), angleSpeed(angleSpeed), angle(startAngle), axis(axis) {}

DynamicRotation::DynamicRotation(float startAngle, const glm::vec3& axis, float angleSpeed, bool opposite)
    : Rotation(startAngle, axis), angleSpeed(angleSpeed), angle(startAngle), axis(axis) {
        if (opposite) {
            direction = -1;
        }
    }

void DynamicRotation::switchDirection() {
    direction *= -1;
}
    
void DynamicRotation::update(float deltaTime) {
    angle += angleSpeed * direction * deltaTime;

    if (angle >= glm::radians(360.0f)) {
        angle -= glm::radians(360.0f);
    } else if (angle < 0) {
        angle += glm::radians(360.0f);
    }
    transform = glm::rotate(glm::mat4(1.0f), angle, axis);
}