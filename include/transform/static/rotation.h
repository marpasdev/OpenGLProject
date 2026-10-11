/**
 * @file rotation.h
 *
 * @brief Declaration of Rotation class, which is a specialization of TransformLeaf, which performs a rotation.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#ifndef ROTATION_H
#define ROTATION_H

#include "transform/transformleaf.h"

class Rotation : public TransformLeaf {
public:
    Rotation(const glm::vec3& eulerAngles);
    Rotation(float angle, const glm::vec3& axis);
};

#endif // ROTATION_H