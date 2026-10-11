
/**
 * @file transformleaf.cpp
 *
 * @brief Represents a single transformation.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#include "transform/transformleaf.h"

TransformLeaf::TransformLeaf(const glm::mat4& transform) : transform(transform) {}

glm::mat4 TransformLeaf::getMatrix() const {
    return transform;
}