#include "scene.h"

RenderMesh::RenderMesh(Mesh* mesh, ShaderProgram* program) : mesh(mesh), program(program) {}

Scene::Scene(const std::vector<RenderMesh>& renderMeshes) : renderMeshes(renderMeshes) {}

void Scene::render() const {
    for (const RenderMesh rm : renderMeshes) {
        rm.program->use();
        rm.mesh->render();
        glUseProgram(0);
    }
}