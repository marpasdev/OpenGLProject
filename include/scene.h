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
#include <optional>

#include "drawableobject.h"
#include "camera.h"
#include "skybox.h"

class Scene {
    std::vector<std::unique_ptr<DrawableObject>> objects;
    std::optional<std::shared_ptr<Skybox>> skybox;

public:
    Scene(std::vector<std::unique_ptr<DrawableObject>> drawableObjects, std::optional<std::shared_ptr<Skybox>> skybox = std::nullopt);

    void update(float deltaTime);

    void render() const;

    DrawableObject* getObject(size_t index) const;

    void addObject(const DrawableObject& obj);

    void removeObject(size_t index);

    std::optional<std::shared_ptr<Skybox>> getSkybox() const;

    void drawSkybox() const;

    size_t getObjectCount() const;

};

#endif // SCENE_H