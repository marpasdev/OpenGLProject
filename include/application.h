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

    bool rotating = false;
    double lastX = 0;
    double lastY = 0;
    float mouseSensitivity = glm::radians(0.2f);

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

    void run();

    void getVersionInfo() const;

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void onKey(int key, int action);

    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    void onResize(int width, int height);

    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    void onMouseButton(int button, int action);

    static void cursorPosCallback(GLFWwindow* window, double x, double y);
    void onMouseMove(double x, double y);
};

#endif // APPLICATION_H