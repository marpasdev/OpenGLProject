/**
 * @file scale.cpp
 *
 * @brief A specialization of TransformLeaf, which performs a scale.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#include "transform/static/scale.h"

#include <glm/gtc/matrix_transform.hpp>

Scale::Scale(float scale)
    : TransformLeaf(glm::scale(glm::mat4(1.0f), glm::vec3(scale))) {}

Scale::Scale(const glm::vec3& scale)
    : TransformLeaf(glm::scale(glm::mat4(1.0f), scale)) {}