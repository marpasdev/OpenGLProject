/**
 * @file application.cpp
 *
 * @brief A class that manages scenes and their resources.
 *
 * @author Marek Pastva
 * 
 * @login PAS0217
 *
 * @year 2026
 **/

#include <glad/gl.h>

#include <cstdlib>
#include <cstdio>
#include <iostream>

#include "models/tree.h"
#include "models/sphere.h"
#include "models/bushes.h"
#include "models/plain.h"
#include "models/login.h"

#include "application.h"

void WindowDeleter::operator()(GLFWwindow* window) {
	glfwDestroyWindow(window);
}

Application::~Application() {
	scenes.clear();
	programs.clear();
	shaders.clear();
	models.clear();
	window.reset();
	glfwTerminate();
}

void Application::initializeGLFW() {
	if (!glfwInit())
		exit(EXIT_FAILURE);
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE,
	GLFW_OPENGL_CORE_PROFILE);

	window.reset(glfwCreateWindow(1200, 900, "OpenGL Project", NULL, NULL));
	if (!window.get())
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	
	glfwMakeContextCurrent(window.get());
	glfwSwapInterval(1);

	glfwSetWindowUserPointer(window.get(), this);
	glfwSetKeyCallback(window.get(), keyCallback);
}

void Application::initialize() {
	initializeGLFW();
	
	if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
	{
        std::cerr << "GLAD initialization failed\n";
		exit(EXIT_FAILURE);
	}

	glEnable(GL_DEPTH_TEST);
}

void Application::createModels() {
    float aspectRatio = 800.0f / 600.0f;

    float points[] = {
        0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };
    models["triangle"] = std::make_unique<Model>(points, sizeof(points));

    float square[] = {
        -0.5f, aspectRatio * 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -aspectRatio * 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -aspectRatio * 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, aspectRatio * 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, aspectRatio * -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, aspectRatio * 0.5f, 0.0f, 1.0f, 1.0f, 0.0f
    };
	models["square"] = std::make_unique<Model>(square, sizeof(square));
	models["sphere"] = std::make_unique<Model>(sphere, sizeof(sphere));
	models["plain"] = std::make_unique<Model>(plain, sizeof(plain));
    models["login"] = std::make_unique<Model>(login, sizeof(login));
	models["tree"] = std::make_unique<Model>(tree, sizeof(tree));
	models["bushes"] = std::make_unique<Model>(bushes, sizeof(bushes));
}

void Application::createShaders() {
	shaders["basicTransformVert"] = std::make_unique<Shader>(GL_VERTEX_SHADER, "shaders/vertex/basictransform.vert");

    shaders["basicFrag"] = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "shaders/fragment/basic.frag");

	shaders["green"] = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "shaders/fragment/green.frag");
	shaders["lightGreen"] = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "shaders/fragment/lightgreen.frag");
	shaders["yellow"] = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "shaders/fragment/yellow.frag");
}

void Application::createPrograms() {
	programs["basic"] = std::make_unique<ShaderProgram>(*shaders.at("basicTransformVert"), *shaders["basicFrag"]);
	programs["green"] = std::make_unique<ShaderProgram>(*shaders.at("basicTransformVert"), *shaders.at("green"));
	programs["lightGreen"] = std::make_unique<ShaderProgram>(*shaders.at("basicTransformVert"), *shaders.at("lightGreen"));
	programs["yellow"] = std::make_unique<ShaderProgram>(*shaders.at("basicTransformVert"), *shaders.at("yellow"));
}

void Application::createScenes() {

    std::vector<DrawableObject> objects;

	objects.push_back(DrawableObject(models.at("triangle").get(),
								programs.at("basic").get()));
	scenes.push_back(Scene(objects));

	objects.clear();
	objects.push_back(DrawableObject(models.at("sphere").get(),
								programs.at("basic").get()));
	scenes.push_back(Scene(objects));
	
	objects.clear();
	// objects.push_back(DrawableObject(models.at("tree").get(),
	// 								 programs.at("basic").get(),
	// 								 Transformation(
	// 									glm::vec3{0.0f, -0.5f, 0.0f},
	// 									glm::vec3(0.0f, 1.0f, 0.0f),
	// 									glm::vec3{0.2f}
	// 								 )));
}

void Application::keyCallback(GLFWwindow* window, int key, [[maybe_unused]] int scancode, int action, [[maybe_unused]] int mods) {
	auto* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (app) {
		app->onKey(key, action);
	}
}

void Application::onKey(int key, int action) {
	if (key == GLFW_KEY_ESCAPE) {
		glfwSetWindowShouldClose(window.get(), GLFW_TRUE);
	}
	if (action == GLFW_PRESS && key >= GLFW_KEY_0 && key <= GLFW_KEY_9) {
		size_t index = key - GLFW_KEY_0;
		if (currentScene != index && index < scenes.size()) {
			currentScene = index;
		}
	}
	if (action == GLFW_PRESS && key >= GLFW_KEY_KP_0 && key <= GLFW_KEY_KP_9) {
		size_t index = key - GLFW_KEY_KP_0;
		if (currentScene != index && index < scenes.size()) {
			currentScene = index;
		}
	}
}

void Application::run() const {
    while (!glfwWindowShouldClose(window.get())) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		scenes[currentScene].render();

        glfwSwapBuffers(window.get());
        glfwPollEvents();
    }
}

void Application::getVersionInfo() const {
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);
}