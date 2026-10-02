#include <glad/gl.h>

#include <cstdlib>
#include <cstdio>
#include <iostream>

#include "models/tree.h"
#include "models/gift.h"
#include "models/login.h"

#include "application.h"

Application::~Application() {
	for (const auto& m : models) {
		delete m.second;
	}

	for (const auto& p : programs) {
		delete p.second;
	}

	for (const auto& s : shaders) {
		delete s.second;
	}

    glfwDestroyWindow(window);
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

	window = glfwCreateWindow(800, 600, "OpenGL Project", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	
	glfwMakeContextCurrent(window);
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
    models["triangle"] =  new Mesh(points, sizeof(points));

    float square[] = {
        -0.5f, aspectRatio * 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -aspectRatio * 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -aspectRatio * 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, aspectRatio * 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, aspectRatio * -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, aspectRatio * 0.5f, 0.0f, 1.0f, 1.0f, 0.0f
    };
    models["square"] = new Mesh(square, sizeof(square));

    models["tree"] = new Mesh(tree, sizeof(tree));
    models["gift"] = new Mesh(gift, sizeof(gift));
    models["login"] = new Mesh(login, sizeof(login));
}

void Application::createShaders() {
    shaders["basicVert"] = new Shader(GL_VERTEX_SHADER, "shaders/vertex/basic.vert");
    shaders["basicFrag"] = new Shader(GL_FRAGMENT_SHADER, "shaders/fragment/basic.frag");

    shaders["scaledownVert"] = new Shader(GL_VERTEX_SHADER, "shaders/vertex/scaledown.vert");
    shaders["moveVert"] = new Shader(GL_VERTEX_SHADER, "shaders/vertex/move.vert");

    shaders["greenFrag"] = new Shader(GL_FRAGMENT_SHADER, "shaders/fragment/green.frag");
    shaders["reddishFrag"] = new Shader(GL_FRAGMENT_SHADER, "shaders/fragment/reddish.frag");
   
    shaders["translation"] = new Shader(GL_VERTEX_SHADER, "shaders/vertex/translation.vert");

	shaders["transformVert"] = new Shader(GL_VERTEX_SHADER, "shaders/vertex/transform.vert");
}

void Application::createPrograms() {

    programs["prog1"] = new ShaderProgram(*shaders["basicVert"], *shaders["basicFrag"]);
    programs["prog2"] = new ShaderProgram(*shaders["scaledownVert"], *shaders["greenFrag"]);
    programs["prog3"] = new ShaderProgram(*shaders["moveVert"], *shaders["reddishFrag"]);

    programs["translation"] = new ShaderProgram(*shaders["translation"], *shaders["basicFrag"]);

	programs["transformProg"] = new ShaderProgram(*shaders["transformVert"], *shaders["basicFrag"]);
	programs["transformProg"]->setUniform("translation", 0.0f, -0.5f, 0.0f);
	programs["transformProg"]->setUniform("rotY", 1.0f);
	programs["transformProg"]->setUniform("scale", 0.2f, 0.2f, 0.2f);
}

void Application::createScenes() {

    std::vector<RenderMesh> meshes;
    // meshes.emplace_back(RenderMesh(models["triangle"], programs["transformProg"]));
    // meshes.emplace_back(RenderMesh(models["square"], programs["prog2"]));
    // meshes.emplace_back(RenderMesh(models["tree"], programs["prog3"]));
    // meshes.emplace_back(RenderMesh(models["gift"], programs["prog2"]));
    meshes.emplace_back(RenderMesh(models["tree"], programs["transformProg"]));

    Scene scene1 = Scene(meshes);
	scenes.push_back(scene1);
}

void Application::run() const {
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (scenes.size() > 0) {
			scenes[0].render();
		}

        glfwSwapBuffers(window);
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