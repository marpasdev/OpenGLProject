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

#include <utility>

Scene::Scene(std::vector<std::unique_ptr<DrawableObject>> objects) : objects(std::move(objects)) {}

void Scene::update(float deltaTime) {
    for (const auto& o : objects) {
        o->update(deltaTime);
    }
}

void Scene::render() const {
    for (const auto& o : objects) {
        o->getProgram()->setUniform("viewMatrix", camera->getView());
        o->getProgram()->setUniform("projectionMatrix", camera->getProjection());
        o->draw();
    }
}

DrawableObject* Scene::getObject(size_t index) const {
    return objects.at(index).get();
}

Camera* Scene::getCamera() const {
    return camera.get();
}

void Scene::setCamera(std::shared_ptr<Camera> newCamera) {
    camera = newCamera;
}