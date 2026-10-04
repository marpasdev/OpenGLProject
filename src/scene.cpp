/**
 * @file scene.cpp
 *
 * @brief Holds a collection of models and their respective shader programs for rendering.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#include "scene.h"

Scene::Scene(std::vector<DrawableObject> objects) : objects(objects) {}

void Scene::render() const {
    for (const DrawableObject& o : objects) {
        o.draw();
    }
}