/**
 * @file transformation.cpp
 *
 * @brief Represents basic transformation of an object.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#include "transformation.h"

// Transformation::Transformation(const glm::vec3& translation, 
//         const glm::vec3& rotation, const glm::vec3& scale)
//             : translation(translation), rotation(rotation), scale(scale) {}
Transformation::Transformation(const glm::mat4& translation,
        const glm::mat4& rotation,
        const glm::mat4& scale)
        : translation(translation), rotation(rotation), scale(scale) {}

glm::mat4 Transformation::getTranslation() const {
    return translation;
}

glm::mat4 Transformation::getRotation() const {
    return rotation;
}

glm::mat4 Transformation::getScale() const {
    return scale;
}
    
// void Transformation::setTranslation(const glm::vec3& t) {
//     translation = t;
// }

// void Transformation::translate(const glm::vec3& deltaT) {
//     translation += deltaT;
// }

// void Transformation::setRotation(const glm::vec3& r) {
//     rotation = r;
// }

// void Transformation::rotate(const glm::vec3& deltaR) {
//     rotation += deltaR;
// }

// void Transformation::setScale(float value) {
//     scale = glm::vec3{value};
// }

// void Transformation::setScale(const glm::vec3& s) {
//     scale = s;
// }

// void Transformation::scaleBy(float factor) {
//     scale *= factor;
// }

// void Transformation::scaleBy(const glm::vec3& factors) {
//     scale *= factors;
// }