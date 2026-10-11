/**
 * @file transformcomposite.h
 *
 * @brief Declaration of the TransformComposite class, which represents a tree of transformations.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#ifndef TRANSFORMCOMPOSITE_H
#define TRANSFORMCOMPOSITE_H

#include "transformcomponent.h"
#include <glm/mat4x4.hpp>
#include <vector>
#include <memory>

class TransformComposite : public TransformComponent {
    std::vector<std::shared_ptr<TransformComponent>> transforms;

public:
    void add(std::shared_ptr<TransformComponent> transform);
    glm::mat4 getMatrix() const override;
};

#endif // TRANSFORMCOMPOSITE_H 