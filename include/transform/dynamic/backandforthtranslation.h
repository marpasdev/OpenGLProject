/**
 * @file backandforthtranslation.h
 *
 * @brief Declaration of BackAndForthTranslation class, which represents a dynamic translation of an object from the starting point to the end, back and forth.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#ifndef BACKANDFORTHTRANSLATION
#define BACKANDFORTHTRANSLATION

#include "transform/static/translation.h"
#include <glm/vec3.hpp>

class BackAndForthTranslation : public Translation {
    glm::vec3 start;
    glm::vec3 end;
    glm::vec3 currentPos;
    int direction = 1;
    float speed;
    float traveled = 0;

public:
    BackAndForthTranslation(const glm::vec3& start, const glm::vec3& end, float speed);

    void update(float deltaTime) override;
};

#endif // BACKANDFORTHTRANSLATION