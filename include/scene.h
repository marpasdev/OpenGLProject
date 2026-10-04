/**
 * @file scene.h
 *
 * @brief Declaration of the Scene class, which holds a collection of models and their respective shader programs for rendering.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "drawableobject.h"

class Scene {
    std::vector<DrawableObject> objects;

public:
    Scene(std::vector<DrawableObject> drawableObjects);

    void render() const;
};

#endif // SCENE_H