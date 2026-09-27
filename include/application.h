#ifndef APPLICATION_H
#define APPLICATION

#include <GLFW/glfw3.h>

#include <vector>

#include "scene.h"

class Application {
    GLFWwindow* window;
    std::vector<Scene> scenes;

public:
    Application() = default;    

    Application(const Application& other) = delete;

    ~Application();

    Application& operator=(const Application& other) = delete;

    void initialize();

    void run() const;

    void getVersionInfo() const;

    void addScene(const Scene& scene);
};

#endif