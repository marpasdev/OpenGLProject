#ifndef APPLICATION_H
#define APPLICATION_H

#include <GLFW/glfw3.h>

#include <vector>
#include <unordered_map>
#include <string>

#include "scene.h"

class Application {
    GLFWwindow* window;
    std::vector<Scene> scenes;
    std::unordered_map<std::string, Mesh*> models;
    std::unordered_map<std::string, Shader*> shaders;
    std::unordered_map<std::string, ShaderProgram*> programs;

    void initializeGLFW();

public:
    Application() = default;    

    Application(const Application& other) = delete;

    ~Application();

    Application& operator=(const Application& other) = delete;

    void initialize();

    void createShaders();

    void createModels();

    void createPrograms();

    void createScenes();

    void run() const;

    void getVersionInfo() const;
};

#endif