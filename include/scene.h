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
#include <memory>

#include "drawableobject.h"
#include "camera.h"

class Scene {
    std::vector<std::unique_ptr<DrawableObject>> objects;

public:
    Scene(std::vector<std::unique_ptr<DrawableObject>> drawableObjects);

    void update(float deltaTime);

    void render() const;

    DrawableObject* getObject(size_t index) const;

};

#endif // SCENE_H