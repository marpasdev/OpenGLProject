/**
 * @file rotation.cpp
 *
 * @brief A specialization of TransformLeaf, which performs a rotation.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#include "transform/static/rotation.h"
#include <glm/gtc/matrix_transform.hpp>

Rotation::Rotation(const glm::vec3& eulerAngles)
    : TransformLeaf(
        glm::rotate(glm::mat4(1.0f), eulerAngles.x, glm::vec3(1.0f, 0.0f, 0.0f)) *
        glm::rotate(glm::mat4(1.0f), eulerAngles.y, glm::vec3(0.0f, 1.0f, 0.0f)) *
        glm::rotate(glm::mat4(1.0f), eulerAngles.z, glm::vec3(0.0f, 0.0f, 1.0f))) {}

Rotation::Rotation(float angle, const glm::vec3& axis)
    : TransformLeaf(glm::rotate(glm::mat4(1.0f), angle, axis)) {}