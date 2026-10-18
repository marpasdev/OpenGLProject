/**
 * @file application.h
 *
 * @brief Declaration of the Application class that manages scenes and their resources.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#ifndef APPLICATION_H
#define APPLICATION_H

#include <GLFW/glfw3.h>

#include <vector>
#include <unordered_map>
#include <string>
#include <memory>

#include <ctime>
#include <chrono>

#include <glm/vec3.hpp>

#include "scene.h"

#include "camera.h" // to be removed

struct WindowDeleter {
    void operator()(GLFWwindow* window);
};

class Application {
    std::unique_ptr<GLFWwindow, WindowDeleter> window;
    Camera camera;
    std::vector<Scene> scenes;
    size_t currentScene = 0;

    void initializeGLFW(int width, int height);

    void processInput(float deltaTime);

    glm::ivec3 getTimeHMS() const;

public:
    Application();    

    Application(const Application& other) = delete;

    ~Application();

    Application& operator=(const Application& other) = delete;

    void initialize(int windowWidth, int windowHeight);

    void createScenes();

    void onKey(int key, int action);

    void run();

    void getVersionInfo() const;

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif // APPLICATION_H