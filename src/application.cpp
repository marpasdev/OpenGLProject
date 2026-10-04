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
#include "models/gift.h"
#include "models/login.h"

#include "application.h"

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
    models["login"] = std::make_unique<Model>(login, sizeof(login));
	models["tree"] = std::make_unique<Model>(tree, sizeof(tree));
	models["gift"] = std::make_unique<Model>(gift, sizeof(gift));
}

void Application::createShaders() {
    shaders["basicFrag"] = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "shaders/fragment/basic.frag");
	shaders["transformVert"] = std::make_unique<Shader>(GL_VERTEX_SHADER, "shaders/vertex/transform.vert");
}

void Application::createPrograms() {
	programs["transformProg"] = std::make_unique<ShaderProgram>(*shaders["transformVert"], *shaders["basicFrag"]);
}

void Application::createScenes() {

    std::vector<DrawableObject> objects;
	objects.push_back(DrawableObject(models.at("tree").get(),
									 programs.at("transformProg").get(),
									 Transformation(
										glm::vec3{0.0f, -0.5f, 0.0f},
										glm::vec3(0.0f, 1.0f, 0.0f),
										glm::vec3{0.2f}
									 )));

	scenes.emplace_back(std::move(objects));
}

void Application::run() const {
    while (!glfwWindowShouldClose(window.get())) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (scenes.size() > 0) {
			scenes[0].render();
		}

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