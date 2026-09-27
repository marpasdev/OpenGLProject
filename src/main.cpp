#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>

#include <GLFW/glfw3.h>  

#include <vector>

#include "models/tree.h"
#include "models/gift.h"

#include "shader.h"
#include "shaderprogram.h"
#include "mesh.h"
#include "scene.h"
#include "application.h"

int main() {

    Application app = Application();

    app.initialize();

    float aspectRatio = 800.0f / 600.0f;

    float points[] = {
        0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };
    Mesh triangleMesh = Mesh(points, sizeof(points));

    float square[] = {
        -0.5f, aspectRatio * 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -aspectRatio * 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -aspectRatio * 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, aspectRatio * 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, aspectRatio * -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, aspectRatio * 0.5f, 0.0f, 1.0f, 1.0f, 0.0f
    };
    Mesh squareMesh = Mesh(square, sizeof(square));
    Mesh treeMesh = Mesh(tree, sizeof(tree));
    Mesh giftMesh = Mesh(gift, sizeof(gift));

    Shader basicVertexShader = Shader(GL_VERTEX_SHADER, "shaders/vertex/basic.vert");
    Shader basicFragmentShader = Shader(GL_FRAGMENT_SHADER, "shaders/fragment/basic.frag");

    Shader scaledownVertexShader = Shader(GL_VERTEX_SHADER, "shaders/vertex/scaledown.vert");
    Shader moveVertexShader = Shader(GL_VERTEX_SHADER, "shaders/vertex/move.vert");

    Shader greenFragmentShader = Shader(GL_FRAGMENT_SHADER, "shaders/fragment/green.frag");
    Shader reddishFragmentShader = Shader(GL_FRAGMENT_SHADER, "shaders/fragment/reddish.frag");

    ShaderProgram program = ShaderProgram(basicVertexShader, basicFragmentShader);
    ShaderProgram program2 = ShaderProgram(scaledownVertexShader, greenFragmentShader);
    ShaderProgram program3 = ShaderProgram(moveVertexShader, reddishFragmentShader);

    std::vector<RenderMesh> meshes;
    meshes.emplace_back(RenderMesh(&triangleMesh, &program));
    // meshes.emplace_back(RenderMesh(&squareMesh, &program));
    // meshes.emplace_back(RenderMesh(&treeMesh, &program2));
    // meshes.emplace_back(RenderMesh(&giftMesh, &program3));

    Scene scene1 = Scene(meshes);

    app.addScene(scene1);

    app.run();

    return 0;
}