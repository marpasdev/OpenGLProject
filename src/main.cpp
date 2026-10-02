/**
 * @file main.cpp
 *
 * @brief application's entry point
 *
 * @author Marek Pastva (PAS0217)
 *
 * @year 2026
 **/
#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>

#include <GLFW/glfw3.h>  

#include <vector>

#include "shader.h"
#include "shaderprogram.h"
#include "mesh.h"
#include "scene.h"
#include "application.h"

int main() {
    Application* app = new Application();

    app->initialize();

    app->createShaders();
    app->createModels();
    app->createPrograms();

    app->createScenes();

    app->run();

    delete app;

    return 0;
}