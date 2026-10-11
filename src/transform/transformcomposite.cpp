
/**
 * @file transformcomposite.cpp
 *
 * @brief Represents a tree of transformations.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#include "transform/transformcomposite.h"

void TransformComposite::add(std::shared_ptr<TransformComponent> transform) {
    transforms.push_back(transform);
}

glm::mat4 TransformComposite::getMatrix() const {
    glm::mat4 transform = glm::mat4(1.0f);

    for (auto it = transforms.rbegin(); it != transforms.rend(); ++it) {
        transform *= it->get()->getMatrix();
    }

    return transform;
}