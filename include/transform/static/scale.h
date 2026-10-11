/**
 * @file scale.h
 *
 * @brief Declaration of Scale class, which is a specialization of TransformLeaf, which performs a scale.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#ifndef SCALE_H
#define SCALE_H

#include "transform/transformleaf.h"

#include <glm/vec3.hpp>

class Scale : public TransformLeaf {
public:   
    Scale(float scale);
    Scale(const glm::vec3& scale);
};

#endif // SCALE_H