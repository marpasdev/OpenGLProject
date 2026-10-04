/**
 * @file transformation.h
 *
 * @brief Declaration of the Transformation class, which represents basic transformation of an object.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <glm/vec3.hpp>

class Transformation {
    glm::vec3 translation = glm::vec3{0.0f};
    glm::vec3 rotation = glm::vec3{0.0f};
    glm::vec3 scale = glm::vec3{1.0f};

public:
    explicit Transformation(const glm::vec3& translation = glm::vec3{0.0f},
                   const glm::vec3& rotation = glm::vec3{0.0f},
                   const glm::vec3& scale = glm::vec3{1.0f});

    glm::vec3 getTranslation() const;
    glm::vec3 getRotation() const;
    glm::vec3 getScale() const;

    void setTranslation(const glm::vec3& t);
    void translate(const glm::vec3& deltaT);

    void setRotation(const glm::vec3& r);
    void rotate(const glm::vec3& deltaR);

    void setScale(float value);
    void setScale(const glm::vec3& s);
    void scaleBy(float factor);
    void scaleBy(const glm::vec3& factors);
};

#endif // TRANSFORMATION_H