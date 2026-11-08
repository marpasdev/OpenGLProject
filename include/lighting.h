/**
 * @file lighting.h
 *
 * @brief Declaration of the Lighting class.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#ifndef LIGHTING_H
#define LIGHTING_H

#include <glm/vec3.hpp>

class Lighting {
    glm::vec3 position = glm::vec3{0.0f};
    glm::vec3 color = glm::vec3{1.0f};
    float intensity = 1.0f;

    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;

public:
    Lighting(const glm::vec3& position, const glm::vec3& color, float intensity);
};

#endif // LIGHTING_H