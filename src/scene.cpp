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

Scene::Scene(std::vector<std::unique_ptr<DrawableObject>> objects,
    std::optional<std::shared_ptr<Skybox>> skybox) : objects(std::move(objects)), skybox(skybox) {}

void Scene::update(float deltaTime) {
    for (const auto& o : objects) {
        o->update(deltaTime);
    }
}

void Scene::render() const {
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    size_t id = 0;
    for (const auto& o : objects) {
        if (id < 256) {
            glStencilFunc(GL_ALWAYS, id, 0xFF);
        }
        o->draw();
        ++id;
    }
}

DrawableObject* Scene::getObject(size_t index) const {
    return objects.at(index).get();
}

void Scene::addObject(const DrawableObject& obj) {
    objects.push_back(std::make_unique<DrawableObject>(obj));
}

void Scene::removeObject(size_t index) {
    objects.erase(objects.begin() + index);
}

std::optional<std::shared_ptr<Skybox>> Scene::getSkybox() const {
    return this->skybox;
}

void Scene::drawSkybox() const {
    if (skybox.has_value()) {
        (*skybox)->draw();
    }
}

size_t Scene::getObjectCount() const {
    return objects.size();
}