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
    // position
    glm::vec3 color = glm::vec3{1.0};
    // constant attenuation factor
    // linear attenuation factor
    // quadratic attenuation factor
    float shininess = 1.0f;

public:
};

#endif // LIGHTING_H