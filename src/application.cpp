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
    models["triangle"] = std::make_unique<Mesh>(points, sizeof(points));

    float square[] = {
        -0.5f, aspectRatio * 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -aspectRatio * 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -aspectRatio * 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, aspectRatio * 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, aspectRatio * -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, aspectRatio * 0.5f, 0.0f, 1.0f, 1.0f, 0.0f
    };
	models["square"] = std::make_unique<Mesh>(square, sizeof(square));
    models["login"] = std::make_unique<Mesh>(login, sizeof(login));
	models["tree"] = std::make_unique<Mesh>(tree, sizeof(tree));
	models["gift"] = std::make_unique<Mesh>(gift, sizeof(gift));
}

void Application::createShaders() {
    shaders["basicVert"] = std::make_unique<Shader>(GL_VERTEX_SHADER, "shaders/vertex/basic.vert");
    shaders["basicFrag"] = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "shaders/fragment/basic.frag");

    shaders["scaledownVert"] = std::make_unique<Shader>(GL_VERTEX_SHADER, "shaders/vertex/scaledown.vert");
    shaders["moveVert"] = std::make_unique<Shader>(GL_VERTEX_SHADER, "shaders/vertex/move.vert");

    shaders["greenFrag"] = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "shaders/fragment/green.frag");
    shaders["reddishFrag"] = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "shaders/fragment/reddish.frag");
   
    shaders["translation"] = std::make_unique<Shader>(GL_VERTEX_SHADER, "shaders/vertex/translation.vert");

	shaders["transformVert"] = std::make_unique<Shader>(GL_VERTEX_SHADER, "shaders/vertex/transform.vert");
}

void Application::createPrograms() {

    programs["prog1"] = std::make_unique<ShaderProgram>(*shaders["basicVert"], *shaders["basicFrag"]);
    programs["prog2"] = std::make_unique<ShaderProgram>(*shaders["scaledownVert"], *shaders["greenFrag"]);
    programs["prog3"] = std::make_unique<ShaderProgram>(*shaders["moveVert"], *shaders["reddishFrag"]);

    programs["translation"] = std::make_unique<ShaderProgram>(*shaders["translation"], *shaders["basicFrag"]);

	programs["transformProg"] = std::make_unique<ShaderProgram>(*shaders["transformVert"], *shaders["basicFrag"]);
	programs["transformProg"]->setUniform("translation", 0.0f, -0.5f, 0.0f);
	programs["transformProg"]->setUniform("rotY", 1.0f);
	programs["transformProg"]->setUniform("scale", 0.2f, 0.2f, 0.2f);
}

void Application::createScenes() {

    std::vector<RenderMesh> meshes;
    // meshes.push_back({RenderMesh(models.at("triangle").get(), programs.at("transformProg").get()});
    // meshes.push_back({RenderMesh(models.at("square").get(), programs.at("prog2").get()});
    // meshes.push_back({RenderMesh(models.at("tree").get(), programs.at("prog3").get()});
    // meshes.push_back({RenderMesh(models.at("gift").get(), programs.at("prog2").get()});
    meshes.push_back({models.at("tree").get(), programs.at("transformProg").get()});

	scenes.emplace_back(std::move(meshes));
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