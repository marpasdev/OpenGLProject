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
#include <random>

#include <glm/trigonometric.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "models/tree.h"
#include "models/sphere.h"
#include "models/bushes.h"
#include "models/plain.h"
#include "models/login.h"
#include "models/space/sun.h"
#include "models/space/earth.h"
#include "models/space/moon.h"
#include "transform/transformcomposite.h"
#include "transform/transformleaf.h"

#include "application.h"

#include <unordered_map>

void WindowDeleter::operator()(GLFWwindow* window) {
	glfwDestroyWindow(window);
}

Application::~Application() {
	scenes.clear();
	window.reset();
	glfwTerminate();
}

void Application::initializeGLFW(int width, int height) {
	if (!glfwInit())
		exit(EXIT_FAILURE);
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE,
	GLFW_OPENGL_CORE_PROFILE);

	window.reset(glfwCreateWindow(width, height, "OpenGL Project", NULL, NULL));
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

void Application::initialize(int windowWidth, int windowHeight) {
	initializeGLFW(windowWidth, windowHeight);
	
	if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
	{
        std::cerr << "GLAD initialization failed\n";
		exit(EXIT_FAILURE);
	}

	glEnable(GL_DEPTH_TEST);
}

void Application::createScenes() {

	std::unordered_map<std::string, std::unique_ptr<Shader>> shaders;
	shaders["basicTransformVert"] = std::make_unique<Shader>(GL_VERTEX_SHADER, "shaders/vertex/basictransform.vert");
    shaders["basicFrag"] = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "shaders/fragment/basic.frag");
	shaders["green"] = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "shaders/fragment/green.frag");
	shaders["lightGreen"] = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "shaders/fragment/lightgreen.frag");
	shaders["yellow"] = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "shaders/fragment/yellow.frag");
	shaders["blue"] = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "shaders/fragment/blue.frag");
	shaders["extendedbasic"] = std::make_unique<Shader>(GL_VERTEX_SHADER, "shaders/vertex/extendedbasictransform.vert");

	std::unordered_map<std::string, std::shared_ptr<ShaderProgram>> programs;
	programs["basic"] = std::make_shared<ShaderProgram>(*shaders.at("basicTransformVert"), *shaders["basicFrag"]);
	programs["green"] = std::make_shared<ShaderProgram>(*shaders.at("basicTransformVert"), *shaders.at("green"));
	programs["lightGreen"] = std::make_shared<ShaderProgram>(*shaders.at("basicTransformVert"), *shaders.at("lightGreen"));
	programs["yellow"] = std::make_shared<ShaderProgram>(*shaders.at("basicTransformVert"), *shaders.at("yellow"));
	programs["blue"] = std::make_shared<ShaderProgram>(*shaders.at("basicTransformVert"), *shaders.at("blue"));
	programs["extendedBasic"] = std::make_shared<ShaderProgram>(*shaders.at("extendedbasic"), *shaders.at("basicFrag"));
    float aspectRatio = 800.0f / 600.0f;

	std::vector<VertexAttribute> layout6;
	layout6.push_back({3, GL_FLOAT});
	layout6.push_back({3, GL_FLOAT});

	std::vector<VertexAttribute> layout9;
	layout9.push_back({3, GL_FLOAT});
	layout9.push_back({3, GL_FLOAT});
	layout9.push_back({3, GL_FLOAT});

    float points[] = {
        0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };
	
	std::unordered_map<std::string, std::shared_ptr<Model>> models;
    models["triangle"] = std::make_shared<Model>(points, sizeof(points), layout6);

    float square[] = {
        -0.5f, aspectRatio * 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -aspectRatio * 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -aspectRatio * 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, aspectRatio * 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, aspectRatio * -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, aspectRatio * 0.5f, 0.0f, 1.0f, 1.0f, 0.0f
    };
	models["square"] = std::make_shared<Model>(square, sizeof(square), layout6);
	models["sphere"] = std::make_shared<Model>(sphere, sizeof(sphere), layout6);
	models["plain"] = std::make_shared<Model>(plain, sizeof(plain), layout6);
    models["login"] = std::make_shared<Model>(login, sizeof(login), layout6);
	models["tree"] = std::make_shared<Model>(tree, sizeof(tree), layout6);
	models["bushes"] = std::make_shared<Model>(bushes, sizeof(bushes), layout6);

	// solar system
	models["sun"] = std::make_shared<Model>(sun, sizeof(sun), layout9);
	models["earth"] = std::make_shared<Model>(earth, sizeof(earth), layout9);
	models["moon"] = std::make_shared<Model>(moon, sizeof(moon), layout9);
    std::vector<std::unique_ptr<DrawableObject>> objects;

	// Scene 0
	auto triangleTransform = std::make_shared<TransformComposite>();
	triangleTransform->add(std::make_shared<TransformLeaf>(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.5f, 0.0f))));
	triangleTransform->add(std::make_shared<TransformLeaf>(glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f))));

	// opposite order of transformations:
	// triangleTransform->add(std::make_shared<TransformLeaf>(glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f))));
	// triangleTransform->add(std::make_shared<TransformLeaf>(glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, 0.0f))));
	objects.push_back(std::make_unique<DrawableObject>(models.at("triangle"),
								programs.at("basic"),
								triangleTransform
								));
	scenes.push_back(Scene(std::move(objects)));

	auto loginTransform = std::make_shared<TransformComposite>();
	loginTransform->add(std::make_shared<TransformLeaf>(glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f))));
	loginTransform->add(std::make_shared<TransformLeaf>(glm::scale(glm::mat4(1.0f), glm::vec3(0.7f))));
	objects.push_back(std::make_unique<DrawableObject>(models.at("login"),
									programs.at("basic"),
									loginTransform
								));
	scenes.push_back(Scene(std::move(objects)));

	// Scene 1
	objects.clear();
	// objects.push_back(std::make_unique<DrawableObject>(models.at("sphere").get(),
	// 							programs.at("basic").get(),
	// 						Transformation(
	// 							glm::translate(glm::mat4)
	// 							glm::vec3{0.1f}
	// 						)));
	// objects.push_back(std::make_unique<DrawableObject>(models.at("login").get(),
	// 								programs.at("basic").get(),
	// 							Transformation(
	// 								glm::vec3{0.8f, -0.8f, 0.0f},
	// 								glm::vec3(0.0f, glm::radians(15.0f), 0.0f),
	// 								glm::vec3{0.2f}
	// 							)));
	// scenes.push_back(Scene(std::move(objects)));
	
	// std::mt19937 rng{std::random_device{}()};

	// std::uniform_real_distribution<float> dist(-0.8f, 0.8f);
	// std::uniform_real_distribution<float> randomAngle(0, 360);
	
	// Scene 2
	// objects.clear();
	// objects.push_back(std::make_unique<DrawableObject>(models.at("plain").get(),
	// 								programs.at("lightGreen").get(),
	// 								Transformation(
	// 									glm::vec3{0.0f, 0.0f, 0.2f},
	// 									glm::vec3(glm::radians(90.0f), 0.0f, 0.0f),
	// 									glm::vec3{1.0f}
	// 								)));
	// objects.push_back(std::make_unique<DrawableObject>(models.at("plain").get(),
	// 								programs.at("blue").get(),
	// 								Transformation(
	// 									glm::vec3{0.0f, 1.8f, 0.1f},
	// 									glm::vec3(glm::radians(90.0f), 0.0f, 0.0f),
	// 									glm::vec3{1.0f}
	// 								)));
	// for (size_t i = 0; i < 15; ++i) {
	// 	objects.push_back(std::make_unique<DrawableObject>(models.at("tree").get(),
	// 									programs.at("green").get(),
	// 									Transformation(
	// 										glm::vec3{dist(rng), dist(rng) - 0.2f, 0.0f},
	// 										glm::vec3(glm::radians(-30.0f), /*glm::radians(randomAngle(rng))*/0.0f, 0.0f),
	// 										glm::vec3{0.04f}
	// 									)));
	// 	objects.push_back(std::make_unique<DrawableObject>(models.at("bushes").get(),
	// 									programs.at("green").get(),
	// 									Transformation(
	// 										glm::vec3{dist(rng), dist(rng), 0.0f},
	// 										glm::vec3(0.0f, glm::radians(randomAngle(rng)), 0.0f),
	// 										glm::vec3{0.2f}
	// 									)));
	// }
	
	// objects.push_back(std::make_unique<DrawableObject>(models.at("sphere").get(),
	// 								 programs.at("yellow").get(),
	// 								 Transformation(
	// 									glm::vec3{0.0f, 0.9f, 0.0f},
	// 									glm::vec3(0.0f),
	// 									glm::vec3{0.05f}
	// 								 )));
	// objects.push_back(std::make_unique<DrawableObject>(models.at("login").get(),
	// 								programs.at("basic").get(),
	// 							Transformation(
	// 								glm::vec3{0.8f, -0.8f, -0.1f},
	// 								glm::vec3(0.0f, glm::radians(15.0f), 0.0f),
	// 								glm::vec3{0.2}
	// 							)));
	// scenes.push_back(Scene(std::move(objects)));

	// Scene 3
	// objects.clear();
	// objects.push_back(std::make_unique<DrawableObject>(models.at("login").get(),
	// 								programs.at("basic").get(),
	// 							Transformation(
	// 								glm::vec3{0.0f},
	// 								glm::vec3(0.0f, glm::radians(30.0f), 0),
	// 								glm::vec3{0.7f}
	// 							)));
	// scenes.push_back(Scene(std::move(objects)));
	
	// Scene 4 - solar system
	objects.clear();
	// Sun
	// objects.push_back(std::make_unique<DrawableObject>(models.at("sun").get(),
	// 		programs.at("extendedBasic").get(),
	// 		Transformation(
	// 			glm::translate(glm::mat4(1.0f), glm::vec3(0.0f)),
	// 			glm::mat4(1.0f),
	// 			glm::scale(glm::mat4(1.0f), glm::vec3(0.2f))
	// 		)));
	// // Earth
	// objects.push_back(std::make_unique<DrawableObject>(models.at("earth").get(),
	// 		programs.at("extendedBasic").get(),
	// 		Transformation(
	// 			glm::translate(glm::mat4(1.0f), glm::vec3(0.7f, 0.0f, 0.0f)),
	// 			glm::mat4(1.0f),
	// 			glm::scale(glm::mat4(1.0f), glm::vec3(0.03f))
	// 		)));

	// // Moon
	// objects.push_back(std::make_unique<DrawableObject>(models.at("moon").get(),
	// 		programs.at("extendedBasic").get(),
	// 		Transformation(
	// 			glm::translate(glm::mat4(1.0f), glm::vec3(0.8f, 0.0f, 0.0f)),
	// 			glm::mat4(1.0f),
	// 			glm::scale(glm::mat4(1.0f), glm::vec3(0.02f))
	// 		)));
	// objects.push_back(std::make_unique<DrawableObject>(models.at("login").get(),
	// 		programs.at("basic").get(),
	// 		Transformation(
	// 			glm::translate(glm::mat4(1.0f), glm::vec3(0.8f, -0.8f, 0.0f)),
	// 			glm::rotate(glm::mat4(1.0f), glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
	// 			glm::scale(glm::mat4(1.0f), glm::vec3(0.2f))
	// 		)));

	// scenes.push_back(Scene(std::move(objects)));

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

void Application::processInput(float deltaTime) {
	// float angleSpeed = glm::radians(90.0f);
	// GLFWwindow* win = window.get();

	// if (glfwGetKey(win, GLFW_KEY_LEFT) == GLFW_PRESS) {
	// 	rotation.y += angleSpeed * deltaTime;
	// }
	// if (glfwGetKey(win, GLFW_KEY_RIGHT) == GLFW_PRESS) {
	// 	rotation.y -= angleSpeed * deltaTime;
	// }
	// if (glfwGetKey(win, GLFW_KEY_UP) == GLFW_PRESS) {
	// 	rotation.x += angleSpeed * deltaTime;
	// }
	// if (glfwGetKey(win, GLFW_KEY_DOWN) == GLFW_PRESS) {
	// 	rotation.x -= angleSpeed * deltaTime;
	// }

	// if (rotation.y < 0.0f) {
	// 	rotation.y += glm::radians(360.0f);
	// }
	// if (rotation.x < 0.0f) {
	// 	rotation.x += glm::radians(360.0f);
	// }
	// if (rotation.y >= glm::radians(360.0f)) {
	// 	rotation.y = 0.0f;
	// }
	// if (rotation.x >= glm::radians(360.0f)) {
	// 	rotation.x = 0.0f;
	// }
}

void Application::run() {
	double previousTime = glfwGetTime();

    while (!glfwWindowShouldClose(window.get())) {
		double now = glfwGetTime();
		float deltaTime = static_cast<float>(now - previousTime);
		previousTime = now;

		processInput(deltaTime);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// scenes.at(3).getObject(0)->setTransform(Transformation(glm::translate(glm::mat4{1.0f}, glm::vec3{0.0f}),
		// 										glm::rotate(glm::mat4{1.0f}, ),
		// 										glm::scale(glm::mat4{1.0f}, glm::vec3{0.7f})));

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