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

Scene::Scene(std::vector<RenderMesh> renderMeshes) : renderMeshes(renderMeshes) {}

void Scene::render() const {
    for (const RenderMesh rm : renderMeshes) {
        rm.program->use();
        rm.mesh->render();
        glUseProgram(0);
    }
}