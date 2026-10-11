/**
 * @file translation.h
 *
 * @brief Declaration of Translation class, which is a specialization of TransformLeaf, which performs a translation.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#ifndef TRANSLATION_H
#define TRANSLATION_H

#include "transform/transformleaf.h"

#include <glm/vec3.hpp>

class Translation : public TransformLeaf {
public:   
    Translation(const glm::vec3& offset);
};

#endif // TRANSLATION_H