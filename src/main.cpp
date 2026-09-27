#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>

#include <GLFW/glfw3.h>  

#include <vector>

#include "models/tree.h"

#include "shader.h"
#include "shaderprogram.h"
#include "mesh.h"
#include "scene.h"
#include "application.h"

int main() {

    Application app = Application();

    app.initialize();

    float points[] = {
        0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };
    Mesh triangleMesh = Mesh(points, sizeof(points));
    Mesh treeMesh = Mesh(tree, sizeof(tree));

    Shader vertexShader = Shader(GL_VERTEX_SHADER, "shaders/vertex/basic.vert");
    Shader fragmentShader = Shader(GL_FRAGMENT_SHADER, "shaders/fragment/basic.frag");

    ShaderProgram program = ShaderProgram(vertexShader, fragmentShader);

    std::vector<RenderMesh> meshes;
    meshes.emplace_back(RenderMesh(&triangleMesh, &program));

    Scene scene1 = Scene(meshes);

    app.addScene(scene1);

    app.run();

    return 0;
}