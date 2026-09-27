#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "mesh.h"
#include "shaderprogram.h"

struct RenderMesh {
    Mesh* mesh;
    ShaderProgram* program;

    RenderMesh(Mesh* mesh, ShaderProgram* program);
};

class Scene {
    std::vector<RenderMesh> renderMeshes; 

public:
    Scene(const std::vector<RenderMesh>& renderMeshes);

    void render() const;
};


#endif