/**
 * @file backandforthtranslation.cpp
 *
 * @brief Represents a dynamic translation of an object from the starting point to the end, back and forth.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#include "transform/dynamic/backandforthtranslation.h"
#include <glm/gtc/matrix_transform.hpp>

BackAndForthTranslation::BackAndForthTranslation(const glm::vec3& start, const glm::vec3& end, float speed)
    : Translation(start), start(start), end(end), speed(speed), currentPos(start) {}

void BackAndForthTranslation::update(float deltaTime) {
    glm::vec3 directionVec = end - start;
    currentPos += glm::normalize(directionVec) * speed * deltaTime * static_cast<float>(direction);
    traveled += speed * deltaTime * static_cast<float>(direction);

    float dist = glm::length(directionVec);

    if (traveled >= dist) {
        traveled = dist; 
        currentPos = end;
        direction = -direction;
    } else if (traveled <= 0) {
        traveled = 0;
        currentPos = start;
        direction = -direction;
    }

    transform = glm::translate(glm::mat4{1.0f}, currentPos);
}