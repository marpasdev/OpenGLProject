/**
 * @file translation.cpp
 *
 * @brief A specialization of TransformLeaf, which performs a translation.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#include "transform/static/translation.h"

#include <glm/gtc/matrix_transform.hpp>

Translation::Translation(const glm::vec3& offset)
    : TransformLeaf(glm::translate(glm::mat4(1.0f), offset)) {}