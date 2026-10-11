/**
 * @file dynamicrotation.h
 *
 * @brief Declaration of DynamicRotation class, which represents a rotation that can change in time.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#ifndef DYNAMICROTATION_H
#define DYNAMICROTATION_H

#include "transform/static/rotation.h"

class DynamicRotation : public Rotation {
    float angle = 0;
    float angleSpeed;
    int direction = 1;
    glm::vec3 axis;

public:
    DynamicRotation(const glm::vec3& axis, float angleSpeed);
    DynamicRotation(float startAngle, const glm::vec3& axis, float angleSpeed);
    DynamicRotation(float startAngle, const glm::vec3& axis, float angleSpeed, bool opposite);

    void switchDirection();
    
    void update(float deltaTime) override;
};

#endif // DYNAMICROTATION_H