/**
 * @file pointlight.cpp
 *
 * @brief 
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#include "pointlight.h"

PointLight::PointLight(const glm::vec3& position, const glm::vec3& color, float intensity)
    : position(position), color(color), intensity(intensity) {

}