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

#include "mesh.h"
#include "shaderprogram.h"

struct RenderMesh {
    Mesh* mesh;
    ShaderProgram* program;
};

class Scene {
    std::vector<RenderMesh> renderMeshes; 

public:
    Scene(std::vector<RenderMesh> renderMeshes);

    void render() const;
};


#endif // SCENE_H