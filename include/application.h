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

#include "scene.h"

struct WindowDeleter {
    void operator()(GLFWwindow* window);
};

class Application {
    std::unique_ptr<GLFWwindow, WindowDeleter> window;
    std::vector<Scene> scenes;
    size_t currentScene = 0;
    std::unordered_map<std::string, std::unique_ptr<Model>> models;
    std::unordered_map<std::string, std::unique_ptr<Shader>> shaders;
    std::unordered_map<std::string, std::unique_ptr<ShaderProgram>> programs;

    void initializeGLFW(int width, int height);

public:
    Application() = default;    

    Application(const Application& other) = delete;

    ~Application();

    Application& operator=(const Application& other) = delete;

    void initialize(int windowWidth, int windowHeight);

    void createShaders();

    void createModels();

    void createPrograms();

    void createScenes();

    void onKey(int key, int action);

    void run() const;

    void getVersionInfo() const;

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif // APPLICATION_H