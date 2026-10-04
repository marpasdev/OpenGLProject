/**
 * @file main.cpp
 *
 * @brief Application's entry point.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>

#include <GLFW/glfw3.h>  

#include <memory>

#include "application.h"

int main() {
    auto app = std::make_unique<Application>();

    app->initialize(1200, 1200);

    app->createShaders();
    app->createModels();
    app->createPrograms();

    app->createScenes();

    app->run();

    return 0;
}