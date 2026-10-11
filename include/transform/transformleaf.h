/**
 * @file transformleaf.h
 *
 * @brief Declaration of the TransformLeaf class, which represents a single transformation.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#ifndef TRANSFORMLEAF_H
#define TRANSFORMLEAF_H

#include <glm/mat4x4.hpp>

#include "transformcomponent.h"

class TransformLeaf : public TransformComponent {
protected:
    glm::mat4 transform;

public:
    TransformLeaf(const glm::mat4& transform);

    glm::mat4 getMatrix() const override;
};

#endif // TRANSFORMLEAF_H